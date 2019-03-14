#include "admin.h"
#include <iostream>

using namespace std;

Admin::Admin(UserData userdata, string password) : User(userdata, password)
{
	validated = false;
}

bool Admin::is_validated()
{
	return validated;
}

UserType Admin::get_usertype()
{
	if (is_validated())
		return U_ADMIN;
	return U_NORMAL;
}