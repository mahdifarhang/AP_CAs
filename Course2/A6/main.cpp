#include <string>
#include <vector>
#include <iostream>
#include "error.h"
#include "StringTokenizer.h"

#define DELAY_TIME 10

using namespace std;

int main()
{
  string input;


  while(getline(cin, input))
  {
    try
    {
      StringTokenizer temp(spacing(input, "=,<>();"), "\t ");
      vector<string> line = temp.get_all_tokens();
      if (line[0] == "draw")
      {

      }
      else if (line[0] == "erase")
      {

      }
      else if (line[0] == "save")
      {

      }
      else if (line[0] == "export")
      {

      }
      else if (line[0] == "group")
      {

      }
      else if (line[0] == "ungroup")
      {

      }
      else if (line[0] == "list")
      {

      }
      else if (line[0] == "touch")
      {

      }
      else if (line[0] == "bring")
      {

      }
      else if (line[0] == "init")
      {

      }
      else if (line[0] == "move")
      {

      }
      else
      {
        Error bug("Soory, but no action match with what you entered");
        throw bug;
      }

      Delay(DELAY_TIME);
    }
    catch(Error bug)
    {
      cout << bug << endl;
    }
  }
}
