#include <iostream>
#include <vector>

#define MAXIMUM_SIZE (size * size)
#define MINIMUM_SIZE 1

using namespace std;

struct Table
{
  vector<vector<int> > fields;
  int size;
};

bool find_table(Table&, Table&, int, int);
bool check_equal_tables(Table&, Table&);
void print_table(Table&);
Table get_table();
Table create_check_bigger_table(Table&);
Table create_table_with_same_elements(int, int);

int main()
{
  Table input = get_table();
  Table table = create_table_with_same_elements(input.size, MINIMUM_SIZE);
  if(find_table(table, input, 0, input.size))
    print_table(table);
  else
    cout << "NO SOLUTION" << endl;
}

bool find_table(Table& table, Table& input, int position, int size)
{
  // print_table(table);
  // cout << endl;
  // cin.get();
  Table temp =create_check_bigger_table(table);
  if (check_equal_tables(input, temp))
    return true;
  if (position == size * size)
    return false;
  for (int i = MINIMUM_SIZE; i <= MAXIMUM_SIZE; i++)
  {
    table.fields[position / size][position % size] = i;
    if(find_table(table, input, position + 1, size))
      return true;
  }
  return false;
}
Table create_check_bigger_table(Table& input)
{
  Table result = create_table_with_same_elements(input.size, 0);
  for (int i = 0; i < result.size; i++)
  {
    for (int j = 0; j < result.size; j++)
    {
      if (i - 1 != -1)
        if (input.fields[i][j] < input.fields[i - 1][j])
          result.fields[i][j]++;
      if (j - 1 != -1)
        if (input.fields[i][j] < input.fields[i][j - 1])
          result.fields[i][j]++;
      if (i + 1 != result.size)
        if (input.fields[i][j] < input.fields[i + 1][j])
          result.fields[i][j]++;
      if (j + 1 != result.size)
        if (input.fields[i][j] < input.fields[i][j + 1])
          result.fields[i][j]++;
    }
  }
  return result;
}
bool check_equal_tables(Table& a, Table& b)
{
  if (a.size != b.size)
    return false;
  for (int i = 0; i < a.size; i++)
  {
    for (int j = 0; j < a.size; j++)
      if (a.fields[i][j] != b.fields[i][j])
        return false;
  }
  return true;
}
void print_table(Table& a)
{
  for (int i = 0; i < a.size; i++)
  {
    for (int j = 0; j < a.size; j++)
    {
      cout << a.fields[i][j] << " ";
    }
    cout << endl;
  }
}
Table get_table()
{
  int n;
  // cout << "How many rows and columns you want this table to have?(enter one number): ";
  cin >> n;
  Table result = create_table_with_same_elements(n, 0);
  // cout << "Enter all the elements in order!" << endl;
  for (int i = 0; i < result.size; i++)
  {
    for (int j = 0; j < result.size; j++)
    {
      cin >> result.fields[i][j];
    }
  }
  return result;
}
Table create_table_with_same_elements(int size, int elements)
{
  Table result;
  result.size = size;
  result.fields = vector<vector<int> >(size, vector <int>(size, elements));
  return result;
}
