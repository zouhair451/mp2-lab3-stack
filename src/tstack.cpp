#include <iostream>
#include "tstack.h"
using namespace std;
int Stack::GetNextIndex(int index)
{
	return ++index;
}

void Stack::Put(const TData & val)
{
	if (IsFull()) SetRetCode(DataFull);
	else if (pMem == NULL) SetRetCode(DataNoMem);
	else
	{
		top = GetNextIndex(top);
		pMem[top] = val;
		DataCount++;
	}
}
TData Stack::Get()
{
	TData temp = -1;
	if (pMem == NULL) SetRetCode(DataNoMem);
	else if (IsEmpty()) SetRetCode(DataEmpty);
	else
	{
		temp = pMem[top--];
		DataCount--;
	}
	return temp;
}
TData Stack::TopElem()
{
	if (IsEmpty())
	{
		SetRetCode(DataEmpty);
		return -1;
	}
	else return pMem[top];
}
void Stack::Print()
{
	for (int i = 0; i<DataCount; ++i)
		cout << pMem[i] << " ";
	cout << endl;
}

int Stack::IsValid()
{
	int res = 0;
	if (pMem == NULL) res = 1;
	if (DataCount>MemSize) res += 2;
	return res;
}
