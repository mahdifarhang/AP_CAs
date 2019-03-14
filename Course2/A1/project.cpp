#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct Table
{
  string TableName;
  vector<string> ColumnNames;
  vector<vector<string> > Records;
};
struct ColumnCon
{
  string Main;
  string Column;
};
struct WordCon
{
  string Main;
  string Word;
};

void CreateSQL(vector<Table>&, vector<string>);//creating a table using CreateTable function and according to what user says.
void CreateTable(string, vector<string>, vector<Table>&);//creating a table without any records. it was said in the first phase of the project.
void InsertSQL(vector<Table>*, vector<string>);//Inserting a record to a table using Insert function and according to what user said.
void Insert(string , vector<Table>* , vector<string>);//inserting a record to a specific table.first phase of the project.
Table SelectSQL(vector<Table>, vector<string>);//detecting what conditions do the user wants us to make before printing the table on the screen.
vector<vector<string> > Select(Table, vector<ColumnCon>, vector<WordCon>);/*this function and the two below will help us select some records with the conditions said from input
we still have to take two vectors and that will be another function's job to give the informations from input and make the conditions into two diffrent vectors.*/
vector<string> Seperating(string);//takes a line as the input and puts each words of it to a diffrent element of a vector.
void CheckWithColumn(vector<vector<string> >&, int, int);//checks if this specific condition is used in this row. the condition is between two columns.
void CheckWithWord(vector<vector<string> >&, int, string);//checks if this specific condition is used in this row. the condition is between a column and a specific word.
void Show(Table);

int main()
{
  vector<Table> Tables;
  string input;
  vector<string> line;
  while(true)
  {
    getline(cin, input);//getting from the users.
    line = Seperating(input);
    if (line[0] == "CREATE" && line[1] == "TABLE")
      CreateSQL(Tables, line);
    else if (line[0] == "INSERT" && line[1] == "INTO")
      InsertSQL(&Tables, line);
    else if (line[0] == "SELECT" && line[1] == "*" && line[2] == "FROM")
    {
      Table printing = SelectSQL(Tables, line);
      Show(printing);
    }
  }
}

