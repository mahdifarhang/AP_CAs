#ifndef MUSIC_CONTAINER_H_
#define MUSIC_CONTAINER_H_

#include <vector>
#include "music.h"
#include "basics.h"

class MusicContainer
{
public:
	MusicContainer();
	List get_musics_names();
	List get_musics_addresses();
	void add_musics(std::vector<Music*> adding_musics);
	void remove_music(std::string input);
	void clear();
	void get_musics(std::vector<Music*>& result);
	int size() { return musics.size(); }
protected:
	std::vector<Music*> musics;
};









#endif