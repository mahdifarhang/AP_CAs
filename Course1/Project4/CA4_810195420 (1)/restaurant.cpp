#include <algorithm>
#include "restaurant.h"
#include "strTokenizer.h"
#include "mystrlib.h"
Restaurant::Restaurant(std::string name,std::string location,std::string phoneNumber){
    this->name=name;
    this->location=location;
    this->phoneNumber=phoneNumber;
}
void Restaurant::addFood(Food* input){
    this->foods.push_back(input);
    std::sort(foods.begin(),foods.end(),foodCompare);
}
std::string Restaurant::makeMenu(){
    std::string returnValue;
    for(int i=0;i<foods.size();i++){
        returnValue=returnValue+phoneNumber+foods[i]->info()+"\n";
    }
    return returnValue;
}
std::string Restaurant::makeList(){
    std::string returnValue;
    for(int i=0;i<foods.size();i++){
        returnValue=returnValue+phoneNumber+foods[i]->info()+" "+this->name+" "+this->location+"\n";
    }
    return returnValue;
}
std::string Restaurant::makeList(std::string type){
    if(type=="European"){
        return this->makeList(EUROPEAN);
    }else if(type=="Iranian"){
        return this->makeList (IRANIAN);
    }else if(type=="Eastern"){
        return this->makeList(EASTERN);
    }
}
std::string Restaurant::makeList(FoodType type){
    std::string returnValue;
    for(int i=0;i<foods.size();i++){
        if(type==foods[i]->getType())
            returnValue=returnValue+phoneNumber+foods[i]->info()+" "+this->name+" "+this->location+"\n";
    }
    return returnValue;
}
std::string Restaurant::info(){
    return name+" "+location+" "+phoneNumber;
}
Food *Restaurant::getFoodByFoodCode(std::string code){
    for(int i=0;i<foods.size();i++){
        if(foods[i]->getFoodCode()==code){
            return foods[i];
        }
    }
}
std::string Restaurant::getName(){
    return this->name;
}
std::string Restaurant::getPhoneNumber(){
    return phoneNumber;
}
std::string Restaurant::getLocation(){
    return location;
}
Restaurant* readAndMakeRestaurantFromLine(std::string line){
    StrTokenizer tokenizerObj(line,std::string(","));
    if(tokenizerObj.numberOfParts()==3){
        return new  Restaurant(tokenizerObj.getWord(0),tokenizerObj.getWord(2),tokenizerObj.getWord(1));
    }
}
bool restaurantCompare(Restaurant* a,Restaurant *b){
    return parseInt(a->getPhoneNumber())<parseInt(b->getPhoneNumber());
}
