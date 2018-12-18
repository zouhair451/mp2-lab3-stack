#include <stdio.h>
#include "tstack.h"
#include <iostream>


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
		std::cout << "Put " << Val << std::endl;
	}
}

TData TStack::Get()
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
		return 0;
	}
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
		return 0;
	}
	else
	{
		DataCount--;
		std::cout<<"Get " << pMem[top] << std::endl;
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
	return GetRetCode();
}

void TStack::Print()
{
	for (int i = 0; i < DataCount; ++i)
		std::cout << pMem[i] << " ";
	std::cout << "\n";
}

