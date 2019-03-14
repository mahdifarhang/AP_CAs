#ifndef BILL_H
#define BILL_H
#include <string>
#include <vector>

class BillItem{
public:
    BillItem(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts);
    std::string info();
    int getFullCost();
    std::string getLocation();
private:
    std::string nameAndInfo,restaurantLocation, options;
    int cost, counts;
};
class Bill{
public:
    Bill(std::string customerInfo,std::string customerLocation);
    void addItem(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts);
    int calc();
    std::string info();
    std::string fullBill();
    std::string fullBillWithoutHeader();
    int getFullCost();
private:
    std::string customerInfo;
    std::string customerLocation;
    std::vector<BillItem*> items;
    int cost;
    int deliveryCost;
};
#endif
