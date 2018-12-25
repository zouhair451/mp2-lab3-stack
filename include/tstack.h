#ifndef __TSTACK_H__
#define __TSTACK_H__

#include "tdataroot.h"

class TStack : public TDataRoot<char>
{
protected:
	int Hi;

public:
	TStack(int Size);
	int GetHi();
	~TStack();
	void Put(const TData & Val);
	TData Get();
	TData& operator[](int i);

	int IsValid();
	void Print();
};

class TStack_d : public TDataRoot<double>
{
protected:
	int Hi;

public:
	TStack_d(int Size);
	int GetHi();
	~TStack_d();
	void Put(const double & Val);
	double Get();
	double& operator[](int i);

	int IsValid();
	void Print();
};

#endif


