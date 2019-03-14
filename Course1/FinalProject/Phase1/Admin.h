#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <vector>
#include <string>
#include "Driver.h"

using namespace std;

class Admin
{
public:
  Admin();
  void checking_registration_requests(string, vector<Driver>, vector<string>);
  void accept_registration(string, vector<Driver>&, vector<string>);
  void reject_registration(string, vector<Driver>&, vector<string>);
  void login(vector<string>);
  void logout(vector<string>);

private:
  bool logedin;
  int credit;
};

#endif
