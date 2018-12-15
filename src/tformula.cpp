#include "tformula.h"
#include "tstack.h"
#include <iostream>
#include <string>

TFormula::TFormula(char *form)
{
	if (form != "")
	{
		strcpy_s(Formula, form);
		strcpy_s(PostfixForm, "");

		int i = 0;
		int bracketCount = 0;
		int closeBracket = 0;
		int openBracket = 0;
		while (Formula[i] != '\0')
		{
			if (Formula[i] == '(')
			{
				openBracket++;
				bracketCount++;
			}
			else if (Formula[i] == ')')
			{
				closeBracket++;
				bracketCount++;
			}

			i++;
		}

		for (int i = 0; i < closeBracket - openBracket; i++)
			bracketCount++;

		for (int i = 0; i < openBracket - closeBracket; i++)
			bracketCount++;

		int brackets[255];
		if (FormulaChecker(brackets, 255) != 0)
		{
			for (int i = 0; i < bracketCount; i += 2)
				std::cout << brackets[i] + 1 << " | " << brackets[i + 1] + 1 << std::endl;
		}
		else
		{
			this->FormulaConverter();
		}
	}
}
/*------------------------------------------------------------------------------*/
int TFormula::FormulaChecker(int brackets[], int size)
{
	TStack mstack(size);

	int bracketsCount = 0;
	int i = 0;
	int errors = 0;
	int bracketIndex = 0;
	while (Formula[i] != '\0')
	{
		if (Formula[i] == '(')
			mstack.Put(bracketIndex++);

		else if (Formula[i] == ')')
		{
			if (mstack.IsEmpty())
			{
				brackets[bracketsCount++] = -1;
				brackets[bracketsCount++] = bracketIndex++;
				errors++;
			}

			else
			{
				brackets[bracketsCount++] = mstack.Get();
				brackets[bracketsCount++] = bracketIndex++;
			}
		}

		i++;
	}

	while (!mstack.IsEmpty())
	{
		brackets[bracketsCount++] = mstack.Get();
		brackets[bracketsCount++] = -1;
		errors++;
	}

	return errors;
}
/*------------------------------------------------------------------------------*/
bool TFormula::IsOperator(char str)
{
	return (str == '*' || str == '/'
		|| str == '+' || str == '-');
}
/*------------------------------------------------------------------------------*/
int TFormula::Priority(char str)
{
	if (str == '*' || str == '/') return 2;
	if (str == '+' || str == '-') return 1;
	return 0;
}
/*------------------------------------------------------------------------------*/
int TFormula::FormulaConverter()
{
	TStack mstack(255);

	int i = 0;
	int postFix = 0;
	while (Formula[i] != '\0')
	{
		if (isdigit(Formula[i]))
		{
			while (isdigit(Formula[i]))
			{
				PostfixForm[postFix++] = Formula[i];
				i++;
			}
			PostfixForm[postFix++] = ' ';
			i--;
		}

		else if (IsOperator(Formula[i]))
		{
			if (Priority(Formula[i]) > Priority(mstack.TopElem()) || Priority(Formula[i]) == 0 || mstack.IsEmpty())
				mstack.Put(Formula[i]);

			else
			{
				while (!mstack.IsEmpty() && Priority(mstack.TopElem()) >= Priority(Formula[i]) && mstack.TopElem() != '(')
					PostfixForm[postFix++] = mstack.Get();

				mstack.Put(Formula[i]);
			}
		}

		if (Formula[i] == '(')
			mstack.Put(Formula[i]);

		if (Formula[i] == ')')
		{
			while (!mstack.IsEmpty())
			{
				if (mstack.TopElem() != '(')
					PostfixForm[postFix++] = mstack.Get();

				else
				{
					mstack.Get();
					break;
				}
			}
		}

		i++;
	}

	while (!mstack.IsEmpty())
		PostfixForm[postFix++] = mstack.Get();
	PostfixForm[postFix] = '\0';

	return 0;
}
/*------------------------------------------------------------------------------*/
double TFormula::FormulaCalculator()
{
	TStack mstack(255);

	int i = 0;
	while (PostfixForm[i] != '\0')
	{
		if (isdigit(PostfixForm[i]))
			mstack.Put(PostfixForm[i] - '0');

		else if (IsOperator(PostfixForm[i]))
		{
			int rigthOperator = mstack.Get();
			int leftOperator = mstack.Get();

			switch (PostfixForm[i])
			{
			case'*':
				mstack.Put(leftOperator * rigthOperator);
				break;
			case '/':
				mstack.Put(leftOperator / rigthOperator);
				break;
			case '+':
				mstack.Put(leftOperator + rigthOperator);
				break;
			case '-':
				mstack.Put(leftOperator - rigthOperator);
				break;
			}
		}

		i++;
	}

	return mstack.Get();
}
/*------------------------------------------------------------------------------*/