void CreateSQL(vector<Table>& tables, vector<string> line)//creating a table using CreateTable function and according to what user says.
{
  string TableName = line[2];//selecting the name.
  if (line[3] != "(")//if the name of the table is'nt one word.
  {
    while(line[3] != "(")
    {
      TableName = TableName + " " + line[3];
      line.erase(line.begin() + 3);
    }
  }
  vector<string> ColList;//having the a vectorfor the names of columns of this table.
  for (int i = 4; i < line.size() - 2; i += 3)//adding the names of each of the column names.
    ColList.push_back(line[i]);
  CreateTable(TableName, ColList, tables);//creating the table.
}
void CreateTable(string Name, vector<string> ColumnNames, vector<Table>& Tables)//creating the table.
{
  Table temp;
  temp.TableName = Name;
  temp.ColumnNames = ColumnNames;
  Tables.push_back(temp);
  cout << "Query OK" << endl;
}
void InsertSQL(vector<Table>* tables, vector<string> line)
{
  string TableName = line[2];
  if (line[3] != "VALUES")//if the table name wasn't one word.
  {
    while(line[3] != "VALUES")
    {
      TableName = TableName + " " + line[3];
      line.erase(line.begin() + 3);
    }
  }
  vector<string> Record;//creating a vector to have the each one of the datas in it.
  int i = 5;
  string temp;
  while(line[i] != ";")//scanning untill reaching to ) .
  {
    temp = "";
    while(line[i] != ")")//end of each word.
    {
      if (line[i] == ",")
        break;
      if (!(line[i][0] == '"'))

      {
          temp = temp + line[i] + " ";
      }
      i++;
    }
    temp.erase(temp.size() - 1);// two spaces and one " in the end of our temp.
    Record.push_back(temp);//adding the word to the record vector.
    i++;
  }
  Insert(TableName, tables, Record);//inserting the record to the table.
}
void Insert(string TableName, vector<Table>* Tables, vector<string> Inputs)//inserting a record to a table.
{
  int j = 0;
  for (int i = 0; i < Tables->size(); i++)
  {
    if (TableName == (*Tables)[i].TableName)//finding which table we should insert the record to.
    {
      ((*Tables)[i].Records).push_back(Inputs);//inserting the record.
      j = i;
      break;
    }
  }
  cout << "Query OK" << endl;
  // for (int i = 0; i < ((*Tables)[j].Records).size(); i++)
  //   for (int k = 0; k < ((*Tables)[j].Records)[i].size(); k++)
  //     cout << ((*Tables)[j].Records)[i][k] << "\n" << endl;
}
Table SelectSQL(vector<Table> tables, vector<string> line)
{
  Table Result;//to give the output to the function which prints the whole table on the screen.
  vector<ColumnCon> Ccondition;//having a vector to give it to the select function.
  vector<WordCon> Wcondition;//same.
  string TableName = line[3];
  // if (line[4] != "WHERE" && line[4] != ";")//if the table name wasn't one word.
  // {
  //   while(line[4] != "WHERE" && line[4] != ";")
  //   {
  //     TableName = TableName + " " + line[4];
  //     line.erase(line.begin() + 4);
  //   }
  // }
  int num = 0;
  for (int i = 0; i < tables.size(); i++)//finding wich table we are working on.
    if ((tables[i]).TableName == TableName)
    {
      num = i;
      break;
    }
  Result.TableName = TableName;
  Result.ColumnNames = tables[num].ColumnNames;
  vector<string> temps;//used to put each one of the conditions in to one of these.
  if (line.size() < 6)
    Result.Records = Select(tables[num], Ccondition, Wcondition);
  else
  {
    int i = 5;
    string temp = "";//used to create the temps vector in the line below.
    while (i < line.size() && line[i] != ";")//doing it untill the end of the line inserted by the user. and puting every condition to temps vector.
    {
      temp = "";
      while (line[i] != "," && line[i] != ";")//doing untill we reach to the end of a condition.
      {
        temp = temp + line[i] + " ";
        i++;
      }
      temp.erase(temp.size() - 1);//erasing the last space.
      temps.push_back(temp);//ading to the temps
      if (i != line[i].size() - 1)
        i++;
        else  break;
    }
    bool isWcon = false;//a flag to get which kind of condition is that.
    for (int i = 0; i < temps.size(); i++)//doing the rest for each of the condition.
    {
      isWcon = false;
      for(int j = 0; j < (temps[i]).size(); j++)
      {
        if (temps[i][j] == '"')//if our condition had " " it means is a condition in the form of W_C.
          isWcon = true;
      }
      if (isWcon)//doing it for W_C conditions.
      {
        WordCon s;
        if(temps[i][0] == '"')//if the word was the first element around the = operator(before that).
        {
          int j = 0;
          temps[i].erase(0, 2);//the two first words are " and space and we don't need them.
          while(true)//getting the word of this condition.
          {
            if (temps[i][j] == '=')//we have reached to the = operator.
            {
              s.Word = temps[i].substr(0, j - 3);//we need the string from the beginning to = but there is a " and two spaces around it.
              break;//out of loop.
            }
            j++;
          }
          s.Main = temps[i].substr(j + 2 , temps[i].size() - j - 2);//adding the other word to the other string of our struct in W_C condition.
        }
        else//if the name was the second element of our condition (after =).
        {
          vector<string> e = Seperating(temps[i]);
          s.Main = e[0];
          e.erase(e.begin());
          e.erase(e.begin());
          e.erase(e.begin());
          string c = "";
          for (int k = 0; k < e.size() - 1; k++)
          {
            c = c + e[k] + " ";
          }
          c.erase(c.size() - 1);
          s.Word = c;
        }
        Wcondition.push_back(s);//adding it to our vector.
      }
      else//the second form of condition (C_C).
      {
        ColumnCon s;
        for (int j = 0; j < temps[i].size(); j++)//doing the rest for all of the C conditions.
        {
          if (temps[i][j] == '=')//we have reached to the = and our second word has started.
          {
            s.Main = temps[i].substr(0, j - 1);
            s.Column = temps[i].substr(j + 2, temps[i].size() - j - 2);
            break;
          }
        }
        Ccondition.push_back(s);
      }
    }
    Result.Records = Select(tables[num], Ccondition, Wcondition);
  }
  return Result;
}
vector<vector<string> > Select(Table table,vector<ColumnCon> Ccondition, vector<WordCon> Wcondition)
{
  vector<vector< string> > Result = table.Records;//creating a list of records so we can present it at last.we give all the records of the table to this list and we erase the lines we don't want from this table.
  int j = 0 , k = 0;//these two will be used to find out wich column are the ones we should check with.
  for (int i = 0; i < Ccondition.size(); i++)//doing all the conditions with "column-column" situation
  {
    j = k = 0;
    for (j = 0; j < (table.ColumnNames).size(); j++)//finding which column is the first condition.
      if (Ccondition[i].Main == (table.ColumnNames)[j])
        break;
    for (k = 0; k < (table.ColumnNames).size(); k++)//finding which column is the second condition.
      if (Ccondition[i].Column == (table.ColumnNames)[k])
        break;
    CheckWithColumn(Result, j, k);//check if the records of the table have this conditions or not.
  }
  for (int i = 0; i < Wcondition.size(); i++)//doing all the conditions with "column-word" situation.
  {
    j = 0;
    for (j = 0; j < (table.ColumnNames).size(); j++)//finding the column to do so.
      if (Wcondition[i].Main == (table.ColumnNames)[j])
        break;
      // cout << "j : " << j << endl;
      if(j < (table.ColumnNames).size())
      {
        CheckWithWord(Result, j, Wcondition[i].Word);
      }
  }
  return Result;
}
void CheckWithColumn(vector<vector<string> >& Result, int FirstColumnCon, int SecondColumnCon)
{
  for (int i = 0; i < Result.size(); i++)//checking all the records and finding out if they are qualified to stay on and being printed as the selected list.
  {
    if((Result[i])[FirstColumnCon] != (Result[i])[SecondColumnCon])//erasing the records which don't have the "C-C" condition.
    {
      Result.erase(Result.begin() + i);
      i--;//number of the elements in this vectorwill reduce by one if we erase the data we don't want. so we have to go back to the previous element.
    }
  }
}
void CheckWithWord(vector<vector<string> >& Result, int ColumnCon, string Word)
{
  for (int i = 0; i < Result.size(); i++)//checking all the records and finding out if they are qualified to stay on and being printed as the selected list.
  {
    if ((Result[i])[ColumnCon] != Word)//erasing the records which don't have the "C-W" condition.
    {
      Result.erase(Result.begin() + i);//number of the elements in this vectorwill reduce by one if we erase the data we don't want. so we have to go back to the previous element.
      i--;
    }
  }
}
vector<string> Seperating(string input)
{
  for (int i = 0; i < input.size(); i++)//seperating the ones which should get seperated.
  {
    if(input[i] == '='|| input[i] == '*'|| input[i] == ';'|| input[i] == ','|| input[i] == '('|| input[i] == ')' || input[i] == '"')
    {
      input.insert(i, " ");
      input.insert(i + 2, " ");
      i += 2;
    }
  }
  istringstream iss(input);
  string word;
  vector<string> line;
  while(iss >> word)//seperating each word into our vector.
    line.push_back(word);
  return line;
}
void Show(Table table)
{
  vector<int> colmax;
  for (int i = 0; i < (table.ColumnNames).size(); i++)//finding out what is the biggest size of stirng in each columns
    colmax.push_back(((table.ColumnNames)[i]).size());
  for(int j = 0; j < colmax.size(); j++)
  {
    for (int i = 0; i < (table.Records).size(); i++)
    {
      if(colmax[j] < ((table.Records)[i][j]).size())
        colmax[j] = ((table.Records)[i][j]).size();
    }
  }
  for (int i = 0; i < (table.ColumnNames).size(); i++)//adding space to beginning and end of each of strings and make all of them the same size.
  {
    (table.ColumnNames)[i] = "| " + (table.ColumnNames)[i];
    int n = (colmax[i] - (table.ColumnNames)[i].size() + 3);//+1 and two beacause it is increasing in the line above.
    for(int j = 0; j < n; j++)
    {
      (table.ColumnNames)[i] = (table.ColumnNames)[i] + " ";
    }

  }
  for (int i = 0; i < (table.Records).size(); i++)
  {
    for (int j = 0; j < ((table.Records)[i]).size(); j++)
    {
      (table.Records)[i][j] = "| " + (table.Records)[i][j];
      int n = colmax[j] - ((table.Records)[i][j]).size() + 3;
      for (int k = 0; k < n; k++)
      {
        ((table.Records)[i][j]) += " ";
      }
    }
  }
  if ((table.Records).size() == 0)
  {
    cout << "Empty set\n";
  }
  else
  {
    for (int i = 0; i < colmax.size(); i++)
      colmax[i] += 2;

    cout << "+";
    for (int i = 0; i < colmax.size(); i++)
    {
      for (int j = 0; j < (colmax[i]); j++)
        cout << "-";
      cout << "+";
    }
    cout << "\n";

    for (int i = 0; i < (table.ColumnNames).size(); i++)
      cout << (table.ColumnNames)[i];
    cout << "|\n";

    cout << "+";
    for (int i = 0; i < colmax.size(); i++)
    {
      for (int j = 0; j < (colmax[i]); j++)
        cout << "-";
      cout << "+";
    }
    cout << "\n";

    for (int i = 0; i < (table.Records).size(); i++)
    {
      for (int j = 0; j < ((table.Records)[i]).size(); j++)
        cout << (table.Records)[i][j];
      cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < colmax.size(); i++)
    {
      for (int j = 0; j < (colmax[i]); j++)
        cout << "-";
      cout << "+";
    }
    cout << "\n";
    if ((table.Records).size() == 1)
      cout << "1 row in set\n";
    else
    cout << (table.Records).size() << " rows in set\n";
  }
}
