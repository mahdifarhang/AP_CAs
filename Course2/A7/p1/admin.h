#ifndef ADMIN_H_
#define ADMIN_H_

#include "user.h"


class Admin : public User
{
public:
	Admin(UserData userdata, std::string password);
	bool is_validated();
	UserType get_usertype();
	void validate() { validated = true; }

private:
};





#endif