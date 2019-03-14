#include "String.h"

void seperating_file(vector<string>& saving, string filename)
{
  ifstream myfile;
  myfile.open(filename);
  while(true)
  {
    string temp;
    getline(myfile, temp);
    if (temp == "")
      break;
    saving.push_back(temp);
  }
  myfile.close();
}
void getting_information(string& username, string& command, vector<string>& arguments)
{
  username = "";
  command = "";
  for (int i = 0; i < arguments.size(); i++)
    arguments.pop_back();
  string all;
  getline(cin, all);
  char note[2];
  string word;
  vector<string> change;
  for (int i = 0; i<all.size();i++)
  {
    if (all[i] != ' ')
    {
      note[0] = all[i];
      word = word + note[0];
    }
    if (all[i] == ' ')
    {
      if (word != "")
        change.push_back(word);
      word = "";
    }
  }
  if (word !="")
    change.push_back(word);

  arguments = change;
  if (change.size() < 2)
    throw "You have to enter at least 2 parameters.";
  username = change[0];
  command = change[1];
  if (change.size() > 2)
  {
    for (int i = 2; i < change.size(); i++)
      change[i] = arguments[i - 2];
    arguments.pop_back();
    arguments.pop_back();
  }
}
int stringToint(string input)
{
  int value = 0;
  int note = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (((int)input[i] - 48) > 9 || ((int)input[i] - 48) < 0)
      throw "Sorry, but you should enter only digits in this place.";
    value += ((int)input[i] - 48) * Tavan(10, input.size() - i -1);
  }
  return value;
}
int Tavan(int paye, int tavan)
{
  int value = 1;
  for (int i = 0; i < tavan; i++)
    value *= paye;
  return value;
}
void seperating_line(string temp, vector<string>& save)//takes the line from "temp" and saves it to "save"
{
  char note[2];
  string word;
  for (int i = 0; i < temp.size();i++)
  {
    if (temp[i] != ' ')
    {
      note[0] = temp[i];
      word = word + note[0];
    }
    if (temp[i] == ' ')
    {
      if (word != "")
        save.push_back(word);
      word = "";
    }
  }
  if (word !="")
    save.push_back(word);
}
