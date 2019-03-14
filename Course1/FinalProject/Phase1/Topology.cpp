#include "Topology.h"

void DividingUniverse(vector<Planet>& Planets, vector<Galaxy>& Galaxies, vector<string> file)
{
  int NumberofGalaxies = stringToint(file[0]);
  int linePointer=1;
  for (int i = 0; i < NumberofGalaxies; i++)
  {
    vector<string> tokens;
    seperating_line(file[linePointer],tokens);
    string galaxy_name=tokens[0];
    int number_of_planets=stringToint(file[linePointer]);
    int number_of_lines=3*number_of_planets-2;
    Galaxies.push_back(Galaxy(galaxy_name,vector<string>(file.begin()+linePointer+1,file.begin()+linePointer+number_of_lines)));
    linePointer+=number_of_lines+1;
  }

}
vector<string> ToVector(string filename)
{
  vector<string> save;
  ifstream myfile;
  myfile.open(filename);
  while(true)
  {
    string temp;
    getline(myfile, temp);
    if (temp == "")
      break;
    // seperating_line(temp, save);
    save.push_back(temp);
  }
  myfile.close();
  return save;
}
int main()
{
  vector<planet> planets;
  vector<Galaxy> galaxies;
  vector<string> print = DividingUniverse(planets, galaxies, ToVector("topology.cfg"));
}
