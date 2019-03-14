#include <vector>
#include <iostream>
#include "api.h"

#define Artist U_ARTIST
#define Editor U_EDITOR
#define Admin U_ADMIN
#define Normal U_NORMAL

using namespace std;





int main()
{
	GerdabifyAPI gerdab;
	try
	{
		UserData user;
		user.username = "ma.farhang";
		user.firstname = "mahdi";
		user.lastname = "farhang";
		user.userType = Normal;
		gerdab.signup(user, "salamsalam");
		user.username = "al.assar";
		user.firstname = "ali";
		user.lastname = "assar";
		user.userType = Artist;
		gerdab.signup(user, "kooftkooft");
		user.username = "amir.shobeir";
		user.firstname = "amir hosein";
		user.lastname = "shobeiry";
		user.userType = Artist;
		gerdab.signup(user, "seyed");
		gerdab.login("admin", "admin");
		gerdab.verifyUser("al.assar");
		gerdab.login("al.assar", "kooftkooft");
		gerdab.enterBrowserMode();
		gerdab.addMusic("beat", "./beat.wav");
		gerdab.login("ma.farhang", "salamsalam");
		gerdab.createPlaylist("mine");
		gerdab.select("beat");
		gerdab.addTo("mine");
		gerdab.select("mine");
		cout << gerdab.list()[0] << endl;
		gerdab.login("admin", "admin");
		gerdab.verifyUser("amir.shobeir");
		gerdab.select("al.assar");
		gerdab.login("amir.shobeir", "seyed");
		gerdab.select("beat");
		gerdab.play();
		gerdab.enterBrowserMode();
		gerdab.addAlbum("amir.shobeir", "shad");
		gerdab.select("beat");
		//gerdab.addTo("shad");
		gerdab.addMusic("book", "beat.wac");
		gerdab.select("book");
		gerdab.addTo("shad");
		gerdab.login("ma.farhang", "salamsalam");
		gerdab.select("shad");
		gerdab.addTo("mine");
		gerdab.select("mine");
		cout << "hoy" << endl;
		List temp = gerdab.listMusics();
		for (int i = 0; i < temp.size(); i++)
			cout << temp[i] << " ";
		cout << endl;
		cout << "hoy" << endl;
		gerdab.select("book");
		gerdab.play();




		gerdab.login("ma.farhang", "salamsalam");
		gerdab.select("beat");
		gerdab.rate(10);
		gerdab.login("amir.shobeir", "seyed");
		gerdab.select("beat");
		gerdab.rate(6);
		gerdab.login("al.assar", "kooftkooft");
		gerdab.select("beat");
		gerdab.rate(5);
		cout << gerdab.getCriticRate() << endl;

		

		cout << gerdab.list().size() << endl;
		gerdab.clearPlaylist("mine");
		cout << gerdab.list().size() << endl;
		cout << gerdab.list()[0] << endl;
		gerdab.goToHome();
		gerdab.goToLibrary();
		for (int i = 0; i < gerdab.list().size(); i++)
			cout << gerdab.list()[i] << endl;

		switch (gerdab.getUserDetails("al.assar").userType)
		{
			case Artist:
				cout << "artist" << endl;
				break;
			case Admin:
				cout << "admin" << endl;
				break;
			case Normal:
				cout << "noraml" << endl;
				break;
			case Editor:
				cout << "editor" << endl;
				break;
		}
	}
	catch (Exception e)
	{
		e.print_error();
		//cout << e.error() << endl;
	}

	cout << gerdab.getUserDetails("amir.shobeir").lastname << endl;
}

