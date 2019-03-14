#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

class Shape
{
public:
  Shape();
  Shape(unsigned double _opacity, double _rotate);
  virtual void move(double dx, double dy) = 0;
protected:
  std::string name;
  unsigned double opacity;
  double rotate;
};
















#endif
