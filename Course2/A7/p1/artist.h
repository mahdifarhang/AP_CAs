#ifndef ARTIST_H_
#define ARTIST_H_

#include "user.h"
#include "basics.h"


class Artist : public User
{
public:
	Artist(UserData userdata, std::string password);
	bool is_validated() { return validated; }
	void validate();
	UserType get_usertype();
	
private:
};










#endif