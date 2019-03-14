#ifndef ALBUM_H_
#define ALBUM_H_

#include <vector>
#include <string>
#include "music.h"
#include "music_container.h"
#include "basics.h"
#include "rate.h"

class Artist;
class User;

class MusicAlbum : public MusicContainer
{
public:
	MusicAlbum(std::string _name, Artist* _artist);
	~MusicAlbum();
	Artist* get_artist() { return artist; }
	std::string get_name() { return name; }
	std::string get_complete_name();
	void rate(int rating, User* user);
	int get_user_rate(User* user);
	int get_average_rate();
	int get_editor_average_rate();

private:
	std::string name;
	Artist* artist;
	std::vector<Rate*> ratings;
};







#endif