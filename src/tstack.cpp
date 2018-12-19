#include <iostream>
#include "tstack.h"

TStack::TStack(int Size):TDataRoot(Size)
{
	top = -1;
}

void TStack::Put(const TData &Val)
{
	if (pMem == NULL)
	{
		SetRetCode(DataNoMem);
		
	}
	else if (IsFull())
	{
		SetRetCode(DataFull);
	}
	else
	{
		pMem[++top] = Val;
		DataCount++;
	}
}

TData TStack::Get()
{
	if (pMem == NULL)
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
	if (pMem == NULL)
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
	return GetRetCode() == DataOK ? true : false;
}

void TStack::Print()
{
	for (int i = 0; i < DataCount; ++i)
	{
		std::cout << pMem[i] << " ";
	}
	std::cout << std::endl;
}