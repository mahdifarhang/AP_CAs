#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_
#include <string>
#include <vector>

class Tournament
{
public:
  Tournamnet();
  void add_team(std::string, std::string, int, float/*, map <std::string, int>*/);
  void add_player(std::string, std::string, std::string, std::string);
  void simulate();
  void print_round_result(int);
  void print_tournament_result();
  void print_team_result();
private:
  std::vector<Team> teams;



};


#endif
