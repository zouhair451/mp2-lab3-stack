// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - тестирование стека

#include <iostream>
#include "tstack.h"
#include "tformula.h"

using namespace std;

int main()
{
  /*TStack st(2);
  int temp;

  cout << "Stack testing" << endl;
  for (int i = 0; i < 35; i++)
  {
    st.Put(i);
    cout << "Put " << i << " Code " << st.GetRetCode() << endl;
  }
  while (!st.IsEmpty())
  {
    temp = st.Get();
    cout << "Got " << temp << " Code " << st.GetRetCode() << endl;
  }*/

  TFormula formula("((3+4)*6-1*(4-6))-5");
  formula.FormulaCalculator();
  system("pause");
  return 0;
}
