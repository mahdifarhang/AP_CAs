#include "Thread.hpp"


Thread::Thread(int Type, Functor* Head)
{
  Thread_type = Type;
  *Top = *Head;
}
void BasicThread::do_step()
{

}
 void Recurren
