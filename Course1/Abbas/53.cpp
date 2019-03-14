#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  string firstname, lastname, studentno;
  string note;
  cout << "Enter your first name" << endl;
  cin >> firstname;
  cout << "Enter your last name" << endl;
  cin >> lastname;
  cout << "Enter your student number" << endl;
  cin >> studentno;
  ifstream myfile("D:\\temp\\text.txt");
  char c;
  while (myfile.get(c))
    note += c;
  note = note + firstname + '\n' + lastname + '\n' + studentno + '\n';
  ofstream file("D:\\temp\\text.txt");
  file << note;
}
