#include "tdataroot.h"

class TStack :public TDataRoot
{
private:
	int top; // index of the last added element
public:
    TStack(int Size = DefMemSize);
    ~TStack() {};
	void Put(const TData &Val);
	TData Get();
	virtual TData TopElem();

	int IsValid();
    void Print();
};
