#ifndef MUSIC_LIB_H_
#define MUSIC_LIB_H_

#include "music.h"
#include "album.h"
#include "basics.h"
#include <vector>
#include <string>

class Artist;
class User;
class Playlist;

class MusicLib
{
public:
	MusicLib();
	~MusicLib();
	void search_musics(std::string name, List& result);
	void search_albums(std::string name, List& result);
	MusicAlbum* select_album(std::string name);
	Music* select_music(std::string name);
	List get_albums(Artist* aritst);
	List get_all_musics_names();
	List get_all_musics_names_from_artist(Artist* artist);
	std::vector<Music*> get_all_musics_from_artist(Artist* artist);
	List get_all_albums_names();
	List get_album_names_from_artist(Artist* artist);
	bool add_to_album(std::string input, Music* adding_musics, User* current_user);
	void remove_music(std::string input, MusicAlbum* album, User* current_user); //removing from an album.
	void remove_music(std::string input, Playlist* current_playlist, User* current_user); //removing from a plyaylist.
	void add_music(std::string name, std::string path, User* artist);
	void add_album(std::string name, User* artist);
private:
	std::vector<MusicAlbum*> albums;
	std::vector<Music*> musics;
};






#endif
