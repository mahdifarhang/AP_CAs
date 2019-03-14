#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
#include <iostream>

class Exception
{
public:
	Exception(std::string input) : error_description(input) { }
	void print_error();
	std::string getMessage();
protected:
	std::string error_description;
};

class ItemDoesNotExist : public Exception
{
public:
	ItemDoesNotExist(std::string input = "") : Exception("Item does not exist: " + input) {}
};

class NotAuthorized : public Exception
{
public:
	NotAuthorized(std::string input = "") : Exception("Not authorized: " + input) {}
};

class MethodNotAvailable : public Exception
{
public:
	MethodNotAvailable(std::string input = "") : Exception("Method not available: " + input) {}
};

class InvalidArguments : public Exception
{
public:
	InvalidArguments(std::string input = "") : Exception("Invalid arguments: " + input) {}
};

class InvalidCredentials : public Exception
{
public:
	InvalidCredentials(std::string input = "") : Exception("Invalid credentilas: " + input) {}
};

class AlreadyExists : public Exception
{
public:
	AlreadyExists(std::string input = "") : Exception("Already exists: " + input) {}
};


class GerdabError : public Exception
{

public:
  GerdabError(std::string input = "") : Exception("Gerdab player error: " + input) {}
};



















#endif