#ifndef REGISTER_H_
#define REGISTER_H_

#include "user.h"
#include "artist.h"
#include "editor.h"
#include "admin.h"
#include "basics.h"
#include <vector>
#include <string>


class Register
{
public:
	Register();
	~Register();
	void signup(UserData userdata, std::string password);
	User* login(std::string username, std::string password);
	void search_artists(std::string name, List& result);
	Artist* select(std::string name);
	List get_artists_names();
	UserData get_user_data(std::string name);
	void verify_user(std::string input);

private:
	std::vector<User*> users;
};




#endif