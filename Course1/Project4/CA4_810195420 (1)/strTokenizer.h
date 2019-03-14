#ifndef STRTOKENIZER_H
#define STRTOKENIZER_H
#include <string>
#include <vector>
class StrTokenizer{
public:
    StrTokenizer(std::string mainString,std::string tokenizerChars);
    std::string getWord(int number);
    int numberOfParts();
private:
    std::string tokenizerChars;
    std::vector<std::string> words;
    bool isItTokenizer(char input);
};
#endif
