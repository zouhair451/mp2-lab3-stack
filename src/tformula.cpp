#include <cstring>
#include <cstdlib>
#include "tformula.h"
#include "tstack.h"
#include <iostream>

using namespace std;

TFormula::TFormula(char* form)
{
	if (strlen(form) > MaxLen)
		throw  "string length cant exceed MaxLen";
	strcpy(Formula, form);
	
	for (int i = 0; i < MaxLen; ++i)
	{
		PostfixForm[i] = 0;
	}
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	int NumErr = 0; // число ошибок

	TStack stack(size);

	int i; // счётчик для массива Formula
	int j; // счётчик для массива Brackets
	int num; // номер скобки

	for (i = 0, j = 0, num = 1; Formula[i] != '\0'; ++i)
	{
		if (Formula[i] != '(' && Formula[i] != ')' && Formula[i] != '+' &&
			Formula[i] != '-' && Formula[i] != '*' && Formula[i] != '/' &&
			!(Formula[i] >= '0' && Formula[i] <= '9') && Formula[i] != '.')
		{
			throw "formula contains invalid characters";
		}

		if (Formula[i] == '(')
		{
			stack.Put(num++);
			continue;
		}

		if (Formula[i] == ')')
		{
			if (stack.IsEmpty())
			{
				Brackets[j++] = 0;
				Brackets[j++] = num++;
				NumErr++;
			}
			else
			{
				Brackets[j++] = stack.Get();
				Brackets[j++] = num++;
			}
			continue;
		}
	}

	while (!stack.IsEmpty())
	{
		Brackets[j++] = stack.Get();
		Brackets[j++] = 0;
		NumErr++;
	}

	return NumErr;
}

int TFormula::FormulaConverter()
{
	int Brackets[255];

	if (FormulaChecker(Brackets, 255) != 0)
	{
		throw "brackets placement is wrong";
	}

	TStack stack(255);

	int i; // счётчик для массива Formula
	int j; // счётчик для массива PostfixForm
	int con; // условие для добавления пробела

	for (i = 0, j = 0; Formula[i] != '\0'; ++i)
	{
		con = 0;

		while (((Formula[i] >= '0' && Formula[i] <= '9') || Formula[i] == '.') && Formula[i] != '\0')
		{
			PostfixForm[j++] = Formula[i++];
			con = 1;
		}

		if (con == 1)
		{
			PostfixForm[j++] = ' ';
		}

		switch (Formula[i])
		{
		case '(':
			stack.Put(Formula[i]);
			break;

		case ')':
			while (stack.TopElem() != '(')
			{
				PostfixForm[j] = stack.Get(); // выталкиваем все элементы до открывающей скобки
				++j;
			}
			stack.Get(); // удаляем открывающую скобку
			break;

		case '+':
			sub:
			if (stack.IsEmpty() || (stack.TopElem() == '(') )
			{
				stack.Put(Formula[i]);
			}
			else
			{
				while (stack.TopElem() != '(') // выталкиваем все элементы, приоритет которых больше или равен приоритету операции сложения (вычитания)
				{
					PostfixForm[j] = stack.Get();
					++j;
				}
				stack.Put(Formula[i]); // кладём операцию сложения (вычитания) в стэк
			}
			break;

		case '-':
			goto sub; // переход в case +, действия аналогичные

		case '*':
			div:
			if (stack.IsEmpty() || (stack.TopElem() == '(') ||
				stack.TopElem() == '+' || stack.TopElem() == '-')
			{
				stack.Put(Formula[i]);
			}
			else
			{
				while ( (stack.TopElem() != '(') && (stack.TopElem() != '+') &&
					(stack.TopElem() != '-') ) // выталкиваем все элементы, приоритет которых больше или равен приоритету операции умножения (деления)
				{
					PostfixForm[j] = stack.Get();
					++j;
				}
				stack.Put(Formula[i]); // кладём операцию умножения (деления) в стэк
			}
			break;

		case '/':
			goto div; // переход в case *, действия аналогичные

		case '\0': // случай \0
			goto end;
		}
	}

	end:
	
	while (!stack.IsEmpty())
	{
		PostfixForm[j] = stack.Get();
		++j;
	}

	return 1;
}

double TFormula::FormulaCalculator()
{
	double DStack[255] = {0};

	int i; // счётчик для массива PostfixForm
	int j; // счётчик для массива DStack

	for (i = 0, j = 0; PostfixForm[i] != '\0'; ++i)
	{
		if (PostfixForm[i] >= '0' && PostfixForm[i] <= '9')
		{
			DStack[j++] = atof(PostfixForm + i);
			while (PostfixForm[i] != ' ')
			{
				++i;
			}
			continue;
		}

		switch (PostfixForm[i])
		{
		case '+':
			--j;
			DStack[j - 1] = DStack[j - 1] + DStack[j];
			DStack[j] = 0;
			break;

		case '-':
			--j;
			DStack[j - 1] = DStack[j - 1] - DStack[j];
			DStack[j] = 0;
			break;

		case '*':
			--j;
			DStack[j - 1] = DStack[j - 1] * DStack[j];
			DStack[j] = 0;
			break;

		case '/':
			--j;
			DStack[j - 1] = DStack[j - 1] / DStack[j];
			DStack[j] = 0;
			break;
		}
	}

	return DStack[0];
}