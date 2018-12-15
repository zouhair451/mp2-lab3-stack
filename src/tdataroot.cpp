#include <stdio.h>
#include "tdataroot.h"

TDataRoot::TDataRoot(int Size): TDataCom()
{
  DataCount = 0;
  MemSize = Size;
  if (Size == 0) // память будет установлена методом SetMem
  {
    pMem = NULL;
    MemType = MEM_RENTER;
  }
  else // память выделяется объектом
  {
    pMem = new TElem[MemSize];
    MemType = MEM_HOLDER;
  }
} /*-------------------------------------------------------------------------*/

TDataRoot::~TDataRoot()
{
  if (MemType == MEM_HOLDER)
    delete [] pMem;
  pMem = NULL;
} /*-------------------------------------------------------------------------*/

void TDataRoot::SetMem(void *p, int Size) // задание памяти
{
  if (MemType == MEM_HOLDER)
    delete [] pMem; // ! информация не сохраняется
  pMem = (TElem*) p;
  MemType = MEM_RENTER;
  MemSize = Size;
} /*-------------------------------------------------------------------------*/

bool TDataRoot::IsEmpty(void) const // контроль пустоты СД
{
  return DataCount == 0;
} /*-------------------------------------------------------------------------*/

bool TDataRoot::IsFull(void) const // контроль переполнения СД
{
  return DataCount == MemSize;
} /*-------------------------------------------------------------------------*/