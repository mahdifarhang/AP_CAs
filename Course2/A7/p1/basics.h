#ifndef BASICS_H_
#define BASICS_H_

#include <vector>
#include <string>

typedef std::vector<std::string> List;


enum UserType { U_ADMIN, U_ARTIST, U_EDITOR, U_NORMAL };


struct UserData
{
	std::string firstname;
	std::string lastname;
	std::string username;
	UserType userType;
};

bool exists_in_string(std::string name, std::string item);

#endif