#include "browser.h"
#include "exceptions.h"

using namespace std;


Browser::Browser()
{

}

void Browser::login(User* temp)
{
	state = HOME;
	current_user = temp;
}

bool Browser::check_in_home()
{
	if (state != HOME)
	{
		throw MethodNotAvailable("not in home!");
		return false;
	}
	return true;
}

bool Browser::check_in_music()
{
	if (state != MUSIC || selected_music == NULL)
	{
		throw MethodNotAvailable("not in any music!");
		return false;
	}
	return true;
}

bool Browser::check_in_album()
{
	if (state != ALBUM || selected_album == NULL)
	{
		throw MethodNotAvailable("not in any album!");
		return false;
	}
	return true;
}

void Browser::deselect_things()
{
	selected_music = NULL;
	selected_album = NULL;
	selected_artist = NULL;
	selected_playlist = NULL;
}

void Browser::go_home()
{
	state = HOME;
	deselect_things();
}

void Browser::go_playlist()
{
	check_in_home();
	state = PLAYLISTS;
}

void Browser::go_library()
{
	check_in_home();
	state = LIBRARY;
}

void Browser::go_album()
{
	check_in_music();
	Music* temp = selected_music;
	select(temp->get_album());
}

void Browser::go_artist()
{
	try
	{
		check_in_music();
	}
	catch (Exception* e)
	{
		try
		{
			check_in_album();
		}
		catch (Exception* e)
		{
			throw MethodNotAvailable("not in album or music!");
		}
		//we are in an album.
		MusicAlbum* temp = selected_album;
		select(temp->get_artist());
	}
	//we are in a music.
	Music* temp = selected_music;
	select(temp->get_artist());
}

void Browser::search_musics(string name, List& result)
{
	music_lib.search_musics(name, result);
}

void Browser::search_albums(std::string name, List& result)
{
	music_lib.search_albums(name, result);
}

void Browser::search_playlists(std::string name, List& result)
{
	List temp = current_user->get_playlists_names();
	string check;
	for (int i = 0; i < temp.size(); i++)
	{
		check = current_user->get_userdata().username + "_" + temp[i];
		if (exists_in_string(check, name))
			result.push_back(check);
	}
}

void Browser::select(Artist* artist)
{
	if (artist->is_validated())
	{
		state = ARTIST;
		deselect_things();
		selected_artist = artist;
	}
}

void Browser::select(MusicAlbum* album)
{
	state = ALBUM;
	deselect_things();
	selected_album = album;
}

void Browser::select(Music* music)
{
	state = MUSIC;
	deselect_things();
	selected_music = music;
}

void Browser::select(Playlist* playlist)
{
	state = PLAYLIST;
	deselect_things();
	selected_playlist = playlist;
}

void Browser::select(string name)
{
	MusicAlbum* temp1 = music_lib.select_album(name);
	Music* temp2 = music_lib.select_music(name);
	Playlist* temp3 = current_user->select_playlist(name);
	if (temp1 != NULL)
		select(temp1);
	else if (temp2 != NULL)
		select(temp2);
	else if (temp3 != NULL)
		select(temp3);
	else
		throw ItemDoesNotExist("nothing found to be selected!");
}

List Browser::list(List artists)
{
	List temp;
	if (state == HOME)
	{
		temp.push_back("playlists");
		temp.push_back("library");
		return temp;
	}
	else if (state == LIBRARY)
		return artists;
	else if (state == ALBUM)
		return selected_album->get_musics_names();
	else if (state == ARTIST)
		music_lib.get_albums(selected_artist);
	else if (state == PLAYLIST)
		return selected_playlist->get_musics_names();
	else
		throw MethodNotAvailable();
}

List Browser::list_of_musics()
{
	if (state == LIBRARY)
		return music_lib.get_all_musics_names();
	else if (state == ALBUM)
		return selected_album->get_musics_names();
	else if (state == ARTIST)
		return music_lib.get_all_musics_names_from_artist(selected_artist);
	else if (state == PLAYLIST)
		return selected_playlist->get_musics_names();
	else
		throw MethodNotAvailable("no musics available!");
}

List Browser::list_of_albums()
{
	if (state == LIBRARY)
		return music_lib.get_all_albums_names();
	else if (state == PLAYLIST)
		return selected_playlist->get_albums();
	else if (state == ARTIST)
		return music_lib.get_albums(selected_artist);
	else
		throw MethodNotAvailable("no albums available!");
}

List Browser::list_of_playlists()
{
	if (state == PLAYLISTS)
		return current_user->get_playlists_names();
	else
		throw MethodNotAvailable("no playlists here!");
}

Queue* Browser::play()
{
	vector<Music*> temp;
	if (state == MUSIC)
		temp.push_back(selected_music);
	else if (state == ALBUM)
		selected_album->get_musics(temp);
	else if (state == PLAYLIST)
		selected_playlist->get_musics(temp);
	else if (state == ARTIST)
		temp = music_lib.get_all_musics_from_artist(selected_artist);
	else
		throw MethodNotAvailable("not in any music, album, playlist or artist while in browse mode!");
	get_current_queue()->add_musics(temp);
	return get_current_queue();
}

List Browser::get_artists_names(List result)
{
	if (state == LIBRARY)
		return result;
	else
		throw MethodNotAvailable("artists aren't here!");
}

