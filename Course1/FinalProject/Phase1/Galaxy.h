#ifndef GALAXIES_H
#define GALAXIES_H

#include <vector>
#include <string>
#include "Planet.h"

class Galaxy
{
public:
  Galaxy(string, vector<string>);
private:
  string Galaxyname;
  Planet* Gate;
  vector<Planet*> ListofPlanets;
};

int GlobalDistance(Planet, Planet);



#endif
