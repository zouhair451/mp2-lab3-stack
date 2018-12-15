#include <stdio.h>
#include <iostream>
#include "tstack.h"
//#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tstack.h"

using namespace std;

    TStack::TStack(int Size)
    {
        if (Size < 0)
            throw "negative size of stack";
        DataCount = 0;
        MemSize = Size;
        pMem = new TElem[MemSize];
        top = -1; // stack is empty
    }

	void TStack::Put(const TData &Val)
	{
		top = top + 1;
	    if (top == MemSize)
            {
                top = top -1; // if the exception is thrown, the next call of Get() may return garbage instead of real top. we must decrease i to avoid it
                throw "DataFull";
            }
        pMem[top] = Val;
        DataCount++;
	}

	TData TStack::Get()
	{
	    if (top == -1)
            throw "DataEmpty";
		top = top - 1;
        DataCount--;
        return pMem[top + 1]; // equal "return and than decrease"
	}
	TData TStack::TopElem()
	{
	    if (top < 0)
            throw "StackIsEmptyDuringTopElemCall";
	    return pMem[top];
	}

	int TStack:: IsValid()
	{
	    return 1;
	}

    void TStack:: Print()
    {
        for (int i = 0; i < top; i++)
        {
            cout << pMem[i] << " " ;
        }
    }
