#ifndef __STACK_H__
#define __STACK_H__

#include "tdataroot.h"

class Stack:public TDataRoot
{
protected:
    int top;
    virtual int GetNextIndex (int index);
public:
    virtual void Print();
    virtual int IsValid();
    Stack (int Size =  DefMemSize ) : TDataRoot(Size) {top=-1;};
    virtual TData TopElem();
    virtual void Put(const TData&Val);
    virtual TData Get();
};
#endif
