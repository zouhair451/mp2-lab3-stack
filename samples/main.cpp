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
	cout << "Test TFormula: " << endl;
	string str1[4] = { "(11+19)/2+(15-5)+15" };
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
		cout << "F " << i + 1 << ": " << str1[i] << endl;
		size = str1[i].length() * 2;
		if (brackets != nullptr)
			delete[] brackets;
		brackets = new int[size];
		for (int i = 0; i < size; i++)
			brackets[i] = 0;
		cout << "\R = " << f[i].FormulaCalculator() << endl;
	}
	delete[] brackets;
	delete[] f;
	system("pause");
	return 0;
}
