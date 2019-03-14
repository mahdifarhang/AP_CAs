#include "customer.h"
#include "strTokenizer.h"
#include "mystrlib.h"

Customer::Customer(std::string name,std::string phoneNumber,std::string location){
    this->name=name;
    this->phoneNumber=phoneNumber;
    this->location=location;
}
void Customer::newOrder(){
    Bill temp(name+" "+correctString(phoneNumber),location);
    bills.push_back(temp);
}
void Customer::addItemToLastBill(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts){
    if(bills.size()!=0){
        bills[bills.size()-1].addItem(nameAndInfo,restaurantLocation,options,cost,counts);
    }
}
std::string Customer::closeOrderAndCalc(){
    if(bills.size()!=0){
        bills[bills.size()-1].calc();
        return bills[bills.size()-1].info();
    }
}
std::string Customer::getLastBillAsString(){
    if(bills.size()!=0){
        return bills[bills.size()-1].fullBill();
    }
}
std::string Customer::getAllBills(){
    if(bills.size()!=0){
        int fullCost=0;
        std::string returnValue;
        returnValue=bills[0].fullBill()+"#\n";
        fullCost+=bills[0].getFullCost();
        for(int i=1;i<bills.size();i++){
            returnValue=returnValue+bills[i].fullBillWithoutHeader()+"#\n";
            fullCost+=bills[i].getFullCost();
        }
        return returnValue+"total purchase "+intToString(fullCost)+"\n";
    }
}
std::string Customer::getPhoneNumber(){
    return phoneNumber;
}
std::string Customer::getLocation(){
    return location;
}
Customer* readAndMakeCustomerFromLine(std::string line){
    StrTokenizer tokenizerObj(line,std::string(","));
    if(tokenizerObj.numberOfParts()==3){
        return new  Customer(tokenizerObj.getWord(0),tokenizerObj.getWord(1),tokenizerObj.getWord(2));
    }
}
