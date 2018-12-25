#include "tstack.h"
#include <stdexcept>
#include <iostream>


TStack::TStack(int Size) : TDataRoot(Size)
{
	top = -1;
}

TStack::TStack(const TStack & a)
{
	MemSize = a.MemSize;
	pMem = new int[MemSize];
	top = a.top;
	std::copy(a.pMem, a.pMem + MemSize, pMem);
}

void TStack::Put(const TData &Val)
{
	if (IsValid() < 0)
		throw "no memory";
	if (IsFull())
		throw "stack is full";
	else
	{
		pMem[++top] = Val;
		DataCount++;
	}
}

TData TStack::Get()
{
	if (IsValid() < 0)
		throw "no memory";
	if (IsEmpty())
		throw "stack is empty";
	else
	{
		DataCount--;
		return pMem[top--];
	}
}

TData TStack::TopElem()
{
	if (IsValid() < 0)
		throw "no memory";
	if (IsFull())
		throw "stack is full";
	else
		return pMem[top];
}

void TStack::Pop()
{
	if (IsValid() < 0)
		throw "no memory";
	if (IsFull())
		throw "stack is full";
	else
	{
		top--;
		DataCount--;
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
	for (int i = 0; i < MemSize; i++)
		std::cout << pMem[i];
	std::cout << "\n";
}

void TStack::Resize(int newsize)
{
	int *array = new int[newsize] {0};

	for (int i = 0; i < MemSize; i++)
		array[i] = pMem[i];

	delete[] pMem;
	pMem = array;

	MemSize = newsize;
}