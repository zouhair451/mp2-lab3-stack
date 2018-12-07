#include "tstack.h"
#include <iostream>

using namespace std;

TStack::TStack(int Size):TDataRoot(Size)
{
    top = -1;
}

void TStack::Put(const TData &Val)
{
    if(pMem == NULL)
        SetRetCode(DataNoMem);
    else if(IsFull())
        SetRetCode(DataFull);
    else
    {
        pMem[++top] = Val;
        ++DataCount;
    }
}

TData TStack::Get()
{
    TData tmp = -1;
    if(pMem == NULL)
        SetRetCode(DataNoMem);
    else if(IsEmpty())
        SetRetCode(DataEmpty);
    else
    {
       tmp = pMem[top--];
       --DataCount;
    }
    return tmp;
}

TData TStack::TopElem()
{
    if(pMem == NULL)
    {
        SetRetCode(DataNoMem);
        return -1;
    }
    else if(IsEmpty())
    {
        SetRetCode(DataEmpty);
        return -1;
    }
    else
        return pMem[top];
}

int TStack::IsValid()
{
    return GetRetCode();
}

void TStack::Print()
{
    for(int i = 0; i <= top; i++)
        cout<<pMem[i]<<" ";
    cout<<"\n";
}
