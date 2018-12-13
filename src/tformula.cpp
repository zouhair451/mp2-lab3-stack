#include <iostream>
#include "tformula.h"
#include "tstack.h"
#include "stdlib.h"
using namespace std;

TFormula::TFormula(char *form)
{
	int i = 0;
	char *j = form;
	int k = 0;
	while (*j) j++;
	int len = j - form;
	for (i = 0; i < len; i++)
	{
		this->Formula[i] = form[i];
	}
	for (i = len; i < MaxLen; i++)
		Formula[i] = 'a';
	for (i = 0; i < MaxLen; i++)
		PostfixForm[i] = 0;
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	TStack brack(MaxLen);
	int k = 0;
	int i = 0;
	int err = 0;
	while (Formula[i] != 'a')
	{
		if (Formula[i] == '(')
		{
			brack.Put(k);
			k++;
		}
		else if (Formula[i] == ')')
		{
			if (brack.IsEmpty())
			{
				err++;
				if (k < size)
				{
					Brackets[k] = -1;
					k++;
				}
			}
			else
			{
				if (k < size)
				{
					Brackets[k] = brack.TopElem();
					Brackets[brack.Get()] = k;
					k++;
				}
			}
		}
		i++;
	}
	if (!brack.IsEmpty())
	{
		while (!brack.IsEmpty())
			Brackets[brack.Get()] = -1;
		err++;
	}
	return err;
}

int Priority(char op)
{
	if (op == '(') return 0;	
	if ((op = ')')) return 1;
	if ((op == '+') || (op = '-')) return 2;
	if ((op == '*') || (op = '/')) return 3;
	return -1;
}



int TFormula::FormulaConverter()
{
	int brack[MaxLen];
	if (FormulaChecker(brack, MaxLen))
		throw - 1;
	TStack stack(MaxLen);
	int j = 0;
	char thrash;
	int len = 0;
	while (Formula[len] != 'a')
		len++;
	for (int i = 0; i < len; i++)
	{
		if (Formula[i] == ')')
		{
			while (stack.TopElem() != '(')
			{
				PostfixForm[j++] = stack.Get();
				PostfixForm[j++] = ' ';
			}
			thrash = stack.Get();
			if (!stack.IsEmpty()) PostfixForm[j++] = stack.Get();
			continue;
		}
		else
		if ((Formula[i] >= '0') && (Formula[i] <= '9'))
		{  
			while ((Formula[i] >= '0') && (Formula[i] <= '9'))
				PostfixForm[j++] = Formula[i++];
			PostfixForm[j++] = ' ';
			i--;
			continue;
		}
		else
			if ((Priority(Formula[i]) == 0) || (Priority(Formula[i]) > Priority(stack.TopElem())) || (stack.IsEmpty()))
				stack.Put(Formula[i]);
			else
			{
				while (Priority(stack.TopElem()) < Priority(Formula[i]))
					PostfixForm[j++] = stack.Get();
				stack.Put(Formula[i]);
			}
	}
	while (!stack.IsEmpty())
		PostfixForm[j++] = stack.Get();
	PostfixForm[j++] = ' ';
	cout << PostfixForm;
	return 1;
}

double TFormula::FormulaCalculator()
{
	FormulaConverter();
	int i = 0;
	double DoubleStack[MaxLen];
	int top = -1;
	while (PostfixForm[i])
	{
		if (PostfixForm[i] == ' ')
		{
			i++;
			continue;
		}
		if ((PostfixForm[i] >= '0') && (PostfixForm[i] <= '9'))
		{
			DoubleStack[++top] = atof(PostfixForm + i);
			while (PostfixForm[i] != ' ')
				i++;
			i++;
			continue;
		}
		double t1 = DoubleStack[top--];
		double t2 = DoubleStack[top--];
		if (top < -1)
			throw -1;
		switch (PostfixForm[i])
		{
		case '+':
			DoubleStack[++top] = t2 + t1;
			break;
		case '-':
			DoubleStack[++top] = t2 - t1;
			break;
		case '*':
			DoubleStack[++top] = t2 * t1;
			break;
		case '/':
			DoubleStack[++top] = t2 / t1;
			break;
		default:
			break;
		}
		i++;
	}
	cout <<" = "<<DoubleStack[top];
	return DoubleStack[top];;
	
}