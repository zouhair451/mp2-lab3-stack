include<iostream>
#include "tstack.h"

TStack::TStack(int len) :TDataRoot(len)
{
	top = -1;
	for (int i = 0; i < MemSize; i++)
		pMem[i] = 0;
}
TStack::TStack(const TStack& obj)
{
	MemSize = obj.MemSize;
	top = obj.top;
	pMem = new int[MemSize];
	std::copy(obj.pMem, obj.pMem + MemSize, pMem);
}
void TStack::Put(const TData &elem)
{
	if (pMem == nullptr)
		SetRetCode(DataNoMem);
	if (!IsFull())
	{
		pMem[++top] = elem;
		DataCount++;
	}
	else
	{
		SetRetCode(DataFull);
		throw "Stack is full";
	}
}
void TStack::Pop()
{
	if (pMem == nullptr)
		SetRetCode(DataNoMem);
	if (!IsEmpty())
	{
		top--;
		DataCount--;
	}
	else
	{
		SetRetCode(DataEmpty);
		throw "Stack is empty";
	}
}
TData TStack::Get()
{
	if (pMem == nullptr)
		SetRetCode(DataNoMem);
	if (!IsEmpty())
		return pMem[top];
	else
	{
		SetRetCode(DataEmpty);
		throw "Stack is empty";
	}
}
void TStack::Resize(int newLen)
{
	if (newLen > 0)
	{
		if (pMem != nullptr)
		{
			int* arr = new int[newLen];
			for (int i = 0; i < newLen; i++)
				arr[i] = 0;
			std::copy(pMem, pMem + MemSize, arr);
			delete[] pMem;
			pMem = arr;
		}
		else
			pMem = new int[newLen];
		MemSize = newLen;
		MemType = MEM_HOLDER;
	}
	else if (newLen == 0)
	{
		if (pMem != nullptr)
			delete[] pMem;
		MemSize = newLen;
		MemType = MEM_RENTER;
	}
	else
		throw "Wrong size of Stack";

}

int TStack::IsValid()
{
	if (pMem == NULL)
	{
		std::cout << "Stack don't have memory";
		return 1;
	}
	if (MemSize >= DataCount)
	{
		for (int i = 0; i < DataCount; i++)
			std::cout << pMem[i] << std::endl;
		std::cout << "Stack is Valid" << std::endl;
		this->Get();
		this->Pop();
		return 1;
	}
	else
		return 0;

}

void TStack::Print()
{
	std::cout << "top -> " << pMem[top] << std::endl;
	for (int i = top - 1; i > 0; i--)
		std::cout << pMem[i] << std::endl;
}
