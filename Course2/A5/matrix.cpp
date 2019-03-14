#include "matrix.h"

using namespace std;


Matrix::Matrix(int r, int c, double num)
{
  Row temp(c, num);
  for (int i = 0; i < r; i++)
    rows.push_back(temp);
}

Matrix::Matrix(int r, int c)
{
  Row temp(c);
  for (int i = 0; i < r; i++)
    rows.push_back(temp);
}

Matrix::Matrix(double input)
{
  Matrix(1, 1, input);
}

Matrix::Matrix(vector<Row> input)
{
  rows = input;
}

Matrix Matrix::operator+(const Matrix& operand) const
{
  if ((*this).height() != operand.height() || (*this).width() != operand.width())
    throw MatrixLengthExeption();
  Matrix temp((*this).height(), (*this).width());
  for (int i = 0; i < (*this).height(); i++)
    temp[i] = rows[i] + operand[i];
  return temp;
}

Matrix Matrix::operator*(const Matrix& operand) const
{
  if ((*this).width() != operand.height())
    throw MatrixMultExeption();
  vector<vector<double> > temp = vector<vector<double> >((*this).height(), vector<double>(operand.width(), 0));
  double sum = 0;
  for (int i = 0; i < (*this).height(); i++)
  {
    for (int j = 0; j < operand.width(); j++)
    {
      for (int k = 0; k < operand.height(); k++)
      {
        sum += (*this)[i][k] * operand[k][j];
      }
      temp[i][j] = sum;
      sum = 0;
    }
  }
  vector<Row> temp2;
  for (int i = 0; i < temp.size(); i++)
    temp2.push_back(temp[i]);
  return Matrix(temp2);
}

Matrix& Matrix::operator=(const Matrix& operand)
{
  if (operand.height() != this->height() || operand.width() != this->width())
    throw MatrixLengthExeption();
  (*this).rows = operand.rows;
  return *this;
}

Matrix& Matrix::operator=(const Row& operand)
{
  if (this->height() != 1 || operand.size() != this->width())
    throw MatrixLengthExeption();
  if (rows.size() == 0)
  {
    rows.push_back(operand);
  }
  else
  {
    for (int i = 0; i < rows.size() - 1; i++)
      rows.pop_back();
    rows[0] = operand;
  }
}

Matrix& Matrix::operator+=(const Matrix& operand)
{
  return ((*this) = (*this) + operand);
}

Matrix& Matrix::operator*=(const Matrix& operand)
{
  return ((*this) = (*this) * operand);
}

bool Matrix::operator==(const Matrix& operand) const
{
  if ((*this).height() != operand.height() || (*this).width() != operand.width())
    return false;
  for (int i = 0; i < operand.height(); i++)
    if (!(operand[i] == (*this)[i]))
      return false;
  return true;
}

Row Matrix::operator[](int i) const
{
  if (i >= rows.size() || i < 0)
    throw IndexOutOfBoundExeption();
  return rows[i];
}

Row& Matrix::operator[](int i)
{
  if (i >= rows.size() || i < 0)
    throw IndexOutOfBoundExeption();
  return rows[i];
}

int Matrix::height() const
{
  return rows.size();
}

int Matrix::width() const
{
  return rows[0].size();
}

void Matrix::insert(const Row& row, int i)
{
  if (row.size() != this->width())
    throw MatrixLengthExeption();
  if (i > this->height())
    throw IndexOutOfBoundExeption();
  rows.insert(rows.begin() + i, row);
}

Row operator*(const Row& row, const Matrix& matrix)
{
  vector<Row> temp;
  temp.push_back(row);
  Matrix temp2(temp);
  Matrix result(1);
  result = (temp2 * matrix);
  return result[0];
}

Matrix operator*(double num, const Matrix& matrix)
{
  vector<Row> temp;
  for (int i = 0; i < matrix.height(); i++)
    temp.push_back(num * matrix[i]);
  return Matrix(temp);
}

ostream& operator<<(ostream& out, const Matrix& matrix)
{
  out << '[' << "\n";
  for (int i = 0; i < matrix.height(); i++)
    out << matrix[i] << "\n";
  out << ']';
  return out;
}

istream& operator>>(istream& in, Matrix& matrix)
{
  string c;
  getline(in, c);
  vector<Row> v;
  Row temp(2);
  try
  {
    if(c != "[")
      throw 0;
    while(true)
    {
      in >> temp;
      v.push_back(temp);
    }
  }
  catch(...)
  {
  }
  matrix.rows = v;
  return in;
}
