#ifndef THREAD
#define THREAD

#include <vector>
#include "Functor.hpp"

#define BASIC_THREAD 1
#define RECURRENT_THREAD 2
#define SINGLERUN_THREAD 3

using namespace std;
class Thread {
public:
  Thread(int Type, Functor* Head);
  virtual void do_step() = 0;




private:
  Functor* Top;
  int Thread_type;
};
class BasicThread : public Thread {
public:
  void do_step();

};
class RecurrenThread : public Thread {
public:
  void do_step();

};
class SinglerunThread : public Thread {
public:
  void do_step();

};




#endif
