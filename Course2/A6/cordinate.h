#ifndef CORDINATE_H_
#define CORDINATE_H_

class Cordinate
{
public:
  Cordinate(double _x, double _y) : x(_x) , y(_y) {}
  void move(double dx, double dy);
private:
  double x;
  double y;
};

#endif
