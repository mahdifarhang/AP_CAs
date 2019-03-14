#include "shape.h"

using namespace std;

Shape::Shape()
{
  opacity = 100;
  rotate = 0;
}
Shape(unsigned double _opacity, double _rotate)
{
  opacity = _opacity;
  rotate = _rotate;
}
