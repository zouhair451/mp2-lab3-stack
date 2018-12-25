#include "tstack.h"
#include <iostream>
#include <algorithm>

TStack::TStack(int size) : top(-1)
{
  if (size == 0)
  {
    MemSize = DefMemSize;
    pMem = new int[MemSize];
  }
  else if (size > 0)
  {
    MemSize = size;
    pMem = new int[MemSize];
  }
  else
    throw "ERR";
}

/*-----------------------------------------------*/
TStack::TStack(const TStack & obj)
{
  MemSize = obj.MemSize;
  pMem = new int[MemSize];
  std::copy(pMem, pMem, obj.pMem);
  top = obj.top;
}
/*-----------------------------------------------*/
void TStack::Put(const TData &val)
{
  if (this->IsFull())
    SetRetCode(DataErr);
  else
  {
    pMem[++top] = val;
    DataCount++;
  }
}
/*-----------------------------------------------*/
TData TStack::Get()
{
  if (top != -1)
  {
    DataCount--;
    return pMem[top--];
  }
  else
  {
    SetRetCode(DataErr);
    return DataEmpty;
  }
}
/*-----------------------------------------------*/
TData TStack::TopElem()
{
  if (top != -1)
    return pMem[top];
  else
  {
    SetRetCode(DataErr);
    return DataEmpty;
  }
}
/*-----------------------------------------------*/
int TStack::IsValid()
{
  int res = 0;
  
  if (pMem == NULL)          res = 1;
  if (MemSize < DataCount)   res += 2;
  
  return res;
}
/*-----------------------------------------------*/
void TStack::Print()
{
  for (int i = 0; i < DataCount; i++)
    std::cout << pMem[i];
  std::cout << std::endl;
}
