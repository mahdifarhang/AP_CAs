#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "restaurant.h"
#include "food.h"
#include "customer.h"
#include "commands.h"
#include "strTokenizer.h"
using namespace std;

void readRestaurantsFile(ifstream &input,vector<Restaurant*> &restaurants);
void readCustomersFile(ifstream &input,vector<Customer*> &customers);
void readInforamtionsFromFiles(vector<Restaurant*> &restaurants,vector<Customer*> &customers);

int main() {
    vector<Restaurant*> restaurants;
    vector<Customer*> customers;
    readInforamtionsFromFiles(restaurants,customers);
    string line;
    while(getline(cin,line)){
        StrTokenizer tokenizerObj(line,string(" "));
        if(tokenizerObj.getWord(0)=="menu"){
            cout<<menuCommand(tokenizerObj,restaurants)<<flush;
        }else if(tokenizerObj.getWord(0)=="restaurants"){
            cout<<restaurantsCommand(tokenizerObj,restaurants,customers)<<flush;
        }else if(tokenizerObj.getWord(0)=="list"){
            cout<<listCommand(tokenizerObj,restaurants,customers)<<flush;
        }else if(tokenizerObj.getWord(0)=="order"){
            orderCommand(tokenizerObj,restaurants,customers);
        }else if(tokenizerObj.getWord(0)=="bill"){
            cout<<billCommand(tokenizerObj,customers)<<flush;
        }

    }
}

void readInforamtionsFromFiles(vector<Restaurant*> &restaurants,vector<Customer*> &customers){
    ifstream restaurantFile("restaurants.txt");
    ifstream customersFile("customers.txt");
    readRestaurantsFile(restaurantFile,restaurants);
    readCustomersFile(customersFile,customers);
}
void readRestaurantsFile(ifstream &input,vector<Restaurant*> &restaurants){
    string line;
    Restaurant *newRestaurant;
    bool isThisLineRestaurantInfo=true;
    while(getline(input,line)){
        if(line==""){
            isThisLineRestaurantInfo=true;
            continue;
        }
        if(isThisLineRestaurantInfo){
            newRestaurant =readAndMakeRestaurantFromLine(line);
            restaurants.push_back(newRestaurant);
            isThisLineRestaurantInfo=false;
        }else{
            newRestaurant->addFood(readAndMakeFoodFromLine(line));
        }
    }
    sort(restaurants.begin(),restaurants.end(),restaurantCompare);
}
void readCustomersFile(ifstream &input,vector<Customer*> &customers){
    string line;
    Customer *newCustomer;
    while(getline(input,line)){
        customers.push_back(readAndMakeCustomerFromLine(line));
    }
}
