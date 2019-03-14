#include "artist.h"

using namespace std;


Artist::Artist(UserData userdata, string password) : User(userdata, password)
{
	validated = false;
}

UserType Artist::get_usertype()
{
	if (is_validated())
		return U_ARTIST;
	return U_NORMAL;
}

void Artist::validate()
{
	validated = true;
}