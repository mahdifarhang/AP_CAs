#include "exceptions.h"

#include <iostream>

using namespace std;

void Exception::print_error()
{
	cout << error_description << endl;
}

string Exception::getMessage()
{
	return error_description;
}