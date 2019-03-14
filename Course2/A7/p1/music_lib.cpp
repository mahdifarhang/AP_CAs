#include "music_lib.h"

#include "artist.h"
#include "user.h"
#include "exceptions.h"
#include "playlist.h"

using namespace std;

MusicLib::MusicLib()
{
	
}

MusicLib::~MusicLib()
{
	for (int i = 0; i < musics.size(); i++)
		delete musics[i];
	for (int i = 0; i < albums.size(); i++)
		delete albums[i];
}

void MusicLib::search_musics(string name, List& result)
{
	string check;
	for (int i = 0; i < musics.size(); i++)
	{
		check = musics[i]->get_artist()->get_userdata().username + "_" + musics[i]->get_album()->get_name() + "_" + musics[i]->get_name();
		if (exists_in_string(check,name))
			result.push_back(check);
	}
}

void MusicLib::search_albums(string name, List& result)
{
	string check;
	for (int i = 0; i < albums.size(); i++)
	{
		check = albums[i]->get_artist()->get_userdata().username + "_" + albums[i]->get_name();
		if (exists_in_string(check, name))
			result.push_back(check);
	}
}

MusicAlbum* MusicLib::select_album(string name)
{
	for (int i = 0; i < albums.size(); i++)
	{
		if (albums[i]->get_name() == name)
			return albums[i];
	}
	return NULL;
}

Music* MusicLib::select_music(string name)
{
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_name() == name)
			return musics[i];
	}
	return NULL;
}

List MusicLib::get_albums(Artist* artist)
{
	List result;
	for (int i = 0; i < albums.size(); i++)
	{
		if (albums[i]->get_artist() == artist)
			result.push_back(albums[i]->get_name());
	}
	return result;
}

List MusicLib::get_all_musics_names()
{
	List result;
	for (int i = 0; i < musics.size(); i++)
		result.push_back(musics[i]->get_name());
	return result;
}

List MusicLib::get_all_musics_names_from_artist(Artist* artist)
{
	List result;
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_artist() == artist)
			result.push_back(musics[i]->get_name());
	}	
	return result;
}

vector<Music*> MusicLib::get_all_musics_from_artist(Artist* artist)
{
	vector<Music*> result;
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_artist() == artist)
			result.push_back(musics[i]);
	}
	return result;
}

List MusicLib::get_all_albums_names()
{
	List result;
	for (int i = 0; i < albums.size(); i++)
		result.push_back(albums[i]->get_name());
	return result;
}

List MusicLib::get_album_names_from_artist(Artist* artist)
{
	List result;
	for (int i = 0; i < albums.size(); i++)
	{
		if (albums[i]->get_artist() == artist)
			result.push_back(albums[i]->get_name());
	}
	return result;
}

bool MusicLib::add_to_album(string input, Music* adding_music, User* current_user)
{
	for (int i = 0; i < albums.size(); i++)
	{
		if (albums[i]->get_name() == input)
		{
			if (adding_music->get_album() != NULL)
				return false;
			if (current_user != albums[i]->get_artist() || current_user != adding_music->get_artist())
				throw NotAuthorized("You aren't the artist!");
			vector<Music*> temp;
			temp.push_back(adding_music);
			albums[i]->add_musics(temp);
			adding_music->set_album(albums[i]);
			return true;
		}
	}
	return false;
}

void MusicLib::remove_music(string input, MusicAlbum* album, User* current_user) // from album
{
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_complete_name() == input)
		{
			if (current_user == musics[i]->get_artist())
			{
				musics[i]->set_album(NULL);
				album->remove_music(input);
				return;
			}
			else
				throw NotAuthorized("you aren't the artist!");
		}
	}
	throw ItemDoesNotExist("no music found!");
}

void MusicLib::remove_music(string input, Playlist* current_playlist, User* current_user) // from playlist
{
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_complete_name() == input)
		{
			for (int i = 0; i < current_playlist->get_musics_names().size(); i++)
			{
				if (input == current_playlist->get_musics_names()[i])
					current_playlist->remove_music(input);
			}
			throw ItemDoesNotExist("music does'n belong to this playlist!");
		}
	}
	throw ItemDoesNotExist("no musics found!");
	//its not possible that the user doesn't own the playlist.
}

void MusicLib::add_music(string name, string path, User* artist)
{
	Music* temp = new Music(name, (Artist*)artist, path);
	musics.push_back(temp);
}

void MusicLib::add_album(string name, User* artist)
{
	MusicAlbum* temp = new MusicAlbum(name, (Artist*)artist);
	albums.push_back(temp);
}