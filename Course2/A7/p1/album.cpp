#include "album.h"

#include "artist.h"
#include "user.h"
#include "exceptions.h"

using namespace std;

MusicAlbum::MusicAlbum(string _name, Artist* _artist) : MusicContainer()
{
	name = _name;
	artist = _artist;
}

MusicAlbum::~MusicAlbum()
{
	for (int i = 0; i < ratings.size(); i++)
		delete ratings[i];
}

string MusicAlbum::get_complete_name()
{
	this->get_artist()->get_userdata().username + "_" + this->get_name();
}

void MusicAlbum::rate(int rating, User* user)
{
	Rate* temp = new Rate(user, rating);
	ratings.push_back(temp);
}

int MusicAlbum::get_user_rate(User* user)
{
	for (int i = 0; i < ratings.size(); i++)
	{
		if (ratings[i]->get_user()->get_userdata().username == user->get_userdata().username)
			return ratings[i]->get_rate();
	}
}

int MusicAlbum::get_average_rate()
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

int MusicAlbum::get_editor_average_rate()
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
