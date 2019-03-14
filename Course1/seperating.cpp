#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  string all;
  getline(cin, all);
  char note[2];
  string word;
  vector<string> save;
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
        save.push_back(word);
      word = "";
    }
  }
  if (word !="")
    save.push_back(word);
  for (int i = 0; i < save.size() ;i++)
  {
    cout << save[i] << endl;
  }
}
