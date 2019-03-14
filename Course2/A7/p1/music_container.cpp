#include "music_container.h"


using namespace std;

MusicContainer::MusicContainer()
{
	
}

List MusicContainer::get_musics_names()
{
	List result;
	for (int i = 0; i < musics.size(); i++)
		result.push_back(musics[i]->get_name());
	return result;
}

List MusicContainer::get_musics_addresses()
{
	List result;
	for (int i = 0; i < musics.size(); i++)
		result.push_back(musics[i]->get_address());
	return result;
}

void MusicContainer::add_musics(vector<Music*> adding_musics)
{
	musics.insert(musics.begin(), adding_musics.begin(), adding_musics.end());
}

void MusicContainer::remove_music(string input)
{
	for (int i = 0; i < musics.size(); i++)
		if (musics[i]->get_name() == input)
			musics.erase(musics.begin() + i);
}

void MusicContainer::clear()
{
	int a = musics.size();
	for (int i = 0; i < a; i++)
		musics.pop_back();
}

void MusicContainer::get_musics(std::vector<Music*>& result)
{
	for (int i = 0; i < musics.size(); i++)
		result.push_back(musics[i]);
}