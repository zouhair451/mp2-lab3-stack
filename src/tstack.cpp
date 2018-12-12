#include"tstack.h"

#include<iostream>
#include<algorithm>

TStack::TStack(int Size) : TDataRoot(Size), top(-1) {}

void TStack::Put(const TData &Val)
{
  if (TDataRoot::IsFull())
    throw DataFull;

  TDataRoot::DataCount++;

  if (TDataRoot::IsFull())
    TDataCom::SetRetCode(DataFull);

  TDataRoot::pMem[++top] = Val;
}

TData TStack::Get()
{
  if (TDataRoot::IsEmpty())
    throw DataEmpty;

  TDataRoot::DataCount--;

  if (TDataRoot::IsEmpty())
    TDataCom::SetRetCode(DataEmpty);

  return TDataRoot::pMem[top--];
}

TData TStack::TopElem() const
{
  if (TDataRoot::IsEmpty())
    throw DataEmpty;
  
  return TDataRoot::pMem[top];
}

int TStack::IsValid()
{
  return 1;
}

void TStack::Print()
{
  std::cout << "{ ";
  for (int i = 0; i < top; ++i)
    std::cout << TDataRoot::pMem[i] << "; ";
  std::cout << "}";
}