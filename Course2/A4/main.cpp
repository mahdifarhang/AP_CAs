#include "tournament.h"
#include <map>
#include <string>

using namespace std;

#define GOALKEEPER "goalkeeper"
#define DEFENDER "defener"
#define MIDFIELDER "midfielder"
#define STRIKER "striker"

int main(){
	Tournament ap_cup;

	map<string, int> fans_in_stadium;
	fans_in_stadium.insert(pair <string, int> ("Camp Nou", 90000));
	fans_in_stadium.insert(pair <string, int> ("Santiago Bernabeu", 10000));
	fans_in_stadium.insert(pair <string, int> ("Emirates Stadium", 4000));
	fans_in_stadium.insert(pair <string, int> ("Anfield", 5000));

	string team_name = "Barcelona";
	ap_cup.add_team(team_name, "Camp Nou", 100000, 5, fans_in_stadium);
	ap_cup.add_player(team_name, "Ter Stegen", 85, GOALKEEPER);
	ap_cup.add_player(team_name, "Sergi Roberto", 81, DEFENDER);
	ap_cup.add_player(team_name, "Pique", 87, DEFENDER);
	ap_cup.add_player(team_name, "Umtiti", 83, DEFENDER);
	ap_cup.add_player(team_name, "Alba", 85, DEFENDER);
	ap_cup.add_player(team_name, "Rakitic", 87, MIDFIELDER);
	ap_cup.add_player(team_name, "Busquets", 86, MIDFIELDER);
	ap_cup.add_player(team_name, "Iniesta", 87, MIDFIELDER);
	ap_cup.add_player(team_name, "Suarez", 92, STRIKER);
	ap_cup.add_player(team_name, "Messi", 93, STRIKER);
	ap_cup.add_player(team_name, "Dembele", 83, STRIKER);


	team_name = "Real Madrid";
	fans_in_stadium["Camp Nou"] = 15000;
	fans_in_stadium["Santiago Bernabeu"] = 70000;
	fans_in_stadium["Emirates Stadium"] = 5000;
	fans_in_stadium["Anfield"] = 7500;
	ap_cup.add_team(team_name, "Santiago Bernabeu", 80000, 5, fans_in_stadium);
	ap_cup.add_player(team_name, "Navas", 85, GOALKEEPER);
	ap_cup.add_player(team_name, "Ramos", 90, DEFENDER);
	ap_cup.add_player(team_name, "Varane", 85, DEFENDER);
	ap_cup.add_player(team_name, "Marcelo", 87, DEFENDER);
	ap_cup.add_player(team_name, "Carvajal", 84, DEFENDER);
	ap_cup.add_player(team_name, "Casemiro", 85, MIDFIELDER);
	ap_cup.add_player(team_name, "Kroos", 90, MIDFIELDER);
	ap_cup.add_player(team_name, "Modric", 89, MIDFIELDER);
	ap_cup.add_player(team_name, "Isco", 89, MIDFIELDER);
	ap_cup.add_player(team_name, "Benzema", 86, STRIKER);
	ap_cup.add_player(team_name, "Ronaldo", 94, STRIKER);


	team_name = "Arsenal";
	fans_in_stadium["Camp Nou"] = 3000;
	fans_in_stadium["Santiago Bernabeu"] = 2000;
	fans_in_stadium["Emirates Stadium"] = 54000;
	fans_in_stadium["Anfield"] = 10000;
	ap_cup.add_team(team_name, "Emirates Stadium", 60000, 3, fans_in_stadium);
	ap_cup.add_player(team_name, "Ospina", 79, GOALKEEPER);
	ap_cup.add_player(team_name, "Mertesacker", 81, DEFENDER);
	ap_cup.add_player(team_name, "Koscielny", 84, DEFENDER);
	ap_cup.add_player(team_name, "Bellerin", 81, DEFENDER);
	ap_cup.add_player(team_name, "Monreal", 80, DEFENDER);
	ap_cup.add_player(team_name, "Ozil", 88, MIDFIELDER);
	ap_cup.add_player(team_name, "Cazorla", 83, MIDFIELDER);
	ap_cup.add_player(team_name, "Ramsey", 82, MIDFIELDER);
	ap_cup.add_player(team_name, "Lacazette", 85, STRIKER);
	ap_cup.add_player(team_name, "Giroud", 82, STRIKER);
	ap_cup.add_player(team_name, "Sanchez", 89, STRIKER);


	team_name = "Liverpool";
	fans_in_stadium["Camp Nou"] = 3000;
	fans_in_stadium["Santiago Bernabeu"] = 2000;
	fans_in_stadium["Emirates Stadium"] = 10000;
	fans_in_stadium["Anfield"] = 48000;
	ap_cup.add_team(team_name, "Anfield", 54000, 4, fans_in_stadium);
	ap_cup.add_player(team_name, "Mignolet", 80, GOALKEEPER);
	ap_cup.add_player(team_name, "Matip", 83, DEFENDER);
	ap_cup.add_player(team_name, "Lovren", 81, DEFENDER);
	ap_cup.add_player(team_name, "Alexander-Arnold", 68, DEFENDER);
	ap_cup.add_player(team_name, "Moreno", 76, DEFENDER);
	ap_cup.add_player(team_name, "Henderson", 82, MIDFIELDER);
	ap_cup.add_player(team_name, "Wijnaldum", 82, MIDFIELDER);
	ap_cup.add_player(team_name, "Coutinho", 86, MIDFIELDER);
	ap_cup.add_player(team_name, "Firmino", 83, STRIKER);
	ap_cup.add_player(team_name, "Mane", 82, STRIKER);
	ap_cup.add_player(team_name, "Salah", 82, STRIKER);


	// adding other teams

	ap_cup.simulate();

	ap_cup.print_tournament_results();
	ap_cup.print_round_results(1);
	ap_cup.print_team_results("Barcelona");

	return 0;
}
