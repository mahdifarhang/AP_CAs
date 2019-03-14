#ifndef FOOD_H
#define FOOD_H
#include<string>

enum FoodType{
IRANIAN,EASTERN,EUROPEAN
};

class Food{
public:
    Food(std::string name,std::string foodCode,FoodType type ,int cost);
    std::string info();
    FoodType getType();
    std::string getFoodCode();
    int getCost();
private:
    std::string name,foodCode;
    int cost;
    FoodType type;
};

Food* readAndMakeFoodFromLine(std::string line);
bool foodCompare(Food* a,Food *b);
#endif
