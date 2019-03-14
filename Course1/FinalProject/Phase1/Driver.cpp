#include "Driver.h"

Driver::Driver(string _username, vector<string> arguments, vector<Driver>& Drivers, vector<string> Passengersname, vector<string> spaceships)
{
  if (arguments.size() != 5 || arguments.size() != 6)
    throw "You have to enter five or six parameters after driver_signing up command.";
  for (int i = 0; i < Drivers.size(); i++)
  {
    if (Drivers[i].getusername() == _username)
      throw "You can't choose this username cause its been chosen by another user.";
    if (Drivers[i].getspaceship_number() == arguments[1])
      throw "This spaceship number is used by another driver.Please if its not you , please report it to the police.";
  }
  for (int i = 0; i < Passengersname.size(); i++)
    if (Passengersname[i] == _username)
      throw "You can't choose this username cause its been chosen by another user.";
  if (_username == "admin")
    throw "You can't choose this username cause its been chosen by another user.";
  if (arguments.size() == 5)
    VIP = false;
  else
  {
    if (arguments[5] == "VIP")
      VIP = true;
    else
    {
      throw "for the sixth parameter you can only write down (VIP).";
    }
  }
  bool exist_spaceship = false;
  for (int i = 0; i < spaceships.size(); i++)
    if(arguments[2] == spaceships[i])
    {
      exist_spaceship = true;
      break;
    }
  if (exist_spaceship == false)
    throw "You are not allowed to drive with this spaceship.";
  username = _username;
  password = arguments[0];
  spaceship_number = arguments[1];
  spaceship_model = arguments[2];
  production_year = arguments[3];
  spaceship_color = arguments[4];
  acceptance = false;
  logedin = false;
  status = AVAILABLE;
  credit = 0;
  cout << "Registering completed. You have to wait for admin to accept you." << endl;
}
void Driver::print_features()
{
  cout << "[ " << username << " " << spaceship_number << " " << spaceship_model << " " << production_year << " " << spaceship_color << " ";
  if (VIP = false)
    cout << "]" << endl;
  else
    cout << "[VIP] ]" << endl;
}
void Driver::accept_request()
{
  acceptance = true;
}
void Driver::reject_request()
{

}
void Driver::login(vector<string> arguments)
{
  if (!acceptance)
    throw "This driver isn't accepted to be a drivet yet.So you can't login.";
  if (arguments.size() != 1)
    throw "Only one parameter after this command must be written.";
  if (arguments[0] != password)
    throw "You have enterd your password wrong.";
  if (logedin)
    throw "This user is loged in already.";
  logedin = true;
  cout << "You are logged in as " << username << "."<< endl;
}
void Driver::logout(vector<string> arguments)
{
  if (arguments.size() != 0)
    throw "You have to enter nothing after logout command.";
  if (!logedin)
    throw "This user isn't loged in.";
  logedin = false;
  cout << "You are successfuly logged out.";
}
