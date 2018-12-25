#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "tformula.h"
#include "tstack.h"

TFormula::TFormula(char* form)
{
	formulaLength = std::strlen(form);
	postfixFormulaLength = 0;

	if (formulaLength == 0)
		throw "error";

	std::strcpy(Formula, form);
}

int TFormula::FormulaChecker()
{
	TStack stack(formulaLength);

	int* Brackets = new int[formulaLength * 2]{};
	int bracketsCount = 0;
	int errors = 0;
	int bracketIndex = 0;
	for (int i = 0; i < formulaLength; i++)
	{
		if (Formula[i] == '(')
			stack.Put(++bracketsCount);
		else
		{
			if (Formula[i] == ')')
			{
				Brackets[++bracketIndex] = ++bracketsCount;

				if (stack.IsEmpty())
				{
					Brackets[--bracketIndex] = 0;
					bracketIndex += 2;
					errors++;
				}
				else
				{
					Brackets[--bracketIndex] = stack.Get();
					bracketIndex += 2;
				}
			}
			else
				continue;
		}
	}
	if (!stack.IsEmpty())
	{
		while (!stack.IsEmpty())
		{
			Brackets[bracketIndex++] = stack.Get();
			Brackets[bracketIndex++] = 0;
			errors++;
		}
	}
	return errors;

}

int TFormula::FormulaConverter()
{
	TStack stack(formulaLength);

	for (int i = 0; i < formulaLength; i++)
	{
		if (isdigit(Formula[i]))
		{
			PostfixForm[postfixFormulaLength++] = Formula[i];
		}
		else  if (Formula[i] != ')')
		{
			if ((!stack.IsEmpty() && Priority(Formula[i]) == 0 || Priority(Formula[i]) > Priority(stack.TopElem()) || stack.IsEmpty()))
				stack.Put(Formula[i]);

			else
			{
				while (!stack.IsEmpty() && Priority(stack.TopElem()) >= Priority(Formula[i]))
					PostfixForm[postfixFormulaLength++] = stack.Get();

				stack.Put(Formula[i]);
			}
		}
		else
		{
			while (!stack.IsEmpty() && Priority(stack.TopElem()) != Priority('('))
				PostfixForm[postfixFormulaLength++] = stack.Get();

			stack.Get();
		}
	}

	while (!stack.IsEmpty())
		PostfixForm[postfixFormulaLength++] = stack.Get();

	return 0;
}

double TFormula::FormulaCalculator()
{
	TStack stack(formulaLength);
	int leftOp = 0;
	int rightOp = 0;

	if (FormulaChecker() != 0)
		throw "error";

	if (postfixFormulaLength == 0)
		FormulaConverter();

	for (int i = 0; i < postfixFormulaLength; i++)
	{
		if (isdigit(PostfixForm[i]))
		{
			stack.Put(PostfixForm[i] - '0' );
		}
		else
		{
			leftOp = stack.Get();
			rightOp = stack.Get();

			switch (PostfixForm[i])
			{
			case '+':
				stack.Put(rightOp + leftOp);
				break;
			case '-':
				stack.Put(rightOp - leftOp);
				break;
			case '*':
				stack.Put(rightOp * leftOp);
				break;
			case '/':
				stack.Put(rightOp / leftOp);
				break;
			}
		}
	}
	return stack.Get();
}

int TFormula::Priority(char sign)
{
	switch (sign)
	{
	case '(':
		return 0;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	default:
		return -1;
	}
}