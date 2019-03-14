#include "strTokenizer.h"

StrTokenizer::StrTokenizer(std::string mainString,std::string tokenizerChars){
    this->tokenizerChars=tokenizerChars;
    std::string temp;
    for(int i=0;i<mainString.size();i++){
        if(isItTokenizer(mainString[i])){
            if(temp!=""){
                words.push_back(temp);
            }
            temp="";
        }else{
            temp=temp+mainString[i];
        }
    }
    if(temp!="")
        words.push_back(temp);
}
std::string StrTokenizer::getWord(int number){
    if(number<words.size()){
        return words[number];
    }
}
int StrTokenizer::numberOfParts(){
    return words.size();
}
bool StrTokenizer::isItTokenizer(char input){
    for(int i=0;i<tokenizerChars.size();i++){
        if(input==tokenizerChars[i])return true;
    }
    return false;
}
