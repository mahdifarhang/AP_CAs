#include <string>
#include <vector>

using namespace std;

#define IRANIAN 1
#define EASTERN 2
#define EUROPIAN 3

class Food
{
  public:




  private:
    int food_code;
    string food_name;
    int food_type;
    int food_cost;
    Restaurant* restaurant;
};
