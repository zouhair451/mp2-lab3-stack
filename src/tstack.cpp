#include <stdio.h>
#include "tstack.h"
#include <iostream>


TStack::TStack(int Size = DefMemSize) : TDataRoot(Size)
{
	if (Size < 1)
		throw - 1;
	top = -1;
}

void TStack::Put(const TData &Val)
{
	if (!IsFull())
	{
		(this->top)++;
		pMem[(this->top)] = Val;
		(this->DataCount)++;
	}
	else
	{
		RetCode = DataFull;
	}
}

TData TStack::Get()
{
	if (!IsEmpty())
	{
		RetCode = DataOK;
		this->DataCount--;
		return this->pMem[top--];
	}
	else
	{
		this->RetCode = DataEmpty;
	}
}

TData TStack::TopElem()
{
	if (!IsEmpty())
	{
		RetCode = DataOK;
		return this->pMem[top];
	}
	else
		RetCode = DataEmpty;

}

int TStack::IsValid() 
{
	return true;
}

void TStack::Print()
{
	for (int i = 0; i < DataCount; ++i)
		std::cout << (char)pMem[i] << " ";
	std::cout << "\n";
}