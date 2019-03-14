#ifndef ROW_H_
#define ROW_H_

#include <vector>
#include <iostream>
#include "error.h"

class Row
{
public:
  Row() {}
  Row(int);
  Row(int, double);
  Row(std::vector<double>);
  int size() const;
  Row operator+(const Row&) const;
  Row& operator=(const Row&);
  Row& operator=(const std::vector<double>&);
  Row& operator+=(const Row&);
  double operator[](int) const;
  double& operator[](int);
  bool operator==(const Row&) const;



  friend Row operator*(double, const Row&);
  friend std::ostream& operator<<(std::ostream&, const Row&);
  friend std::istream& operator>>(std::istream&, Row&);

private:
  std::vector<double> elements;
};

Row operator*(double, const Row&);
std::ostream& operator<<(std::ostream&, const Row&);
std::istream& operator>>(std::istream&, Row&);




#endif
