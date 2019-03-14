#include "Functor.hpp"

Functor::Functor()
{
  is_done = false;
  returnval = 0;
}
void Functor::CheckAvailableForDoing()
{
  for (int i = 0 ;i < children.size() ;i++)
  {
    if(!children[i]->check_done())
      children[i]->CheckAvailableForDoing();
      return NULL;
  }
  this->doing();
  is_done = true;
}
void Cin::doing()
{
  if (children.size() == 0)
  {
    cout << "Enter the number:" << endl;
    cin >> returnval;
  }
  else
    throw -1;
}
void Cout::doing()
{
  if (children.size() == 1)
    cout << children[0] << endl;
  else
    throw -1;
}
void Add::doing()
{
  if(children.size() == 2)
    returnval = children[0]->returnval + children[1]->returnval;
  else
    throw -1;
}
void Multiply::doing()
{
  if (children.size() == 2)
    returnval = children[0]- >returnval * children[1]->returnval;
  else
    throw -1;
}
void If::doing()
{
  if (children.size() == 3)
  {
    if (children[0])
      returnval children[1];
    else
      returnval children[2];
  }
  else
    throw -1;
}
void Negative::doing()
{
  if (children.size() == 1)
    returnval = -returnval;
  else
    throw -1;
}
