#include "register.h"
#include "exceptions.h"

using namespace std;

Register::Register()
{
	UserData userdata;
	userdata.firstname = "admin";
	userdata.lastname = "admin";
	userdata.username = "admin";
	userdata.userType = U_ADMIN;
	Admin* temp = new Admin(userdata, "admin");
	temp->validate();
	users.push_back(temp);
}

Register::~Register()
{
	for (int i = 0; i < users.size(); i++)
	{
		delete users[i];
		//possible that we have bugs here beacause of ...
	}
}

void Register::signup(UserData userdata, string password)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_userdata().username == userdata.username)
			throw NotAuthorized("repetitive username!");
	}
	User* temp;
	if (userdata.userType == U_NORMAL)
		temp = new User(userdata, password);
	else if (userdata.userType == U_ARTIST)
		temp = new Artist(userdata, password);
	else if (userdata.userType == U_EDITOR)
		temp = new Editor(userdata, password);
	else if (userdata.userType == U_ADMIN)
		temp = new Admin(userdata, password);
	else
		temp = new User(userdata, password);
	users.push_back(temp);
}

User* Register::login(string username, string password)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_userdata().username == username)
		{
			if (users[i]->check_correct_password(password))
				return users[i];
			throw InvalidCredentials("wrong password!");
		}
	}
	throw InvalidCredentials("username not found!");
}

void Register::search_artists(string name, List& result)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_usertype() == U_ARTIST)
		{
			if (exists_in_string(users[i]->get_userdata().username, name))
				result.push_back(users[i]->get_userdata().username);
		}
	}
}

Artist* Register::select(string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (name == users[i]->get_userdata().username && users[i]->get_usertype() == U_ARTIST)
			return (Artist*)(users[i]);
	}
	return NULL;
}

List Register::get_artists_names()
{
	List result;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_usertype() == U_ARTIST)
			result.push_back(users[i]->get_userdata().username);
	}
	return result;
}

UserData Register::get_user_data(string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_userdata().username == name)
			return users[i]->get_userdata();
	}
	throw ItemDoesNotExist("no user found!");
}

void Register::verify_user(string input)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->get_userdata().username == input)
			users[i]->validate();
}