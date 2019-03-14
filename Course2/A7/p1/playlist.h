#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "music_container.h"
#include <string>
#include "basics.h"

class Playlist : public MusicContainer
{
public:
	Playlist(std::string input);
	std::string get_name() { return name; }
	List get_albums();
	void order_item(std::string music_name, int index);
private:
	std::string name;
};





#endif