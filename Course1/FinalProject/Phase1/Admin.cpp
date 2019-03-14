#include "Admin.h"

Admin::Admin()
{
  logedin = false;
}
void Admin::checking_registration_requests(string username, vector<Driver> Drivers, vector<string> arguments)
{
  if(arguments.size() != 1)
    throw "You have to enter only 1 parameter after this command.";
  int numberofunaccepteds = 0;
  if (username != "admin")
    throw "Only the admin can see the registration requests.";
  if (logedin == false){
    throw "You have to log in first as the admin to be allowed to do this action.";
  }
  for (int i = 0; i < Drivers.size(); i++)
    if (Drivers[i].accepted() == false)
    {
      Drivers[i].print_features();
      numberofunaccepteds ++;
    }
  if(numberofunaccepteds == 0)
    cout << "There isn't any request of becoming a driver." << endl;
}
void Admin::accept_registration(string username, vector<Driver>& Drivers, vector<string> arguments)
{
  if (arguments.size() != 1)
    throw "Only 1 parameter must be entered after this command.";
  string drivername = arguments[0];
  if (username != "admin")
    throw "Only the admin can see the registration requests.";
  if (logedin == false)
  {
    throw "You have to log in first as the admin to be allowed to see the requests of resignation.";
  }
  bool done_accepting = false;
  for (int i = 0; i < Drivers.size(); i++){

    if(Drivers[i].getusername() == drivername)
    {
      Drivers[i].accept_request();
      cout << "Accepting completed!" << endl;
      done_accepting;
      break;
    }
  }
  if (done_accepting)
    cout << "There isn't any driver with this name." << endl;
}
void Admin::reject_registration(string username, vector<Driver>& Drivers, vector<string> arguments)
{
  if (arguments.size() != 1)
    throw "Only 1 parameter must be entered after this command.";
  string drivername = arguments[0];
  if (username != "admin")
    throw "Only the admin can see the registration requests.";
  if (logedin == false)
  {
    throw "You have to log in first as the admin to be allowed to do this action.";
  }
  bool done_rejecting = false;
  for (int i = 0; i < Drivers.size(); i++)
    if(Drivers[i].getusername() == drivername)
    {
      Drivers[i].reject_request();
      done_rejecting = true;
      cout << "Rejecting completed!" << endl;
      break;
    }
  if(done_rejecting)
    cout << "There isn't any driver with this name." << endl;
}
void Admin::login(vector<string> arguments)
{
  if (arguments.size() != 1)
    throw "Only one parameter after this command must be written.";
  if (arguments[0] != "s3cret")
    throw "You have enterd your password wrong.";
  logedin = true;
  cout << "You are logged in as admin." << endl;
}
void Admin::logout(vector<string> arguments)
{
  if(arguments.size() != 0)
    throw "No parametets must be entered after logout command.";
  if (!logedin)
    throw "This user isn't logedin.";
  cout << "You are logged out." << endl;
}
