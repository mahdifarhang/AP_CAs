#ifndef MUSIC_H_
#define MUSIC_H_

#include <string>
#include <vector>
#include "rate.h"

class MusicAlbum;
class Artist;
class User;

class Music
{
public:
	Music(std::string _name, Artist* _artist, std::string file_path);
	~Music();
	MusicAlbum* get_album() { return album; }
	Artist* get_artist() { return artist; }
	std::string get_name() { return name; }
	std::string get_address() { return file_path; }
	std::string get_complete_name();
	void set_album(MusicAlbum* setting_album);
	void rate(int rating, User* user);
	int get_user_rate(User* user);
	int get_average_rate();
	int get_editor_average_rate();

private:
	std::string name;
	MusicAlbum* album;
	Artist* artist;
	std::string file_path;
	std::vector<Rate*> ratings;


};








#endif