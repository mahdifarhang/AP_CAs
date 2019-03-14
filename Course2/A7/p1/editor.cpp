#include "editor.h"

using namespace std;

Editor::Editor(UserData userdata, string password) : User(userdata, password)
{
	validated = false;
}

UserType Editor::get_usertype()
{
	if (is_validated())
		return U_EDITOR;
	return U_NORMAL;
}

void Editor::validate()
{
	validated = true;
}

