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
    if (note[i] == ' ' && note[i + 1] > 96 && note[i + 1] < 123)
        note[i + 1] -= 32;
  ofstream file;
  file.open("text.txt");
  file << note;
  file.close();
}
