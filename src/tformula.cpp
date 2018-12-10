#include <stdio.h>
#include <iostream>
#include "tstack.h"
#include "tformula.h"

int TFormula::FormulaChecker(int Brackets[], int size)
{
	int errors = 0; //Счетчик ошибок
	int r = 1; //порядковый номер скобки
	int n = 0; //позиция для записи в Brackets
	TStack stack(MaxLen);


	for (int i = 0; i < strlen(this->Formula); ++i)
	{
		if ((Formula[i] != '(') && (Formula[i] != ')'))
			continue;

		if (Formula[i] == '(')
		{
			stack.Put(r);
			++r;
		}
		if (Formula[i] == ')')
		{
			if (!stack.IsEmpty())
			{
				Brackets[n] = stack.Get();
				Brackets[n + 1] = r;
				++r;
				n += 2;
			}
			else
			{
				Brackets[n] = 0;
				Brackets[n + 1] = r;
				++r;
				n += 2;
				errors++;
			}
		}
	}

	if (!stack.IsEmpty())
	{
		while (!stack.IsEmpty())
		{
			Brackets[n] = stack.Get();
			Brackets[n + 1] = 0;
			n += 2;
			errors++;
		}
	}

	if (errors == 0)
		std::cout << "All Ok" << std::endl;
	else
		std::cout << "Total " << errors << " errors." << std::endl;
	
	for (int i = 0; i <= n; i+=2)
	{
		std::cout << Brackets[i] << "   " << Brackets[i + 1] << std::endl;
	}
}

bool IsOperation(char c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
		return true;
	else
		return false;
}

bool IsOperand(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

int GetPriority(char c)
{
	switch (c)
	{
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
	default: return -1;
	}
}

int TFormula::FormulaConverter()
{

	int br[MaxLen];

	if (!FormulaChecker(br , MaxLen))
		throw "Breckets err";

	TStack st(MaxLen);
	int i = 0;// для Formula
	int j = 0;// для PostfixFormula

	while (Formula[i])
	{
		// при появлении закрывающей скобки

		if (Formula[i] == ')')
		{
			while (st.TopElem() != '(')
			{
				PostfixForm[j] = st.Get();
				PostfixForm[j + 1] = ' ';
				j += 2;
				
			}

			st.Get();
			i++;
			continue;
		}

		//при появлении операнда
		if (IsOperand(Formula[i]) || Formula[i] == '.')
		{
			PostfixForm[j] = Formula[i];
			i++;
			j++;

			if (!IsOperand(Formula[i + 1]))
			{
				PostfixForm[j] = ' ';//разделяем операнды и операции
				j++;
			} 

			continue;
		}

		//при появлении операции

		if (IsOperation(Formula[i]))
		{
			if ( (GetPriority(Formula[i]) == 0) || (GetPriority(Formula[i]) >(GetPriority( st.TopElem() ) ) ) || st.IsEmpty() )
			{
				st.Put(Formula[i]);
				i++;
			}

			else
			{
				while (!st.IsEmpty()  && (GetPriority(Formula[i]) <= GetPriority(st.TopElem()) ) )
				{
					PostfixForm[j] = st.Get();
					PostfixForm[j+1] = ' ';
					j += 2;
					
				}
			}
			continue;
		}
	}
	

	while (!st.IsEmpty())
	{
		PostfixForm[j] = st.Get();
		PostfixForm[j + 1] = ' ';
		j += 2;
	}

	PostfixForm[j] = '\0';
	j = 0;

	while (PostfixForm[j] != '\0')
	{
		std::cout << PostfixForm[j];
	}
	std::cout << std::endl;
}

double TFormula::FormulaCalculator()
{
	if (PostfixForm[0] == '\0')
		this->FormulaConverter();
	double stack[MaxLen] = { 0 };

	double op1;
//	double op2;

	int top = -1;
	int i = 0;
	while (PostfixForm[i] != '\0')
	{
		if (IsOperand(PostfixForm[i]))
		{
			top++;
			stack[top] = atof(PostfixForm + i);

			while (PostfixForm[i] != ' ')
				i++;
			i++;
		}

		if (IsOperation(PostfixForm[i]))
		{
			switch (PostfixForm[i])
			{
			case '*':
				op1 = stack[top];
				top--;
				stack[top] *= op1;
				break;

			case '/':
				op1 = stack[top];
				top--;
				stack[top] = op1 / stack[top];
				break;

			case '+':
				op1 = stack[top];
				top--;
				stack[top] += op1;
				break;

			case '-':
				op1 = stack[top];
				top--;
				stack[top] = op1 - stack[top];
				break;
			
			default:
				break;
			}
		}

	}

	return stack[top];

}