// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - тестирование стека

#include <iostream>
#include<string>
#include "../include/tstack.h"
#include"../include/tformula.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	cout << "Testing Class TFormula: " << endl;
	string str1[4] = { "(2+3)*6*4/8-(2+5)/16","2+2*(6-3)/4","7+(3*10)-2","15/5-3+8" };
	int size = 0;
	int* brackets = nullptr;
	TFormula * f = new TFormula[4]
	{
		str1[0], 
		str1[1], 
		str1[2],
		str1[3]
	};
	for (int i = 0; i < 4; i++)
	{
		cout << "Formula " << i + 1 << ": " << str1[i] << endl;
		size = str1[i].length() * 2; 
		if (brackets != nullptr)
			delete[] brackets;
		brackets = new int[size];
		for (int i = 0; i < size; i++)
			brackets[i] = 0;
		cout << "\nresult of calculation = " << f[i].FormulaCalculator() << endl;
		for (int i = 0; i < 30; i++)
			cout << "*";
		cout << endl;
	}
	delete[] brackets;
	delete[] f;
	system("pause");
  return 0;
}