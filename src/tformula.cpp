#include "tformula.h"
#include "tstack.h"
#include <iostream>
#include <string>

TFormula::TFormula(char* form)
{
	int i;
	for (i = 0; (form[i] != '\0') && (i < MaxLen - 1); ++i)
	{
		Formula[i] = form[i];
	}
	Formula[i] = '\0';

	for (i = 0; i < MaxLen; ++i)
	{
		PostfixForm[i] = '\0';
	}

}

int TFormula::FormulaChecker(int Brackets[], int size) //DONE
{
	TStack st(MaxLen);
	int br_number = 0;
	int err = 0;

	int i = 0;
	while ((Formula[i] != '\0'))
	{
		if (Formula[i] == '(')
		{
			st.Put(br_number++);
		}
		else if (Formula[i] == ')')
		{
			if (st.IsEmpty())
			{
				err++;
				Brackets[br_number++] = -1;
			}
			else
			{
				Brackets[br_number] = st.TopElem();
				Brackets[st.Get()] = br_number++;
				
			}
		}
		i++;
	}

	while (!st.IsEmpty())
	{
		Brackets[st.Get()] = -1;
		err++;
	}

	return err;
}

bool IsOperation(char c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsDigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}

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
	int brackets[MaxLen];
	if (FormulaChecker(brackets, MaxLen))
	{
		throw -1;
	}


	TStack st(MaxLen);

	int i = 0;
	int j = 0;

	while ((Formula[i] != '\0') && (i < MaxLen - 1))
	{
		//опеpанды пеpеписываются в выходную стpоку
		if (IsDigit(Formula[i]) || Formula[i] == '.')
		{
			PostfixForm[j++] = Formula[i];

			if ((IsOperation(Formula[i + 1])) || (Formula[i + 1] == ')'))
			{
				PostfixForm[j++] = ' ';
			}
		}

		//если очеpедной символ из исходной стpоки есть откpывающая скобка, то он пpоталкивается в стек
		if (Formula[i] == '(')
		{
			st.Put(Formula[i]);
		}

		//закpывающая кpуглая скобка выталкивает все опеpации из стека до ближайшей откpывающей скобки
		//сами скобки в выходную стpоку не пеpеписываются, а уничтожают дpуг дpуга
		if (Formula[i] == ')')
		{
			while (st.TopElem() != '(')
			{
				PostfixForm[j++] = st.Get();
			}
			st.Get();
		}

		//опеpация выталкивает из стека все опеpации с большим или pавным пpиоpитетом в выходную стpоку
		//если стек пуст, то опеpация из входной стpоки пеpеписывается в стек
		if (IsOperation(Formula[i]))
		{
			if (GetPriority(Formula[i]) > GetPriority(st.TopElem()) || st.IsEmpty())
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

		//переход к следующему символу
		i++;

	}

	while (!st.IsEmpty())
	{
		PostfixForm[j++] = st.Get();
	}
}

double TFormula::FormulaCalculator()
{
	if (PostfixForm[0] == '\0')
	{
		this->FormulaConverter();
	}
		

	double stack[MaxLen] = { 0 };

	int top = -1;
	int i = 0;

	while (PostfixForm[i] != '\0')
	{
		if (IsDigit(PostfixForm[i]))
		{
			stack[++top] = atof(PostfixForm + i);

			while (!IsOperation(PostfixForm[i + 1]) && PostfixForm[i + 1] != ' ')
			{
				i++;
			}
		}

		if (IsOperation(PostfixForm[i]))
		{
			switch (PostfixForm[i])
			{

				case '+':
				{
					double top_elem = stack[top--];
					double result = top_elem + stack[top--];
					stack[++top] = result;
					break;
				}

				case '-':
				{
					double top_elem = stack[top--];
					double result = stack[top--] - top_elem;
					stack[++top] = result;
					break;
				}

				case '*':
				{
					double top_elem = stack[top--];
					double result = top_elem * stack[top--];
					stack[++top] = result;
					break;
				}

				case '/':
				{
					double top_elem = stack[top--];
					double result = stack[top--] / top_elem;
					stack[++top] = result;
					break;
				}
			}
		}

		i++;
	}

	return stack[top];
}
