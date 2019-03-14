#ifndef FUNCTOR
#define FUNCTOR

#include <vector>
#include <iostream>

using namespace std;

class Functor {
public:
  Functor();
  virtual void doing() = 0;
  void CheckAvailableForDoing();
  bool check_done(){return is_done;}
  int returnresult(){return returnval;}
protected:
  vector<Functor*> children;
  int returnval;
  bool is_done;
};
class Cin : public Functor {
public:
  void doing();
};
class Cout : public Functor {
public:
  void doing();
};
class Add : public Functor {
public:
  void doing();
};
class Multiply : public Functor {
public:
  void doing();
};
class If: public Functor {
public:
  void doing();
};
class Negative : public Functor {
public:
  void doing();
};

#endif
