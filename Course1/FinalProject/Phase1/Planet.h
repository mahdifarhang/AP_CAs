#ifndef PLANET_H
#define PLANET_H


#include <vector>
#include <string>

class Planet
{
public:
  Planet(string, vector<Planet*>, Galaxy*);
  int LocalDistance(Planet);
  int DistanceToGate();
private:
  string name;
  vector<Planet*> neighbors;
  string BaseGalaxy;
};




#endif
