#include "tdataroot.h"

class TStack :public TDataRoot
{
private:
	int top; 
public:
    TStack(int size);
	TStack(const TStack &obj);
	void Put(const TData &Val); 
	TData Get();
	virtual TData TopElem(); 

	int IsValid();
    void Print();
};