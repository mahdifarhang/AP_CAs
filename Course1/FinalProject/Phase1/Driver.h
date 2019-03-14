#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <vector>
#include <string>

#define AVAILABLE 1
#define UNAVAILABLE 2
#define TRAVELING 3

using namespace std;

class Driver
{
public:
  Driver(string, vector<string>, vector<Driver>&, vector<string>, vector<string>);
  void accept_request();
  void reject_request();
  string getusername(){return username;}
  string getspaceship_number(){return spaceship_number;}
  bool accepted(){return acceptance;}
  void print_features();
  void login(vector<string>);
  void logout(vector<string>);
  void set_status(vector<string>);
private:
  string username;
  string password;
  string spaceship_number;
  string spaceship_model;
  string production_year;
  string spaceship_color;
  bool logedin;
  int credit;
  bool VIP;
  bool acceptance;
  int status;//three difrent situation is acceptable (available,unavailable,traveling)
};

#endif
