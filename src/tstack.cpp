#include "tstack.h"
#include <iostream>

TStack::TStack(int Size):TDataRoot(Size)
{
    top=0;
}

void TStack::Put(const TData &Val)
{
    if (pMem==NULL)
    {
        SetRetCode(DataNoMem);
        return;
    }
    if (IsFull())
    {
        SetRetCode(DataFull);
        return;
    }
    ++DataCount;
    pMem[top++]=Val;
}

TData TStack::Get(void)
{
    if (pMem==NULL)
    {
        SetRetCode(DataNoMem);
        throw -1;
    }
    if (IsEmpty())
    {
        SetRetCode(DataEmpty);
        throw -1;
    }
    --DataCount;
    return pMem[--top];
}

TData TStack::TopElem()
{
    if (pMem==NULL)
    {
        SetRetCode(DataNoMem);
        throw -1;
    }
    if (IsEmpty())
    {
        SetRetCode(DataEmpty);
        throw -1;
    }
    return pMem[top-1];
}

int TStack::IsValid()
{
    return GetRetCode();
}

void TStack::Print()
{
    for (int i=0;i<top;++i)
        std::cout << (TData)pMem[i] << ' ';
}
