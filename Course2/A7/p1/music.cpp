#include "music.h"

#include "album.h"
#include "artist.h"
#include "user.h"
#include "exceptions.h"

using namespace std;


Music::Music(std::string _name, Artist* _artist, string path)
{
	name = _name;
	album = NULL;
	artist = _artist;
	file_path = path;
}

Music::~Music()
{
	for (int i = 0; i < ratings.size(); i++)
		delete ratings[i];
}

string Music::get_complete_name()
{
	return this->get_artist()->get_userdata().username + "_" + this->get_album()->get_name() + "_" + this->get_name();
}



void Music::set_album(MusicAlbum* setting_album)
{
	album = setting_album;
}

void Music::rate(int rating, User* user)
{
	Rate* temp = new Rate(user, rating);
	ratings.push_back(temp);
}

int Music::get_user_rate(User* user)
{
	for (int i = 0; i < ratings.size(); i++)
	{
		if (ratings[i]->get_user()->get_userdata().username == user->get_userdata().username)
			return ratings[i]->get_rate();
	}
}

int Music::get_average_rate()
{
	int sum = 0;
	int count = 0;
	for (int i = 0; i < ratings.size(); i++)
	{
		if (ratings[i]->get_user()->get_usertype() != U_EDITOR)
		{
			sum += ratings[i]->get_rate();
			count++;
		}
	}
	if (count == 0)
		throw Exception("no users voted to this item yet. bet the first to do it!");
	return sum / count;
}

int Music::get_editor_average_rate()
{
	int sum = 0;
	int count = 0;
	for (int i = 0; i < ratings.size(); i++)
	{
		if (ratings[i]->get_user()->get_usertype() == U_EDITOR)
		{
			sum += ratings[i]->get_rate();
			count++;
		}
	}
	if (count == 0)
		throw Exception("no users voted to this item yet. bet the first to do it!");
	return sum / count;
}