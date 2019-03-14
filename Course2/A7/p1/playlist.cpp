#include "playlist.h"

#include "album.h"
#include "exceptions.h"

using namespace std;

Playlist::Playlist(std::string input) : MusicContainer()
{
	name = input;
}


List Playlist::get_albums()
{
	List result;
	for (int i = 0; i < musics.size(); i++)
	{
		result.push_back((musics[i]->get_album())->get_name());
		for (int i = 0; i < result.size() - 1; i++)
		{
			if (result[result.size() - 1] == result[i])
			{
				result.pop_back();
				break;
			}
		}
	}
}

void Playlist::order_item(string music_name, int index)
{
	index --;
	if (index < 0 || index > musics.size() - 1)
		throw InvalidArguments("can't change the order in this way!");
	bool flag = false;
	for (int i = 0; i < musics.size(); i++)
	{
		if (musics[i]->get_name() == music_name)
		{
			Music* temp = musics[i];
			if (i > index)
			{
				musics.erase(musics.begin() + i);
				musics.insert(musics.begin() + index, temp);
			}
			else if (i < index)
			{
				musics.erase(musics.begin() + i);
				musics.insert(musics.begin() + index + 1, temp);
			}
			flag = true;
			break;
		}
	}
	if (flag == false)
		throw ItemDoesNotExist("no music found!");
}