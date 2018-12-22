#pragma once
#include"tdataroot.h"
class TStack : public TDataRoot
{
protected:
	int top; 
	int* mem;
public:
	TStack(int len);
	TStack(const TStack& obj);
	~TStack() {};
	int GetSize() { return MemSize; }
	void Put(const TData &elem);
	TData Get();
	void Pop();
	void Resize(int newLen);
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == MemSize - 1; }
	virtual int  IsValid();                 
	virtual void Print();             
};