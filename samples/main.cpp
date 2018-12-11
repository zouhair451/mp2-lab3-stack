/* // this main.cpp is a sample for tstack.cpp
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - тестирование стека

#include <iostream>
//#include "tstack.h"
#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tstack.h"

using namespace std;

int main() // this main() is for Stack of int!!! Change typedef TElem in the file tdataroot.h
{
  TStack st(2);
  int temp;

  setlocale(LC_ALL, "Russian");
  //cout << "Тестирование программ поддержки структуры типа стек: " << endl;
  cout << "Testing of stack structure supporting: " << endl;
  for (int i = 0; i < 3; i++)
  {
      try{
    st.Put(i);
    //cout << "Положили значение " << i << " Код " << st.GetRetCode() << endl;
    cout << "Put the value " << i << " Code " << st.GetRetCode() << endl;
      }
      catch ( const char * excep)
      {
          cout << excep << endl;
            break;
      }
  }
  while (!st.IsEmpty())
  {
      try{
    temp = st.Get();
    //cout << "Взяли значение " << temp << " Код " << st.GetRetCode() << endl;
    cout << "Got the value " << temp << " Code " << st.GetRetCode() << endl;
      }
      catch( const char * excep)
      {
            cout << excep << endl;
            break;
      }
  }
 // system("pause");
  return 0;
}
*/
