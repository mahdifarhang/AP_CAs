#include "bill.h"
#include "mystrlib.h"
BillItem::BillItem(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts){
    this->nameAndInfo=nameAndInfo;
    this->cost=cost;
    this->counts=counts;
    this->restaurantLocation=restaurantLocation;
    this->options=options;
}
std::string BillItem::info(){
    return nameAndInfo+" "+intToString(counts)+" "+intToString(cost*counts)+(options==""?"":" "+options);
}
int BillItem::getFullCost(){
    return cost*counts;
}
std::string BillItem::getLocation(){
    return restaurantLocation;
}
Bill::Bill(std::string customerInfo,std::string customerLocation){
    this->customerInfo=customerInfo;
    this->customerLocation=customerLocation;
}
void Bill::addItem(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts){
    items.push_back(new BillItem(nameAndInfo,restaurantLocation,options,cost,counts));
}
int Bill::calc(){
    bool isOutOfLocation=false;
    cost=0;
    for(int i=0;i<items.size();i++){
        cost+=items[i]->getFullCost();
        if(items[i]->getLocation()!=customerLocation)isOutOfLocation=true;
    }
    if(cost>100000||!isOutOfLocation){
        deliveryCost=0;
    }else{
        deliveryCost=5000;
    }
    return cost+deliveryCost;
}
std::string Bill::info(){
    return customerInfo+" "+intToString(cost+deliveryCost);
}
std::string Bill::fullBill(){
    std::string returnValue=customerInfo+"\n";
    return returnValue+fullBillWithoutHeader();
}
std::string Bill::fullBillWithoutHeader(){
    std::string returnValue;
    for(int i=0;i<items.size();i++){
        returnValue=returnValue+items[i]->info()+"\n";
    }
    returnValue=returnValue+"delivery cost "+intToString(deliveryCost)+"\n";
    returnValue=returnValue+"total cost "+intToString(cost+deliveryCost)+"\n";
    return returnValue;
}
int Bill::getFullCost(){
    return deliveryCost+cost;
}
