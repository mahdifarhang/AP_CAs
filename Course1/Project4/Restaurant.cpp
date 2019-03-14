#include "Restaurant.hpp"

class Restaurant
{
  public:
    Restaurant(string _name, string _phonenumber, string _location);
    void get_information();
    void menu_oeder();
  private:
    string restaurant_name;
    string location;
    string phone_number;
    vector<food*> foods;

};

Restaurant::Restaurant(string _name, string _phonenumber, string _location)
{
  restaurant_name = _name;
  phone_number = _phonenumber;
  location = _location;
}
void Restaurant::get_information()
{
    fstream restaurant_information_file;
    restaurant_information_file.open("restaurants.txt");
    restaurant_information_file.getline()





  while (getline(restaurant.txt))
  {
    if
  }
}
void Restaurant::menu_order()
{
  for (int i = 0; i < foods.size(); i++)
    cout << foods[i]->get_foodcode << " " << foods[i]->get_foodname << " " << foods[i]->get_foodtype << " " << foods[i]->get_foodcost << endl;
}
