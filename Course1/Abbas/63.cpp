#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string note, result;
  ifstream myfile;
  myfile.open("text.txt");
  char c;
  while(myfile.get(c))
    note += c;
  myfile.close();
  for (int i = 0; i < note.size() - 1; i++)
    if (note[i] == ' ' && note[i + 1] == ' ')
      {
        note.erase(note.begin() + i + 1);
        i--;
      }
  ofstream file;
  file.open("text.txt");
  file << note;
  file.close();

}
