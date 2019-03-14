#ifndef TEAM_H_
#define TEAM_H_

#include <vector>
#include <string>
#include <map>
#include "player.h"

class Team
{
public:
	Team(std::string, std::string, int, float);
private:
	std::string name;
	std::string stadium;
	int capacity;
	float impact;
	std::vector<Player> goalkeepers;
	std::vector<Player> defenders;
	std::vector<Player> midfielders;
	std::vector<Player> strikers;
	void add_player(std::string name, std::string power, std::string post);

};







#endif
