#include "gerdab.h"
#include "exceptions.h"

using namespace std;

Gerdab::Gerdab()
{
	current_state = LoginMode;
}

bool Gerdab::check_in_browser()
{
	if (current_state != BrowserMode)
		throw MethodNotAvailable("not in browser mode!");
	return true;
}

bool Gerdab::check_in_register()
{
	if (current_state != LoginMode)
		throw MethodNotAvailable("not in login mode!");
	return true;
}

bool Gerdab::check_in_player()
{
	if (current_state != PlayMode)
		throw MethodNotAvailable("not in player mode!");
	return true;
}

void Gerdab::enter_browser_mode()
{
	if (current_state == LoginMode)
		throw MethodNotAvailable("not available while in login mode!");
	current_state = BrowserMode;
}

void Gerdab::go_home()
{
	check_in_browser();
	browser.go_home();
}

void Gerdab::go_playList()
{
	check_in_browser();
	browser.go_playlist();
}

void Gerdab::go_library()
{
	check_in_browser();
	browser.go_library();
}

void Gerdab::go_album()
{
	check_in_browser();
	browser.go_album();
}

void Gerdab::go_artist()
{
	check_in_browser();
	browser.go_artist();
}

List Gerdab::search(string name)
{
	check_in_browser();
	List result;
	registering.search_artists(name, result);
	browser.search_musics(name, result);
	browser.search_albums(name, result);
	browser.search_playlists(name, result);
	return result;
}

void Gerdab::select(string name)
{
	check_in_browser();
	//we first search in artists, then in albums and then in musics.
	//so if we reached to the musics and we didn't find anything, means it doesn't exist.
	Artist * temp = registering.select(name);
	if (temp != NULL)
		browser.select(temp);
	else
		browser.select(name);
}

List Gerdab::list()
{
	check_in_browser();
	return browser.list(registering.get_artists_names());
}

List Gerdab::list_of_musics()
{
	check_in_browser();
	return browser.list_of_musics();
}

List Gerdab::list_of_albums()
{
	check_in_browser();
	return browser.list_of_albums();
}

List Gerdab::list_of_playlists()
{
	check_in_browser();
	return browser.list_of_playlists();
}

List Gerdab::list_of_artists()
{
	check_in_browser();
	return browser.get_artists_names(registering.get_artists_names());
}

void Gerdab::play()
{
	if (current_state == LoginMode)
		throw MethodNotAvailable("not available in login mode!");
	else if (current_state == BrowserMode)
		player.set_queue(browser.play());
	current_state = PlayMode;
	player.play();
}

void Gerdab::add_to(string input)
{
	check_in_browser();
	browser.add_to(input);
}

void Gerdab::go_to(string input)
{
	check_in_browser();
	browser.go_to_playlist_or_queue(input);
}

void Gerdab::create_playlist(string input)
{
	check_in_browser();
	browser.create_playlist(input);
}

void Gerdab::clear_playlist(string input)
{
	check_in_browser();
	browser.clear_playlist(input);
}

void Gerdab::remove_music(string input)
{
	check_in_browser();
	browser.remove_music(input);
}

void Gerdab::order_item(string music_name, int index)
{
	check_in_browser();
	browser.order_item(music_name, index);
}

void Gerdab::rate(int i)
{
	check_in_browser();
	browser.rate(i);
}

string Gerdab::get_artist()
{
	check_in_browser();
	return browser.get_artist();
}

string Gerdab::get_album()
{
	check_in_browser();
	return browser.get_album();
}

string Gerdab::get_name()
{
	check_in_browser();
	return browser.get_name();
}

string Gerdab::get_complete_name()
{
	check_in_browser();
	return browser.get_complete_name();
}

int Gerdab::get_rate()
{
	check_in_browser();
	return browser.get_my_rate();
}

int Gerdab::get_user_rate()
{
	check_in_browser();
	return browser.get_average_rate();
}

int Gerdab::get_critic_rate()
{
	check_in_browser();
	return browser.get_editor_average_rate();
}

void Gerdab::enter_player_mode()
{
	if (current_state == LoginMode)
		throw MethodNotAvailable("can't go to player mode from login mode!");
	current_state = PlayMode;
	player.set_queue(browser.get_current_queue());
}

void Gerdab::next_music()
{
	check_in_player();
	player.next_music();
}

void Gerdab::previous_music()
{
	check_in_player();
	player.previous_music();
}

void Gerdab::pause()
{
	check_in_player();
	player.pause();
}

void Gerdab::repeat_one()
{
	check_in_player();
	player.repeat_one();
}

void Gerdab::repeat()
{
	check_in_player();
	player.repeat();
}

void Gerdab::signup(UserData userdata, string password)
{
	check_in_register();
	registering.signup(userdata, password);
}

void Gerdab::login(string username, string password)
{
	//check_in_register();
	User* temp = registering.login(username, password);
	current_state = BrowserMode;
	browser.login(temp);
}

void Gerdab::add_music(string music_name, string file_path)
{
	check_in_browser();
	browser.add_music(music_name, file_path);
}

void Gerdab::add_album(string artist_name, string album_name)
{
	check_in_browser();
	browser.add_album(artist_name, album_name);
}

void Gerdab::validate()
{
	browser.validate();
}

UserData Gerdab::get_user_data(string name)
{
	return registering.get_user_data(name);
}

void Gerdab::verify_user(string input)
{
	check_in_browser();
	if (!browser.is_admin())
		throw MethodNotAvailable("only admins can verify users!");
	registering.verify_user(input);
}
