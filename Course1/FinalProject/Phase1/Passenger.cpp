#include "Passenger.h"


Passenger::Passenger(string _username, vector<string> arguments, vector<Passenger>& Passengers, vector<string> Driversname)
{
  if (arguments.size() != 2 || arguments.size() != 3)
      throw "You have to enter two or three parameters after passenger_signing up command.";
  for (int i = 0; i < Passengers.size(); i++)
    if (Passengers[i].getusername() == _username)
      throw "You can't choose this username cause its been chosen by another user.";
  for (int i = 0; i < Driversname.size(); i++)
    if (Driversname[i] == _username)
      throw "You can't choose this username cause its been chosen by another user.";
  if (_username == "admin")
    throw "You can't choose this username cause its been chosen by another user.";
  bool wrongphonenumber = true;
  for (int i = 0; i < Passengers.size(); i++)
    if(Passengers[i].getphonenumber() == arguments[1])
    {
      wrongphonenumber = false;
      break;
    }
  if (!wrongphonenumber)
    throw "There is a person signed in with this phone number. if it's not you please report it to the police.";
  bool true_discount = false;
  if (arguments.size() == 3)
  {
    for (int i = 0; i < Passengers.size(); i++)
    {
      if (Passengers[i].getdiscount() == arguments[2])
      {
        Passengers[i].increase_credit(10);
        credit = 10;
        true_discount = true;
        break;
      }
    }
    if (!true_discount)
      throw "There wasn't any discount code match.";
  }
  else
    credit = 0;
  username = _username;
  password = arguments[0];
  phonenumber = arguments[1];
  much = false;
  logedin = false;
  discount_code = _username + "_discount";
  UsedDiscountCodeTime = 0;
  cout << "Registering completed. from now on you can order drivers to take you through planets or galaxies." << endl;
}
void Passenger::login(vector<string> arguments)
{
  if (arguments.size() != 1)
    throw "Only one parameter after this command must be written.";
  if (arguments[0] != password)
    throw "You have enterd your password wrong.";
  if (logedin)
    throw "This user is loged in.";
  logedin = true;
  cout << "You are logged in as " << username << "."<< endl;
}
void Passenger::logout(vector<string> arguments)
{
  if (arguments.size() != 0)
    throw "You have to enter nothing after logout command.";
  if (!logedin)
    throw "This user isn't loged in yet.";
  logedin = false;
  cout << "You are successfuly logged out.";
}
void Passenger::increase_credit(int a)
{
  if (UsedDiscountCodeTime < 5)
  {
    UsedDiscountCodeTime++;
    credit += 10;
  }
}
void Passenger::get_discount_code(vector<string> arguments)
{
  if (arguments.size() != 0)
    throw "You shouldn't enter anything after this command.";
  if (!logedin)
    throw "This user hasn't loged in yet.";
  cout << discount_code << " " << 5 - UsedDiscountCodeTime << endl;
}
void Passenger::charge_account(vector<string> arguments)
{
  if (!logedin)
    throw "This user should login first.";
  if (arguments.size() != 1)
    throw "You should only enter 1 parameter afrer charge_account command.";
  credit += stringToint(arguments[0]);
}
void Passenger::get_credit(vector<string> arguments)
{
  if (arguments.size() != 0)
    throw "Please don't enter ant parameters after this command.";
  if (!logedin)
    throw "You have to login first.";
  cout << credit << endl;
}
