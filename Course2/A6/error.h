#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include <iostream>

class Error
{
public:
  Error(std::string input)  {message = input;}
  void print_message()  {std::cout << message << std::endl;}
  std::string get_message()  {return message;}
  friend std::ostream& operator<<(std::ostream& out, const Error& bug);
private:
  std::string message;
};

std::ostream& operator<<(std::ostream& out, const Error& bug)
{
  out << bug.message;
  return out;
}
#endif
