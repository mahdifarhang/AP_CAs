#include "tournament.h"

using namespace std;

Tournament::Tournament()
{

}
int Tournament::add_team(string team_name, string stadium_name, int capacity, float impact/*, map <string, int> fans_in_stadium*/)
{
  for (unsigned int i = 0; i < teams.size(); i++)
    if (teams[i].name == team_name)
      return 0;
  Team temp(team_name, stadium_name, capacity, impact);
  teams.push_back(temp);
  return 0;
}
void Tournament::add_player(string team_name, string player_name, string player_power, string player_position)
{

}
void Tournament::simulate()
{

}
void Tournament::print_round_result(int round_number)
{

}
void Tournament::print_tournament_result()
{

}
void Tournament::print_team_result()
{

}
