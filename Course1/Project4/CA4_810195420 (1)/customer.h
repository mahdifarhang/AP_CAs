#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>
#include "bill.h"
class Customer{
public:
    Customer(std::string name,std::string phoneNumber,std::string location);
    void newOrder();
    void addItemToLastBill(std::string nameAndInfo,std::string restaurantLocation,std::string options,int cost,int counts);
    std::string closeOrderAndCalc();
    std::string getLastBillAsString();
    std::string getAllBills();
    std::string getPhoneNumber();
    std::string getLocation();
private:
    std::string name,phoneNumber,location;
    std::vector<Bill>bills;
};

Customer* readAndMakeCustomerFromLine(std::string line);
#endif
