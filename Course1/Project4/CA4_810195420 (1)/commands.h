#include <string>
#include <vector>
#include "mystrlib.h"
#include "restaurant.h"
#include "strTokenizer.h"
#include "customer.h"
#include "food.h"
using namespace std;
string menuCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants);
string restaurantsCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers);
string listCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers);
void orderCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers);
string billCommand(StrTokenizer& tokens,vector<Customer*> customers);
