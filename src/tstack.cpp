#include <iostream>
#include "tstack.h"

using namespace std;

TStack::TStack(int Size) : TDataRoot(Size)
{
	top = -1;
}

void TStack::Put(const TData &Val)
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
	}
	else if (IsFull())
	{
		SetRetCode(DataFull);
	}
	else
	{
		DataCount++;
		pMem[++top] = Val;
	}
}

TData TStack::Get()
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
	}
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}
	else
	{
		DataCount--;
		return pMem[top--];
	}
}

TData TStack::TopElem()
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
	}
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}
	else
	{
		return pMem[top];
	}
}

int TStack::IsValid()
{
	return 1;
}

void TStack::Print()
{	
	for (int i = 0; i < DataCount; i++)
	{
		cout << pMem[i] << ' ';
	}
}