string Browser::get_artist()
{
	if (state == MUSIC)
		return selected_music->get_artist()->get_userdata().username;
	else if (state == ALBUM)
		return selected_album->get_artist()->get_userdata().username;
	else
		throw MethodNotAvailable("doesn't have an artist!");
}

string Browser::get_album()
{
	check_in_music();
	return selected_music->get_album()->get_name();
}

void Browser::add_to(string input)
{
	vector<Music*> musics;
	if (state == MUSIC)
		musics.push_back(selected_music);
	else if (state == ALBUM)
		selected_album->get_musics(musics);
	else
		throw MethodNotAvailable();
	if (musics.size() == 0)
		throw ItemDoesNotExist("no musics found");
	if (!(current_user->add_to_playlist_or_queue(input, musics) || music_lib.add_to_album(input, musics[0], current_user)))
		throw ItemDoesNotExist("no musics or albums found!");
}

void Browser::go_to_playlist_or_queue(string input)
{
	if (input == "queue")
	{
		deselect_things();
		state = QUEUE;
	}
	else
	{
		Playlist* temp = current_user->get_playlist(input);
		if (temp == NULL)
			throw ItemDoesNotExist();
		deselect_things();
		state = PLAYLIST;
		selected_playlist = temp;
	}
}

void Browser::create_playlist(string input)
{
	current_user->create_playlist(input);
}

void Browser::clear_playlist(string input)
{
	current_user->clear_playlist(input);
}

void Browser::remove_music(string input)
{
	check_in_music();
	if (state == ALBUM)
		music_lib.remove_music(input, selected_album, current_user);
	else if (state == PLAYLIST)
		music_lib.remove_music(input, selected_playlist, current_user);
}

void Browser::order_item(string music_name, int index)
{
	if (state != PLAYLIST)
		throw MethodNotAvailable("you aren't in a playlist!");
	current_user->order_item(music_name, index, selected_playlist->get_name());
}

void Browser::rate(int rating)
{
	if (rating > 10 || rating < 0)
		throw InvalidArguments("not in range!");
	if (state == MUSIC)
		selected_music->rate(rating, current_user);
	else if (state == ALBUM)
		selected_album->rate(rating, current_user);
	else
		throw MethodNotAvailable("not in music or album!");
}

int Browser::get_my_rate()
{
	if (state == MUSIC)
		return selected_music->get_user_rate(current_user);
	else if (state == ALBUM)
		return selected_album->get_user_rate(current_user);
	else
		throw MethodNotAvailable("not in music or album!");
}

int Browser::get_average_rate()
{
	if (state == MUSIC)
		return selected_music->get_average_rate();
	else if (state == ALBUM)
		return selected_album->get_average_rate();
	else
		throw MethodNotAvailable("not in music or album!");
}

int Browser::get_editor_average_rate()
{
	if (state == MUSIC)
		return selected_music->get_editor_average_rate();
	else if (state == ALBUM)
		return selected_album->get_editor_average_rate();
	else
		throw MethodNotAvailable("not in music or album!");
}

void Browser::add_music(string name, string path)
{
	if (current_user->get_usertype() == U_ARTIST)
		music_lib.add_music(name, path, current_user);
	else
		throw NotAuthorized("artists can add musics!");
}

void Browser::add_album(string artist_name, string album_name)
{
	if (current_user->get_usertype() == U_ARTIST)
	{
		if (current_user->get_userdata().username == artist_name)
			music_lib.add_album(album_name, current_user);
		else
			throw NotAuthorized("artist name doesn't match!");
	}
	else
		throw NotAuthorized("artists can add albums!");
}

string Browser::get_name()
{
	if (state == MUSIC)
		return selected_music->get_name();
	else if (state == PLAYLIST)
		return selected_playlist->get_name();
	else if (state == ARTIST)
		return selected_artist->get_userdata().username;
	else if (state == ALBUM)
		return selected_album->get_name();
	else if (state == HOME)
		return "HOME";
	else if (state == LIBRARY)
		return "LIBRARY";
	else if (state == PLAYLISTS)
		return "PLAYLISTS";
	else if (state == QUEUE)
		return "QUEUE";
}

string Browser::get_complete_name()
{
	if (state == HOME)
		return "HOME";
	else if (state == PLAYLISTS)
		return "PLAYLISTS";
	else if (state == LIBRARY)
		return "LIBRARY";
	else if (state == QUEUE)
		return "QUEUE";
	else if (state == MUSIC)
		return selected_music->get_complete_name();
	else if (state == ALBUM)
		return selected_album->get_complete_name();
	else if (state == PLAYLIST)
		return current_user->get_userdata().username + "_" + selected_playlist->get_name();
	else if (state == ARTIST)
		return selected_artist->get_userdata().username;
}

void Browser::validate()
{
	if (current_user->get_usertype() != U_ADMIN)
		throw NotAuthorized("only admin can validate!");
	if (state == ARTIST)
		selected_artist->validate();
	else
		throw MethodNotAvailable("can't be validated!");
}

bool Browser::is_admin()
{
	if (current_user->get_usertype() == U_ADMIN)
		return true;
	return false;
}

Queue* Browser::get_current_queue()
{
	return current_user->get_queue();
}