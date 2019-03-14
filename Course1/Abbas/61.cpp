#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string note, result;
  ifstream myfile("text.txt");
  char c;
  while(myfile.get(c))
    note += c;
  myfile.close();
  for (int i = 0; i < note.size(); i++)
    result += note[note.size() - i - 1];
  ofstream file;
  file.open("text.txt");
  file << result;
  file.close();
}
