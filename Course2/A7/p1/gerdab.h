#ifndef GERDAB_H_
#define GERDAB_H_

#include <string>
#include "basics.h"
#include "browser.h"
#include "player.h"
#include "register.h"

enum State { LoginMode, BrowserMode, PlayMode };

class Gerdab
{
public:
	Gerdab();
	void enter_browser_mode();
	void go_home();
	void go_playList();
	void go_library();
	void go_album();
	void go_artist();
	List search(std::string name);
	void select(std::string name);
	List list();
	List list_of_musics();
	List list_of_albums();
	List list_of_playlists();
	List list_of_artists();
	void play();
	void add_to(std::string input);
	void go_to(std::string input);
	void create_playlist(std::string input);
	void clear_playlist(std::string input);
	void remove_music(std::string input);
	void order_item(std::string music_name, int index);
	void rate(int i);
	std::string get_artist();
	std::string get_album();
	std::string get_name();
	std::string get_complete_name();
	int get_rate();
	int get_user_rate();
	int get_critic_rate();
	void enter_player_mode();
	void next_music();
	void previous_music();
	void pause();
	void repeat_one();
	void repeat();
	void signup(UserData userdata, std::string password);
	void login(std::string username, std::string password);
	void add_music(std::string music_name, std::string file_path);
	void add_album(std::string artist_name, std::string album_name);
	void validate();
	UserData get_user_data(std::string name);
	void verify_user(std::string input);

private:
	State current_state;
	Register registering;
	Browser browser;
	Player player;

	bool check_in_browser();
	bool check_in_register();
	bool check_in_player();

};


#endif