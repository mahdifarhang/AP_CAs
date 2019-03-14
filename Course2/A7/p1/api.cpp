#include "api.h"

using namespace std;

GerdabifyAPI::GerdabifyAPI()
{

}

void GerdabifyAPI::enterBrowserMode()
{
	gerdab.enter_browser_mode();
}

void GerdabifyAPI::goToHome()
{
	gerdab.go_home();
}

void GerdabifyAPI::goToPlayList()
{
	gerdab.go_playList();
}

void GerdabifyAPI::goToLibrary()
{
	gerdab.go_library();
}

void GerdabifyAPI::goToAlbum()
{
	gerdab.go_album();
}

void GerdabifyAPI::goToArtist()
{
	gerdab.go_artist();
}

List GerdabifyAPI::search(string name)
{
	return gerdab.search(name);
}

void GerdabifyAPI::select(string input)
{
	gerdab.select(input);
}

List GerdabifyAPI::list()
{
	 return gerdab.list();
}

List GerdabifyAPI::listMusics()
{
	return gerdab.list_of_musics();
}

List GerdabifyAPI::listAlbums()
{
	return gerdab.list_of_albums();
}

List GerdabifyAPI::listPlaylists()
{
	return gerdab.list_of_playlists();
}

List GerdabifyAPI::listArtists()
{
	return gerdab.list_of_artists();
}

void GerdabifyAPI::play()
{
	gerdab.play();
}

void GerdabifyAPI::addTo(string input)
{
	gerdab.add_to(input);
}

void GerdabifyAPI::goTo(string input)
{
	gerdab.go_to(input);
}

void GerdabifyAPI::createPlaylist(string input)
{
	gerdab.create_playlist(input);
}

void GerdabifyAPI::clearPlaylist(string input)
{
	gerdab.clear_playlist(input);
}

void GerdabifyAPI::remove(string input)
{
	gerdab.remove_music(input);
}

void GerdabifyAPI::orderItem(string music_name, int index)
{
	gerdab.order_item(music_name, index);
}

void GerdabifyAPI::rate(int i)
{
	gerdab.rate(i);
}

string GerdabifyAPI::getArtist()
{
	return gerdab.get_artist();
}

string GerdabifyAPI::getAlbum()
{
	return gerdab.get_album();
}

string GerdabifyAPI::getName()
{
	return gerdab.get_name();
}

string GerdabifyAPI::getCompleteName()
{
	return gerdab.get_complete_name();
}

int GerdabifyAPI::getRate()
{
	return gerdab.get_rate();
}

int GerdabifyAPI::getUserRate()
{
	return gerdab.get_user_rate();
}

int GerdabifyAPI::getCriticRate()
{
	return gerdab.get_critic_rate();
}

void GerdabifyAPI::enterPlayMode()
{
	gerdab.enter_player_mode();
}

void GerdabifyAPI::next()
{
	gerdab.next_music();
}

void GerdabifyAPI::previous()
{
	gerdab.previous_music();
}

void GerdabifyAPI::pause()
{
	gerdab.pause();
}

void GerdabifyAPI::repeatOne()
{
	gerdab.repeat_one();
}

void GerdabifyAPI::repeat()
{
	gerdab.repeat();
}

void GerdabifyAPI::signup(UserData userdata, string password)
{
	gerdab.signup(userdata, password);
}

void GerdabifyAPI::login(string username, string password)
{
	gerdab.login(username, password);
}

void GerdabifyAPI::addMusic(string music_name, string file_path)
{
	gerdab.add_music(music_name, file_path);
}

void GerdabifyAPI::addAlbum(string artist, string name)
{
	gerdab.add_album(artist, name);
}

void GerdabifyAPI::validate()
{
	gerdab.validate();
}

UserData GerdabifyAPI::getUserDetails(string username)
{
	return gerdab.get_user_data(username);
}

void GerdabifyAPI::verifyUser(string input)
{
	gerdab.verify_user(input);
}