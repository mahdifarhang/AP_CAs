#ifndef BIGNUM
#define BIGNUM
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Bignum
{
public:
  Bignum();
  Bignum(double input);
  Bignum(string input);
  Bignum operator+(const Bignum& input) const;
  Bignum operator+(const double input) const;
  Bignum& operator+=(const Bignum& input);
  Bignum& operator=(const Bignum& input);
  Bignum& operator-();
  ‌Bignum& operator++();
  Bignum operator++(int free);
  bool operator==(const Bignum& input) const;
  bool operator!=(const Bignum& input) const;
  bool operator<(const Bignum& input) const;
  bool operator>(const Bignum& input) const;
  bool operator<=(const Bignum& input) const;
  bool operator>=(const Bignum& input) const;
  // int operator[](int input);
private:
  vector<int> Before;
  vector<int> After;
  bool MinusSign;
  int getnumber(int place);
  void ConstructorfromString(string input);
};
Bignum operator+(const double& firstinput, const Bignum& secondinput);
int max (int a, int b);
int min (int a, int b);
#endif
