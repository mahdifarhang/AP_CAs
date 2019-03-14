#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H
#include <string>
#include <vector>
class StringTokenizer
{
public:
  StringTokenizer(std::string mainString, std::string tokenizerChars);
  std::vector<std::string> get_all_tokens();
  std::string operator[](int input);
  std::vector<std::string>::size_type size();
private:
  std::string tokenizers;
  std::vector<std::string> tokens;
  bool isItTokenizer(char input);
};
std::string charToString(char input);
std::string spacing(std::string input, std::string distancing);

#endif
