#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Restaurant
{
  public:
    void get_information();



  private:
    string restaurant_name;
    string location;
    int phone_number;
    vector<food*> foods;




};
