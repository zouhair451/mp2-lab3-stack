#include <iostream>
#include "tstack.h"

using namespace std;

TStack::TStack(int Size)
{
	if (Size < 0)
		throw - 1;
	this->pMem = new TData[Size];
	this->MemSize = Size;
	this->DataCount = 0;
}

void TStack::Put(const TData &Val)
{
	if (!IsFull())
	{
		RetCode = DataOK;
		pMem[DataCount] = Val;
		DataCount++;
	}
	else RetCode = DataFull;
}

TData TStack::Get()
{
	if (!IsEmpty())
	{
		RetCode = DataOK;
		int tmp = pMem[DataCount - 1];
		DataCount--;
		return tmp;
	}
	else RetCode = DataEmpty;
}

TData TStack::TopElem()
{
	if (!IsEmpty())
	{
		RetCode = DataOK;
		return pMem[DataCount - 1];
	}
	else RetCode = DataEmpty;
}

int TStack::IsValid()
{
	return 1;
}

void TStack::Print()
{	
	for (int i = 0; i < DataCount; i++)
		cout << pMem[i] << " ";
	cout << endl;
}