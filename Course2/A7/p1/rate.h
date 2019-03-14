#ifndef RATE_H_
#define RATE_H_

class User;

class Rate
{
public:
	Rate(User* _user, int _rate);
	User* get_user() { return user; }
	int get_rate() { return rate; }


private:
	User* user;
	int rate;
};

















#endif