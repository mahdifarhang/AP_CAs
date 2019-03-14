#ifndef EDITOR_H_
#define EDITOR_H_

#include "user.h"


class Editor : public User
{
public:
	Editor(UserData userdata, std::string password);
	bool is_validated() { return validated; }
	void validate();
	UserType get_usertype();

private:
};






#endif