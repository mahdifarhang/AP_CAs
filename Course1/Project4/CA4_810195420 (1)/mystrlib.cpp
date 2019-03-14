#include "mystrlib.h"
int parseInt(std::string input){
    int returnValue=0;
    for(int i=0;i<input.size();i++){
        returnValue=returnValue*10 +input[i]-48;
    }
    return returnValue;
}
std::string intToString(int input){
    if(input==0)return std::string("0");
    char temp[10];
    int i;
    for (i=0;input!=0;i++) {
        temp[i]=input%10+48;
        input=input/10;
    }
    char inverted[10];
    for(int j=i-1;j>=0;j--){
        inverted[j]=temp[i-1-j];
    }
    inverted[i]='\0';
    return std::string(inverted);
}
std::string correctString(std::string input){
    std::string returnValue;
    bool firstZeroEnd=false;
    for(int i=0;i<input.size();i++){
        if(input[i]!='0')firstZeroEnd=true;
        if(firstZeroEnd)returnValue=returnValue+input[i];
    }
    return returnValue;
}
