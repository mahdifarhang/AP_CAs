#ifndef USER_H_
#define USER_H_

#include <string>
#include <vector>
#include "basics.h"
#include "album.h"
#include "music.h"
#include "queue.h"
#include "playlist.h"

class User
{
public:
	User(UserData _userdata, std::string _password);
	~User();
	virtual bool is_validated();
	virtual void validate();
	UserData get_userdata();
	virtual UserType get_usertype();
	bool check_correct_password(std::string _password);
	Playlist* select_playlist(std::string name);
	List get_playlists_names();
	bool add_to_playlist_or_queue(std::string input, std::vector<Music*> musics);
	Playlist* get_playlist(std::string input);
	void create_playlist(std::string input);
	void clear_playlist(std::string input);
	Queue* get_queue() { return &queue; }
	void order_item(std::string music_name, int index, std::string playlist_name);

protected:
	std::string firstname;
	std::string lastname;
	std::string username;
	std::string password;
	bool validated;
	Queue queue;
	std::vector<Playlist*> playlists;
	
};

#endif