#include "Galaxy.h"

Galaxy::Galaxy(string n, vector<string> v);
{
  for(int i = 0; i < v.size(); i++)
    cout << v[i] << "_";
  cout << endl;
}
