#include <iostream>
#include "food.h"
#include "strTokenizer.h"
#include "mystrlib.h"

Food::Food(std::string name,std::string foodCode,FoodType type ,int cost){
    this->name=name;
    this->foodCode=foodCode;
    this->type=type;
    this->cost=cost;
}
std::string Food::info(){
    std::string returnValue=foodCode+" "+name+" ";
    switch (type) {
        case IRANIAN:
            returnValue=returnValue+"Iranian";
            break;
        case EUROPEAN:
            returnValue=returnValue+"European";
            break;
        case EASTERN:
            returnValue=returnValue+"Eastern";
            break;
    }
    returnValue=returnValue+" "+intToString(cost);
    return returnValue;
}
FoodType Food::getType(){
    return type;
}
std::string Food::getFoodCode(){
    return foodCode;
}
int Food::getCost(){
    return cost;
}
Food* readAndMakeFoodFromLine(std::string line){
    StrTokenizer tokenizerObj(line,std::string(","));
    if(tokenizerObj.numberOfParts()==4){
        int cost;
        FoodType type;
        std::string costString=tokenizerObj.getWord(3),typeString=tokenizerObj.getWord(2);
        cost=parseInt(costString);
        if(typeString=="European"){
            type=EUROPEAN;
        }else if(typeString=="Eastern"){
            type=EASTERN;
        }else if(typeString=="Iranian"){
            type=IRANIAN;
        }
        return new  Food(tokenizerObj.getWord(1),tokenizerObj.getWord(0),type,cost);
    }
}
bool foodCompare(Food* a,Food *b){
    return a->getFoodCode()<b->getFoodCode();
}
