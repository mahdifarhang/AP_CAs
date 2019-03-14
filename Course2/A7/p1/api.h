#ifndef API_H_
#define API_H_
#include <string>
#include "basics.h"
#include "gerdab.h"



class GerdabifyAPI
{
public:
	GerdabifyAPI();
    void enterBrowserMode();
    void goToHome();
    void goToPlayList();
    void goToLibrary();
    void goToAlbum();
    void goToArtist();
    List search(std::string);
    void select(std::string);
    List list();
    List listMusics();
    List listAlbums();
    List listPlaylists();
    List listArtists();
    void play();
    void addTo(std::string);
    void goTo(std::string);
    void createPlaylist(std::string);
    void clearPlaylist(std::string);
    void remove(std::string);
    void orderItem(std::string, int);
    void rate(int);
    std::string getArtist();
    std::string getAlbum();
    std::string getName();
    std::string getCompleteName();
    int getRate();
    int getUserRate();
    int getCriticRate();
    void enterPlayMode();
    void next();
    void previous();
    void pause();
    //void shuffle();
    void repeatOne();
    void repeat();
    void signup(UserData userdata, std::string password);
    void login(std::string, std::string);
    void addMusic(std::string, std::string);
    void addAlbum(std::string, std::string);
    void validate();
    UserData getUserDetails(std::string);
    void verifyUser(std::string);

private:
	Gerdab gerdab;
};

#endif