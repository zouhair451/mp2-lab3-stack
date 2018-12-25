// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdataroot.h - Copyright (c) Гергель В.П. 28.07.2000 (06.08)
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - базовый (абстрактный) класс - версия 3.2
//   память выделяется динамически или задается методом SetMem

#ifndef __DATAROOT_H__
#define __DATAROOT_H__

#include "tdatacom.h"

#define DefMemSize   30  // размер памяти по умолчанию

#define DataEmpty  -101  // СД пуста
#define DataFull   -102  // СД переполнена
#define DataNoMem  -103  // нет памяти

typedef char    TElem;    // тип элемента СД
typedef TElem* PTElem;
typedef char    TData;    // тип значений в СД

enum TMemType { MEM_HOLDER, MEM_RENTER };


template <class T>
class TDataRoot : public TDataCom
{
protected:
	T* pMem;      // память для СД
	int MemSize;      // размер памяти для СД
	int DataCount;    // количество элементов в СД
	TMemType MemType; // режим управления памятью

	void SetMem(void *p, int Size);             // задание памяти
public:
	virtual ~TDataRoot();
	TDataRoot(int Size = DefMemSize);
	virtual bool IsEmpty(void) const;           // контроль пустоты СД
	virtual bool IsFull(void) const;           // контроль переполнения СД
	virtual void  Put(const T &Val) = 0; // добавить значение
	virtual T Get(void) = 0; // извлечь значение

	// служебные методы
	virtual int  IsValid() = 0;                 // тестирование структуры
	virtual void Print() = 0;                 // печать значений

	// дружественные классы
	friend class TMultiStack;
	friend class TSuperMultiStack;
	friend class TComplexMultiStack;
};

template<class T>
void TDataRoot<T>::SetMem(void *p, int Size)
{
	if (MemType == MEM_HOLDER)
		delete[] pMem;
	pMem = (T*)p;
	MemType = MEM_RENTER;
	MemSize = Size;
}

template<class T>
TDataRoot<T>::~TDataRoot()
{
	if (MemType == MEM_HOLDER)
		delete[] pMem;
	pMem = NULL;
}

template<class T>
TDataRoot<T>::TDataRoot(int Size)
{
	if (Size < 0)
	{
		SetRetCode(DataErr);
		return;
	}
	MemSize = Size;
	DataCount = 0;
	if (MemSize == 0)
	{
		MemType = MEM_RENTER;
		pMem = NULL;
	}
	else
	{
		MemType = MEM_HOLDER;
		pMem = new T[MemSize];
	}
	SetRetCode(DataOK);
}

template<class T>
bool TDataRoot<T>::IsEmpty(void) const
{
	return DataCount == 0;
}

template<class T>
bool TDataRoot<T>::IsFull(void) const
{
	return DataCount == MemSize;
}

#endif
