#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string note1, note2, result;
  ifstream firstfile, secondfile;
  firstfile.open("D:\\temp\\File1.txt");
  char c;
  while(firstfile.get(c))
    note1 += c;
  firstfile.close();
  secondfile.open("D:\\temp\\File2.txt");
  while(secondfile.get(c))
    note2 += c;
  secondfile.close();
  ofstream file;
  file.open("D:\\temp\\File1.txt");
  result = note1 + note2;
  file << result;
  file.close();
}
