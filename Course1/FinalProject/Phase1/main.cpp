#include "Passenger.h"
#include "Driver.h"
#include "Admin.h"
#include "String.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;


int main()
{
  vector<Passenger> Passengers;
  vector<Driver> Drivers;
  string username;
  string command;
  vector<string> arguments;
  Admin admin;
  vector<string> Spaceships;
  seperating_file(Spaceships, "vehicles.cfg");
  while(true)
  {
    try
    {
      getting_information(username, command, arguments);
      if(command == "register_passenger")
      {
        vector<string> Driversname;
        for (int i = 0; i < Drivers.size(); i++)
          Driversname.push_back(Drivers[i].getusername());
        Passengers.push_back(Passenger(username, arguments, Passengers, Driversname));
      }
      else if(command == "register_driver")
      {
        vector<string> Passengersname;
        for (int i = 0; i < Passengers.size(); i++)
          Passengersname.push_back(Passengers[i].getusername());
        Drivers.push_back(Driver(username, arguments, Drivers, Passengersname, Spaceships));
      }
      else if(command == "show_registration_requests")
      {
        admin.checking_registration_requests(username, Drivers, arguments);
      }
      else if(command == "accept_registration")
      {
        admin.accept_registration(username, Drivers, arguments);
      }
      else if(command == "reject_registration")
      {
        admin.reject_registration(username, Drivers, arguments);
      }
      else if(command == "login")
      {
        bool doneloggingin = false;
        if (username == "admin")
        {
          admin.login(arguments);
          doneloggingin = true;
        }
        if (!doneloggingin)
          for (int i = 0; i < Passengers.size(); i++)
            if(Passengers[i].getusername() == username)
            {
              Passengers[i].login(arguments);
              doneloggingin = true;
              break;
            }
        if (!doneloggingin)
          for (int i = 0; i < Drivers.size(); i++)
            if (Drivers[i].getusername() == username)
            {
              Drivers[i].login(arguments);
              doneloggingin = true;
              break;
            }
        if (!doneloggingin)
          throw "This username doesn't exist.";
      }
      else if(command == "logout")
      {
        bool doneloggingout = false;
        if (username == "admin")
        {
          admin.logout(arguments);
          doneloggingout = true;
        }
        if (!doneloggingout)
          for (int i = 0; i < Passengers.size(); i++)
            if(Passengers[i].getusername() == username)
            {
              Passengers[i].logout(arguments);
              doneloggingout = true;
              break;
            }
        if (!doneloggingout)
          for (int i = 0; i < Drivers.size(); i++)
            if (Drivers[i].getusername() == username)
            {
              Drivers[i].logout(arguments);
              doneloggingout = true;
              break;
            }
        if (!doneloggingout)
          throw "This username doesn't exist.";
      }
      else if(command == "get_discount_code")
      {
        bool flag = false;
        for (int i = 0; i < Passengers.size(); i++)
        {
          if(Passengers[i].getusername() == username)
          {
            Passengers[i].get_discount_code(arguments);
            flag = true;
            break;
          }
        }
        if(!flag)
          throw "No username match found.";
      }
      // else if(command == "set_status")
      // {
      //   bool flag = false;
      //   for (int i = 0; i < Drivers.size(); i++)
      //   {
      //     if(Drivers[i].getusername() == username)
      //     {
      //       Drivers[i].set_status(arguments);
      //       flag = true;
      //       break;
      //     }
      //   }
      //   if (!flag)
      //     throw "No username match found.";
      // }
      else if(command == "charge_account")
      {
        bool flag = false;
        for (int i = 0; i < Passengers.size(); i++)
        {
          if(Passengers[i].getusername() == username)
          {
            Passengers[i].charge_account(arguments);
            flag = true;
            break;
          }
        }
        if(!flag)
          throw "No username match found.";
      }
      else if(command == "get_credit")
      {
        bool flag = false;
        for (int i = 0; i < Passengers.size(); i++)
        {
          if(Passengers[i].getusername() == username)
          {
            Passengers[i].get_credit(arguments);
            flag = true;
            break;
          }
        }
        if(!flag)
          throw "No username match found.";
      }
      else
        throw "Problem detecting your command.";
    }
    catch(const char* a)
    {
      cout << a << endl;
    }
  }
}
