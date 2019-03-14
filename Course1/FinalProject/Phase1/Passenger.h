#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <vector>
#include <string>
#include "String.h"

using namespace std;

class Passenger
{
public:
  Passenger(string, vector<string>, vector<Passenger>&, vector<string>);
  string getusername(){return username;}
  string getdiscount(){return discount_code;}
  string getphonenumber(){return phonenumber;}
  void charge_account(vector<string>);
  void get_credit(vector<string>);
  void get_discount_code(vector<string>);
  void increase_credit(int);
  void login(vector<string>);
  void logout(vector<string>);

private:
  string username;
  string password;
  string phonenumber;
  bool much;
  bool logedin;
  int credit;
  string discount_code;
  int UsedDiscountCodeTime;
};













#endif
