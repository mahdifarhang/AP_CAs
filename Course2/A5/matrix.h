#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <iostream>
#include "row.h"
#include "error.h"

class Matrix
{
public:
  Matrix() {}
  Matrix(int, int, double);
  Matrix(int, int);
  Matrix(double);
  Matrix(std::vector<Row>);

  Matrix operator+(const Matrix&) const;
  Matrix operator*(const Matrix&) const;
  Matrix& operator=(const Matrix&);
  Matrix& operator=(const Row&);
  Matrix& operator+=(const Matrix&);
  Matrix& operator*=(const Matrix&);
  bool operator==(const Matrix&) const;
  Row operator[](int) const;
  Row& operator[](int);
  int height() const;
  int width() const;
  void insert(const Row&, int);

  friend Row operator*(const Row&, const Matrix&);
  friend Matrix operator*(double, const Matrix&);
  friend std::istream& operator>>(std::istream&, Matrix&);
private:
  std::vector<Row> rows;
};

Row operator*(const Row&, const Matrix&);
Matrix operator*(double, const Matrix&);
std::ostream& operator<<(std::ostream&, const Matrix&);
std::istream& operator>>(std::istream&, Matrix&);

#endif
