#include "user.h"
#include "exceptions.h"

using namespace std;

User::User(UserData _userdata, string _password)
{
	firstname = _userdata.firstname;
	lastname = _userdata.lastname;
	username = _userdata.username;
	password = _password;
	validated = true;
}

User::~User()
{
	for (int i = 0; i < playlists.size(); i++)
		delete playlists[i];
}

bool User::is_validated()
{
	throw MethodNotAvailable("users don't get validated!");
}

void User::validate()
{
	throw MethodNotAvailable("users don't get validated!");
}

bool User::check_correct_password(string _password)
{
	if (password == _password)
		return true;
	return false;
}

UserData User::get_userdata()
{
	UserData temp;
	temp.firstname = firstname;
	temp.lastname = lastname;
	temp.username = username;
	temp.userType = get_usertype();
	return temp;
}

UserType User::get_usertype()
{
	return U_NORMAL;
}

Playlist* User::select_playlist(string name)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (playlists[i]->get_name() == name)
			return playlists[i];
	}
	return NULL;
}

List User::get_playlists_names()
{
	List result;
	for (int i = 0; i < playlists.size(); i++)
	{
		result.push_back(playlists[i]->get_name());
	}
	return result;
}

bool User::add_to_playlist_or_queue(std::string input, std::vector<Music*> musics)
{
	if (input == "queue")
	{
		queue.add_musics(musics);
		return true;
	}
	else
	{
		for (int i = 0; i < playlists.size(); i++)
		{
			if (playlists[i]->get_name() == input)
			{
				playlists[i]->add_musics(musics);
				return true;
			}
		}
		return false;
	}
}

Playlist* User::get_playlist(string input)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (playlists[i]->get_name() == input)
			return playlists[i];
	}
	return NULL;
}

void User::create_playlist(string input)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (playlists[i]->get_name() == input)
			throw AlreadyExists();
	}
	Playlist* temp = new Playlist(input);
	playlists.push_back(temp);
}

void User::clear_playlist(string input)
{
	bool flag = false;
	for (int i = 0; i < playlists.size(); i++)
	{
		if (playlists[i]->get_name() == input)
		{
			playlists[i]->clear();
			flag = true;
			break;
		}
	}
	if (flag == false)
		throw ItemDoesNotExist();
}

void User::order_item(string music_name, int index, string playlist_name)
{
	for (int i = 0; i < playlists.size(); i++)
		if (playlists[i]->get_name() == playlist_name)
		{
			playlists[i]->order_item(music_name, index);
			break;
		}
}
