#include "StringTokenizer.h"
bool StringTokenizer::isItTokenizer(char input)
{
    for(int i=0;(unsigned)i<tokenizers.size();i++)
    {
        if(tokenizers[i]==input)return true;
    }
    return false;
}
std::string StringTokenizer::charToString(char input)
{
    char returnValue[2];
    returnValue[0]=input;
    returnValue[1]='\0';
    return std::string(returnValue);
}
StringTokenizer::StringTokenizer(std::string mainString,std::string tokenizerChars)
{
    tokenizers=tokenizerChars;
    std::string temp;
    for(int i=0;(unsigned)i<mainString.size();i++)
    {
        if(isItTokenizer(mainString[i])){
            if(temp!="")
                tokens.push_back(temp);
            temp="";
        }else{
            temp=temp+charToString(mainString[i]);
        }
    }
    if(temp!="")
        tokens.push_back(temp);
}
std::vector<std::string> StringTokenizer::getAllTokens()
{
    return tokens;
}
std::string StringTokenizer::operator[](int input)
{
    if(input<0)return std::string();
    if((unsigned)input<tokens.size()){
        return tokens[input];
    }else{
        return std::string();
    }
}
std::vector<std::string>::size_type StringTokenizer::size()
{
    return tokens.size();
}

std::string spacing(std::string input, std::string distancing)
{
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < distancing.size(); j++)
    {
      if(input[i] == distancing[j])
      {
        input.insert(i, " ");
        input.insert(i + 2, " ");
        i += 2;
        break;
      }
    }
  }

}
