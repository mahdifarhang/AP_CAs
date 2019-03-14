#include <string>
#include "StringTokenizer.h"
#include "row.h"
#include <sstream>

using namespace std;

Row::Row(int num, double value)
{
  vector<double> result = vector<double>(num, value);
  elements = result;
}

Row::Row(int input)
{
  vector<double> result = vector<double>(input, 0);
  elements = result;
}

Row::Row(vector<double> inputs)
{
  Row(inputs.size());
  elements = inputs;
}

int Row::size() const
{
  return elements.size();
}

Row Row::operator+(const Row& operand) const
{
  if (elements.size() != operand.size())
  throw RowLengthExeption();
  vector<double> result = vector<double> (elements.size(), 0);
  for (int i = 0; i < elements.size(); i++)
  result[i] = elements[i] + operand[i];
  return Row(result);
}

Row& Row::operator=(const Row& operand)
{
  if (operand.size() != elements.size())
    throw RowLengthExeption();
  elements = operand.elements;
  return *this;
}

Row& Row::operator=(const vector<double>& operand)
{
  if (operand.size() != elements.size())
    throw RowLengthExeption();
  elements = operand;
  return *this;
}

Row& Row::operator+=(const Row& operand)
{
  if (elements.size() != operand.size())
    throw RowLengthExeption();
  *this = (*this) + operand;
  return *this;
}

double Row::operator[](int i) const
{
  if (i >= elements.size() || i < 0)
    throw IndexOutOfBoundExeption();
  return elements[i];
}

double& Row::operator[](int i)
{
  if (i >= elements.size() || i < 0)
    throw IndexOutOfBoundExeption();
  return elements[i];
}

bool Row::operator==(const Row& operand) const
{
  if (elements.size() != operand.size())
    return false;
  for (int i = 0; i < operand.size(); i++)
    if (elements[i] != operand[i])
      return false;
  return true;
}

Row operator*(double num, const Row& operand)
{
  vector<double> result = vector<double>(operand.size(), 0);
  for (int i = 0; i < operand.size(); i++)
    result[i] = operand.elements[i] * num;
  return Row(result);
}

ostream& operator<<(ostream& out, const Row& row)
{
  for (int i = 0; i < row.size(); i++)
    out << row[i] << "\t";
  return out;
}

double parse_double(string input)
{
  double temp;
  istringstream is(input);
  is >> temp;
  return temp;
}

istream& operator>>(istream& in, Row& row)
{
  string line;
  getline(in, line);
  StringTokenizer tokens(line, "\t");
  vector<double> temp;
  if(tokens.size() == 0 || line == "]")
    throw 0;
  for (int i = 0; i < tokens.size(); i++)
  {
    temp.push_back(parse_double(tokens[i]));
  }
  row.elements = temp;
  return in;
}
