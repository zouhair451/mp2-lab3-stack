#include <stdio.h>
#include <iostream>
#include "tstack.h"
#include "tformula.h"



TFormula::TFormula(char* form)
{
	int i = 0;
	while ((form[i] != '\0') && (i < MaxLen - 1))
	{
		Formula[i] = form[i];
		i++;
	}
	Formula[i] = '\0';
}


int TFormula::FormulaChecker(int Brackets[], int size)
{
	TStack st(MaxLen);
	int r = 0;
	int er = 0;
	int i = 0;

	while(Formula[i] != '\0')
	{
		if (Formula[i] == '(')
		{
			st.Put(r++);
		}
		else if (Formula[i] == ')')
		{
			if (st.IsEmpty())
			{
				er++;
				if (r < size)
				{
					Brackets[r++] = -1;
				}
			}
			else
			{
				if (r < size)
				{
					Brackets[r] = st.TopElem();
					Brackets[st.Get()] = r;
					r++;
				}
			}
		}
		i++;

	}

	if (!st.IsEmpty())
	{
		while (!st.IsEmpty())
			Brackets[st.Get()] = -1;
		er++;
	}

	return er;
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
	if (FormulaChecker(br, MaxLen))
		throw "Brackets exception";

	TStack st(MaxLen);
	int i = 0;  // Formula

	int j = 0; // PostfixForm

	while(Formula[i] != '\0')
	{
		if (Formula[i] == '(')
		{
			st.Put(Formula[i]);
		}

		if (Formula[i] == ')')
		{
			while (st.TopElem() != '(')
			{
				PostfixForm[j++] = st.Get();
			}
			st.Get();
		}

		if (IsOperand(Formula[i]) || Formula[i] == '.')
		{
			PostfixForm[j++] = Formula[i];

			if ((IsOperation(Formula[i + 1])) || (Formula[i + 1] == ')'))
			{
				PostfixForm[j++] = ' ';
			}
		}

		if (IsOperation(Formula[i]))
		{
			if (GetPriority(Formula[i]) > st.TopElem() || st.IsEmpty())
			{
				st.Put(Formula[i]);
			}
			else
			{
				while (GetPriority(Formula[i]) <= GetPriority(st.TopElem()))
				{
					PostfixForm[j++] = st.Get();
				}
				st.Put(Formula[i]);
			}
		}
		
		i++;
	}

	while (!st.IsEmpty())
		PostfixForm[j++] = st.Get();

	PostfixForm[j] = '\0';
}

double TFormula::FormulaCalculator()
{
	FormulaConverter();

	double stack[MaxLen] = { 0 };
	int top = -1;
	int i = 0;
	

	while (PostfixForm[i] != '\0')
	{
		if (IsOperand(PostfixForm[i]))
		{
			stack[++top] = atof(PostfixForm + i);

			while (!IsOperation(PostfixForm[i + 1]) && PostfixForm[i + 1] != ' ')
			{
				i++;
			}
		}

		if (IsOperation(PostfixForm[i]))
		{
			if (PostfixForm[i] == '+')
			{
				double top_elem = stack[top--];
				double result = top_elem + stack[top--];
				stack[++top] = result;
			}

			if (PostfixForm[i] == '-')
			{
				double top_elem = stack[top--];
				double result = stack[top--] - top_elem;
				stack[++top] = result;
			}

			if (PostfixForm[i] == '*')
			{
				double top_elem = stack[top--];
				double result = top_elem * stack[top--];
				stack[++top] = result;
			}

			if (PostfixForm[i] == '/')
			{
				double top_elem = stack[top--];
				double result = stack[top--] / top_elem;
				stack[++top] = result;
			}
		}
		i++;
	}
	return stack[top];
}


