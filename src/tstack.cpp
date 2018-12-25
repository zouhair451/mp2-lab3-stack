#include <iostream>
#include "tstack.h"

TStack::TStack(int Size) {
	if (Size < 1)
		throw - 1;
	this->pMem = new TData[Size];
	this->MemSize = Size;
	this->DataCount = 0;
}

void TStack::Put(const TData& Val) {
	if (!IsFull()) {
		RetCode = DataOK;
		pMem[DataCount++] = Val;
	}
	else {
		RetCode = DataFull;
	}
}
TData TStack::Get() {
	if (!IsEmpty()) {
		RetCode = DataOK;
		return pMem[--DataCount];
	}
	else {
		RetCode = DataEmpty;
	}
}

int TStack::IsValid() {
	return true;
}

void TStack::Print() {
	for (int i = 0; i < DataCount; ++i)
		std::cout << (char)pMem[i] << " ";
	std::cout << "\n";
}

TData TStack::TopElem() {
	if (!IsEmpty()) {
		RetCode = DataOK;
		return pMem[DataCount - 1];
	}
	else {
		RetCode = DataEmpty;
	}
}
