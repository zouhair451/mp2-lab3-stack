// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - тестирование стека

#include <iostream>
#include "tformula.h"

using namespace std;

int main()
{
  TStack st(2);
  int temp;

  cout << "\033[91m\tStack testing\033[0m" << endl;
  for (int i = 0; i < 35; i++)
  {
    try
    {
      st.Put(i);
      cout << "\033[91m\tPut \033[0m" << i << "\033[91m Code \033[0m" << st.GetRetCode() << endl;
    }
    catch (const std::exception&)
    {
      continue;
    }
  }
  while (!st.IsEmpty())
  {
    temp = st.Get();
    cout << "\033[91m\tGot \033[0m" << temp << "\033[91m Code \033[0m" << st.GetRetCode() << endl;
  }
  cout << endl << endl;

  TFormula formula("((3+4)*6-3*(4-6))-5");
  formula.FormulaCalculator();
  return 0;
}
