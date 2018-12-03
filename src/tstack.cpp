#include "tstack.h"
#include <stdexcept>
#include <iostream>

TStack::TStack(int Size): TDataRoot(Size)
{
    top = -1;
}

void TStack::Put(const TData& Val)
{
    if (IsValid() < 0)
        throw std::logic_error("No memory");

    if (IsFull())
    {
        SetRetCode(DataFull);
        throw std::range_error("Stack is full");
    }
    else
    {
      pMem[++top] = Val;
      DataCount++;
      SetRetCode(DataOK);
    }
}

TData TStack::Get()
{
    if (IsValid() < 0)
        throw std::logic_error("No memory");

    if (IsEmpty())
    {
      SetRetCode(DataEmpty);
      throw std::range_error("Stack is empty");
    }
    else
    {
      SetRetCode(DataOK);
      DataCount--;

      auto temp = pMem[top];
      pMem[top--] = 0;
      return temp;
    }
}

TData TStack::TopElem()
{
    if (IsValid() < 0)
        throw std::logic_error("No memory");

    if (IsEmpty())
    {
        SetRetCode(DataEmpty);
        throw std::logic_error("Stack is empty");
    }
    else
    {
      return pMem[top];
    }
}

int TStack::IsValid()
{
    if (pMem == NULL)
        return SetRetCode(DataNoMem);
    if (MemSize == 0)
        return SetRetCode(DataNoMem);
    return 1;
}

void TStack::Print()
{
    if (IsValid() < 0)
        throw std::logic_error("No memory");

    if (IsEmpty())
    {
        SetRetCode(DataEmpty);
        throw std::logic_error("Stack is empty");
    }

    for (auto i = 0; i < DataCount; i++)
        std::cout << pMem[i] << " " << std::endl;
}