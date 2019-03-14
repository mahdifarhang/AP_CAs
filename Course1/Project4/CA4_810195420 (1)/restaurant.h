#ifndef RESTAURANT_H
#define RESTAURANT_H
#include<string>
#include<vector>
#include"food.h"
class Restaurant{
public:
    Restaurant(std::string name,std::string location,std::string phoneNumber);
    void addFood(Food* input);
    std::string makeMenu();
    std::string makeList();
    std::string makeList(std::string type);
    std::string makeList(FoodType type);
    std::string info();
    Food *getFoodByFoodCode(std::string code);
    std::string getName();
    std::string getPhoneNumber();
    std::string getLocation();
private:
    std::vector<Food*> foods;
    std::string name,location,phoneNumber;
};

Restaurant* readAndMakeRestaurantFromLine(std::string line);
bool restaurantCompare(Restaurant* a,Restaurant *b);
#endif
