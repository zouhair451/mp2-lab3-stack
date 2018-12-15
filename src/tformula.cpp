#include "tformula.h"
#include "tstack.h"
#include <cstring>
#include <iostream>
using namespace std;

TFormula::TFormula(char *form)
{
	strcpy(Formula, form);
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	int BrNum = 0;
	int BrQuant = 0;
	int i = 0;

	TStack st(size);

	while (Formula[i])
	{
		if ((Formula[i] <= '0') && (Formula[i] >= '9') &&
			(Formula[i] != '(') && (Formula[i] != ')') &&
			(Formula[i] != '+') && (Formula[i] != '-') && (Formula[i] != '*') && (Formula[i] != '/') &&
			(Formula[i] != ' ') && (Formula[i] != '.'))
			throw(-1);
		
		if (Formula[i] == '(')
		{
			st.Put(++BrNum);
		}

		else if (Formula[i] == ')')
		{
			if (st.IsEmpty())
			{
				Brackets[BrQuant++] = 0;
				Brackets[BrQuant++] = ++BrNum;
			}
			else
			{
				Brackets[BrQuant++] = st.Get();
				Brackets[BrQuant++] = ++BrNum;
			}
		}
		i++;
	}

	while (!st.IsEmpty())
	{
		Brackets[BrQuant++] = 0;
		st.Get();
	}

}

int TFormula::FormulaConverter()
{
	TStack OpSt(255);
	TStack PrSt(255);

	int ResNum = 0;
	int i = 0;

	while (Formula[i])
	{
		if (((Formula[i] <= '0') || (Formula[i] >= '9')) &&
			(Formula[i] != '(') && (Formula[i] != ')') &&
			(Formula[i] != '+') && (Formula[i] != '-') && (Formula[i] != '*') && (Formula[i] != '/') &&
			(Formula[i] != ' ') && (Formula[i] != '.'))
			throw(-1);	

		if (((Formula[i] >= '0') && (Formula[i] <= '9')) || (Formula[i] == '.'))
		{
			while (((Formula[i] >= '0') && (Formula[i] <= '9')) || (Formula[i] == '.'))
			{
				PostfixForm[ResNum++] = Formula[i];
				i++;
			}
			PostfixForm[ResNum++] = ' ';
		}

		else
		{
			switch (Formula[i])
			{
			case '(':
			{
				OpSt.Put('(');
				PrSt.Put(0);
				break;
			}
			case ')':
			{
				while (OpSt.TopElem() != '(')
				{
					PostfixForm[ResNum++] = OpSt.Get();
					PostfixForm[ResNum++] = ' ';
					PrSt.Get();
				}
				PrSt.Get();
				OpSt.Get();
				break;
			}
			case '+':
			{
				while ((PrSt.TopElem() >= 2) && !(OpSt.IsEmpty()))
				{
					PostfixForm[ResNum++] = OpSt.Get();
					PostfixForm[ResNum++] = ' ';
					PrSt.Get();
				}
				OpSt.Put('+');
				PrSt.Put(2);
				break;
			}
			case '-':
			{
				while ((PrSt.TopElem() >= 2) && !(OpSt.IsEmpty()))
				{
					PostfixForm[ResNum++] = OpSt.Get();
					PostfixForm[ResNum++] = ' ';
					PrSt.Get();
				}
				OpSt.Put('-');
				PrSt.Put(2);
				break;
			}
			case '*':
			{
				while ((PrSt.TopElem() >= 3) && !(OpSt.IsEmpty()))
				{
					PostfixForm[ResNum++] = OpSt.Get();
					PostfixForm[ResNum++] = ' ';
					PrSt.Get();
				}
				OpSt.Put('*');
				PrSt.Put(3);
				break;
			}
			case '/':
			{
				while ((PrSt.TopElem() >= 3) && !(OpSt.IsEmpty()))
				{
					PostfixForm[ResNum++] = OpSt.Get();
					PostfixForm[ResNum++] = ' ';
					PrSt.Get();
				}
				OpSt.Put('/');
				PrSt.Put(3);
				break;
			}
			}		
			i++;
		}		
	}

	while (!OpSt.IsEmpty())
	{
		PostfixForm[ResNum++] = OpSt.Get();
		PostfixForm[ResNum++] = ' ';
	}

	PostfixForm[ResNum++] = '\0';
	return ResNum;

}

double TFormula::FormulaCalculator()
{
	FormulaConverter();

	TStack St(255);

	int i = 0;
	int k = 0;


	while (PostfixForm[i])
	{
		if ((PostfixForm[i] >= '0') && (PostfixForm[i] <= '9'))
		{
			k = k * 10 + ((int)(PostfixForm[i]) - '0');
			if (!((PostfixForm[i + 1] >= '0') && (PostfixForm[i + 1] <= '9')))
			{				
				St.Put(k);
				k = 0;
			}
			
				
		}
		else if ((PostfixForm[i] == '+') || (PostfixForm[i] == '-') || (PostfixForm[i] == '*') || (PostfixForm[i] == '/'))
		{
			double b = St.Get();
			double a = St.Get();
			switch (PostfixForm[i])
			{
				case '+':
					St.Put(a + b);
					break;
				case '-':
					St.Put(a - b);
					break;
				case '*':
					St.Put(a * b);
					break;
				case '/':
					St.Put(a / b);
					break;
			}
		}
		i++;
	}
	return St.TopElem();
}