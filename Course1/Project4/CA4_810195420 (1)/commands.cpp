#include <iostream>
#include "commands.h"


using namespace std;

string menuCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants){
    string returnValue;
    if(tokens.numberOfParts()==2){
        for(int i=0;i<restaurants.size();i++){
            if(restaurants[i]->getPhoneNumber()==tokens.getWord(1)){
                returnValue=restaurants[i]->makeMenu();
                break;
            }
        }
    }
    return returnValue;
}
string restaurantsCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers){
    string returnValue;
    if(tokens.numberOfParts()==1){
        for(int i=0;i<restaurants.size();i++){
            returnValue=returnValue+restaurants[i]->info()+"\n";
        }
    }else if (tokens.numberOfParts()==3){
        if(tokens.getWord(1)=="near"){
            for(int i=0;i<customers.size();i++){
                if(customers[i]->getPhoneNumber()==tokens.getWord(2)){
                    for(int j=0;j<restaurants.size();j++){
                        if(restaurants[j]->getLocation()==customers[i]->getLocation())
                            returnValue=returnValue+restaurants[j]->info()+"\n";
                    }
                }
            }
        }
    }
    return returnValue;
}
string listCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers){
    string returnValue;
    if(tokens.numberOfParts()==1){
        for(int i=0;i<restaurants.size();i++){
            returnValue=returnValue+restaurants[i]->makeList();
        }
    }else if (tokens.numberOfParts()==3){
        if(tokens.getWord(1)=="near"){
            for(int i=0;i<customers.size();i++){
                if(customers[i]->getPhoneNumber()==tokens.getWord(2)){
                    for(int j=0;j<restaurants.size();j++){
                        if(restaurants[j]->getLocation()==customers[i]->getLocation())
                            returnValue=returnValue+restaurants[j]->makeList();
                    }
                }
            }
        }else if(tokens.getWord(1)=="type"){
            for(int i=0;i<restaurants.size();i++){
                returnValue=returnValue+restaurants[i]->makeList(tokens.getWord(2));
            }
        }
    }
    return returnValue;
}
void orderCommand(StrTokenizer& tokens,vector<Restaurant*> &restaurants,vector<Customer*> customers){
    if(tokens.numberOfParts()==2){
        Customer *selectedCustomer;
        bool foundCustomer=false;
        for(int i=0;i<customers.size();i++){
            if(customers[i]->getPhoneNumber()==tokens.getWord(1)){
                foundCustomer=true;
                selectedCustomer=customers[i];
                selectedCustomer->newOrder();
            }
        }
        if(foundCustomer){
            string line;
            while(getline(cin,line)){
                StrTokenizer tokenizerObj(line,string(" "));
                if(tokenizerObj.numberOfParts()>1){
                    string restaurantPhone,foodCode,foodOptions;
                    string firstObj= tokenizerObj.getWord(0);
                    for(int i=0;i<firstObj.size()-3;i++){
                        restaurantPhone=restaurantPhone+firstObj[i];
                    }
                    for(int i=firstObj.size()-3;i<firstObj.size();i++){
                        foodCode=foodCode+firstObj[i];
                    }
                    for(int i=2;i<tokenizerObj.numberOfParts();i++){
                        foodOptions=foodOptions+ tokenizerObj.getWord(i);
                        if(i!=tokenizerObj.numberOfParts()-1)foodOptions=foodOptions+" ";
                    }
                    for(int i=0;i<restaurants.size();i++){
                        if(restaurants[i]->getPhoneNumber()==restaurantPhone){
                            Food* seletedFood= restaurants[i]->getFoodByFoodCode(foodCode);
                            selectedCustomer->addItemToLastBill(restaurantPhone+seletedFood->info(),restaurants[i]->getLocation(),foodOptions,seletedFood->getCost(),parseInt(tokenizerObj.getWord(1)));
                            break;
                        }
                    }
                }else if(tokenizerObj.getWord(0)=="$"){
                    cout<< selectedCustomer->closeOrderAndCalc()<<endl;
                    break;
                }
            }
        }
    }
}
string billCommand(StrTokenizer& tokens,vector<Customer*> customers){
    if(tokens.numberOfParts()==2){
        for(int i=0;i<customers.size();i++){
            if(customers[i]->getPhoneNumber()==tokens.getWord(1)){
                return customers[i]->getLastBillAsString();
            }
        }
    }else if(tokens.numberOfParts()==3){
        if(tokens.getWord(1)=="all"){
            for(int i=0;i<customers.size();i++){
                if(customers[i]->getPhoneNumber()==tokens.getWord(2)){
                    return customers[i]->getAllBills();
                }
            }
        }
    }
}
