#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string encoder(string& w)//a function which codes our string;
{
  if (w.size() == 1)
   return w;
  string temp1 = w.substr(0, w.size() / 2);
  string temp2;
  if (w.size() % 2 == 0)
    temp2 = w.substr(w.size() / 2, w.size() / 2);
  else
    temp2 = w.substr(w.size() / 2, w.size() / 2 + 1);
  reverse(temp1.begin(), temp1.end());
  reverse(temp2.begin(), temp2.end());
  return encoder(temp2) + encoder(temp1);
}

int main()
{
  string n = "";
  int i, j;
  cin >> i >> j;
  if (j > i || i < 1 || j < 1)
  {
    cout << "wrong input." << endl;
    return 0;
  }
  for (int k = 0; k < i; k++)
    n += "a";
  n[j - 1] = ';';
  string temp = encoder(n);
  for (int k = 0; k < temp.size(); k++)
    if (temp[k] == ';')
      cout << k + 1 << endl;
}
