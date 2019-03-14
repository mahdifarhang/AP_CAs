#ifndef BROWSER_H_
#define BROWSER_H_

#include "music_lib.h"
#include "user.h"
#include "artist.h"
#include "basics.h"
#include "playlist.h"
#include "queue.h"
#include <string>
#include <vector>

enum BrowserState { HOME, PLAYLISTS, PLAYLIST, QUEUE, LIBRARY, ARTIST, ALBUM, MUSIC };

class Browser
{
public:
	Browser();
	void login(User*);
	void go_home();
	void go_playlist();
	void go_library();
	void go_album();
	void go_artist();
	void search_musics(std::string name, List& result);
	void search_albums(std::string name, List& result);
	void search_playlists(std::string name, List& result);
	void select(Artist* artist);
	void select(MusicAlbum* album);
	void select(Music* music);
	void select(Playlist* playlist);
	void select(std::string name);
	List list(List artists);
	List list_of_musics();
	List list_of_albums();
	List list_of_playlists();
	Queue* play();
	List get_artists_names(List result);
	std::string get_artist();
	std::string get_album();
	void add_to(std::string input);
	void go_to_playlist_or_queue(std::string input);
	void create_playlist(std::string input);
	void clear_playlist(std::string input);
	void remove_music(std::string input);
	void order_item(std::string music_name, int index);
	void rate(int i);
	int get_my_rate();
	int get_average_rate();
	int get_editor_average_rate();
	void add_music(std::string name, std::string path);
	void add_album(std::string artist_name, std::string album_name);
	std::string get_name();
	std::string get_complete_name();
	void validate();
	bool is_admin();
	Queue* get_current_queue();


private:
	bool check_in_home();
	bool check_in_music();
	bool check_in_album();
	void deselect_things();

	User* current_user;
	BrowserState state;
	Music* selected_music;
	MusicAlbum* selected_album;
	Artist* selected_artist;
	Playlist* selected_playlist;
	MusicLib music_lib;
};


#endif