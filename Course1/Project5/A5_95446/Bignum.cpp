#include "Bignum.hpp"

Bignum::Bignum()
{
  int temp = 0;
  After.push_back(temp);
  Before.push_back(temp);
  MinusSign = false;
}
Bignum::Bignum(string input)
{
  ConstructorfromString(input);
}
Bignum::Bignum(double input)
{
  ostringstream entered;
  entered << input;
  ConstructorfromString(entered.str());
}
void Bignum::ConstructorfromString(string input)
{
  bool DotCheck = false;
  if (input[0] == '-')
    MinusSign = true;
  for (int i = 0; i < input.size(); i++)
  {
    if (i == 0 && input[i] == '-')
      continue;
    if (input[i] == '.')
    {
      if (DotCheck)
        throw 0;
      DotCheck = true;
    }
    else if(input[i] >= '0' && input[i] <= '9')
    {
      if (DotCheck)
        After.push_back(input[i] - 48);
      else
        Before.push_back(input[i] - 48);
    }
    else
      throw 0;
  }
  reverse(Before.begin(), Before.end());
}
Bignum Bignum::operator+(const Bignum& input) const
{
  Bignum returnvalue;
  int carry = 0;
  vector<int> BigAfter;
  vector<int> BigBefore;
  vector<int> LittleAfter;
  vector<int> LittleBefore;
  if (this->After.size() > input.After.size())
  {
    BigAfter = this->After;
    LittleAfter = input.After;
  }
  else
  {
    LittleAfter = this->After;
    BigAfter = input.After;
  }
  if (this->Before.size() > input.Before.size())
  {
    BigBefore = this->Before;
    LittleBefore = input.Before;
  }
  else
  {
    LittleBefore = this->Before;
    BigBefore = input.Before;
  }
  if (this->MinusSign == input.MinusSign)
  {
    returnvalue.MinusSign = this->MinusSign;
    for(int i = 0; i < BigAfter.size() - LittleAfter.size(); i++)
      LittleAfter.push_back(0);
    for (int i = 0; i < BigAfter.size(); i++)
      returnvalue.After.push_back(0);
    for (int i = 0; i < BigAfter.size(); i++)
    {
      if (BigAfter[BigAfter.size() - 1 - i] + LittleAfter[LittleAfter.size() - 1 - i] + carry > 9)
      {
        carry = 1;
        returnvalue.After[BigAfter.size() - 1 - i] = BigAfter[BigAfter.size() - 1 - i] + LittleAfter[LittleAfter.size() - 1 - i] + carry - 10;
      }
      else
      {
        returnvalue.After[BigAfter.size() - 1 - i] = BigAfter[BigAfter.size() - 1 - i] + LittleAfter[LittleAfter.size() - 1 - i] + carry;
        carry = 0;
      }
    }
    for(int i = 0; i < BigBefore.size() - LittleBefore.size(); i++)
      LittleBefore.push_back(0);
    for (int i = 0; i < BigBefore.size(); i++)
      returnvalue.Before.push_back(0);
    for (int i = 0; i < BigBefore.size(); i++)
    {
      if (BigBefore[i] + LittleBefore[i] + carry > 9)
      {
        returnvalue.Before[i] = BigBefore[i] + LittleBefore[i] + carry - 10;
        carry = 1;
      }
      else
      {
        returnvalue.Before[i] = BigBefore[i] + LittleBefore[i] + carry;
        carry = 0;
      }
    }
    if (carry == 1)
      returnvalue.After.push_back(1);
  }
  else
  {
    if(this->Minussign)
    {
      Bignum nNumber = *this;
      Bignum pNumber = input;

    }
    else
    {
      Bignum nNumber = input;
      Bignum pNumber = *this;
    }
  }
  return returnvalue;

}
Bignum Bignum::operator+(const double input) const
{
  return (*this) + Bignum(input);
}
Bignum& Bignum::operator+=(const Bignum& input)
{
  Bignum sum = *this + input;
  this->After = sum.After;
  this->Before = sum.Before;
  this->MinusSign = sum.MinusSign;
  return sum;
}
Bignum& Bignum::operator=(const Bignum& input)
{
  this->MinusSign = input.MinusSign;
  this->After = input.After;
  this->Before = input.Before;
  return *this;
}
Bignum& Bignum::operator-()
{
  if(this->MinusSign == true)
    this->MinusSign = false;
  if(this->MinusSign == false)
    this->MinusSign = true;
}
Bignum& Bignum::operator++()
{
  (*this) += Bignum("1");
  return (*this);
}
Bignum Bignum::operator++(int free)
{
  Bignum temp = Bignum (*this);
  ++(*this);
  return temp;
}
bool Bignum::operator==(const Bignum& input) const
{
  if (this->MinusSign != input.MinusSign)
    return false;
  if (this->After != input.After)
    return false;
  if (this->Before != input.Before)
    return false;
  return true;
}
bool Bignum::operator!=(const Bignum& input) const
{
  return !(*this == input);
}
bool Bignum::operator<(const Bignum& input) const
{
  if (input.MinusSign != this->MinusSign)
    return this->MinusSign;
  int maxAfter = max(this->After.size(), input.After.size());
  int maxBefore = max(this->Before.size(), input.Before.size());
  for (int i = maxBefore - 1; i >= (-maxAfter); i--)
  {
    if (this->getnumber(i) == input.getnumber(i))
      continue;
    if (this->getnumber(i) < input.getnumber(i))
      return true;
    else if (this->getnumber(i) > input.getnumber(i))
      return false;
  }
  return false;
}
bool Bignum::operator>(const Bignum& input) const
{
  return input < *this;
}
bool Bignum::operator<=(const Bignum& input) const
{
  return !(*this > input);
}
bool Bignum::operator>=(const Bignum& input) const
{
  return !(*this < input);
}
Bignum operator+(const double& firstinput, const Bignum& secondinput)
{
  return secondinput + firstinput;
}
int Bignum::getnumber(int place)
{
  if (place < 0)
  {
    place = -place;
    place--;
    if (place > Before.size() - 1)
      return 0;
    return Before[place];
  }
  else
  {
    if (place > After.size() - 1)
      return 0;
    return After[place];
  }
}
int max (int a, int b)
{
  if (a > b)
    return a;
  return b;
}
int min (int a, int b)
{
  if (a < b)
    return a;
  return b;
}
