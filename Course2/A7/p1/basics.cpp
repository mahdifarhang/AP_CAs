#include "basics.h"

using namespace std;

bool exists_in_string(string name, string item)
{
	if (name.size() < item.size())
		return false;
	for (int i = 0; i < name.size() - item.size() + 1; i++)
		if (name.substr(i, item.size()) == item)
			return true;
	return false;
}