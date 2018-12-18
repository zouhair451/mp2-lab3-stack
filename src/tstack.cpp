#include <iostream>
#include "tstack.h"

using namespace std;

TStack::TStack(int Size) : TDataRoot(Size)
{
	top = -1;
}

void TStack::Put(const TData & Val)
{
	if (pMem == nullptr) SetRetCode(DataNoMem);
	else if (IsFull()) {
		SetRetCode(DataFull);
		throw "cant_put_elem_when_its_full";
	}
	else {
		DataCount++;
		pMem[++top] = Val;
	}
}

TData TStack::Get()
{
	TData  tmp = -1;
	if (pMem == nullptr) SetRetCode(DataNoMem);
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
		throw "cant_get_elem_when_its_empty";
	}
	else {
		tmp = pMem[top--];
		DataCount--;
	}
	return tmp;
}

TData TStack::TopElem()
{
	TData  tmp = -1;
	if (pMem == nullptr) SetRetCode(DataNoMem);
	else if (IsEmpty()) SetRetCode(DataEmpty);
	else {
		tmp = pMem[top];
	}

	return tmp;
}

int TStack::IsValid() //тестиорование структуры
{
	/*int res = 0;
	if (pMem == nullptr) res = 1;
	if (MemSize < DataCount) res += 2;
	return res;*/
	return GetRetCode();
}

void TStack::Print()
{
	if (pMem == nullptr) SetRetCode(DataNoMem);
	else if (IsEmpty()) SetRetCode(DataEmpty);
	else {
		for (int i = 0; i < DataCount; i++) {
			cout << pMem[i] << ' ';
		}
	}
}