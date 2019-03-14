#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  fstream check;
  string test;
  check.open("restaurants.txt");
  while(true);
  {
    if (getline(check, test) == "" )
      break;
    cout << test << endl;
    cout << "its done man" << endl;
  }
  check.close();


}
