#include "tformula.h"
#include <cstdlib>

int Get_Pr(char c) //приоритет операции
{
	if (c == ' ') return -1;
	if (c == '(') return 0;
	if (c == ')') return 1;
	if (c == '+' || c == '-') return 2;
	if (c == '*' || c == '/') return 3;
}

bool is_op(char c) //пседопроверка на операнд
{
	int t = Get_Pr(c) / 4;
	if (t == 0 && c != '.') return false;
	return true;
}


TFormula::TFormula(const char* form)
{
	int i;
	for (i = 0; form[i] != '\0'; i++)
		Formula[i] = form[i];
	Formula[i] = '\0';
}

char* TFormula::GetFormula()
{
	return Formula;
}

int TFormula::FormulaChecker()
{
	TStack st(DefMemSize);
	int BracketsCounter = 0, MistakeCounter = 0;
	for (int i = 0; Formula[i] != '\0'; i++)
	{
		if (Formula[i] == '(') st.Put('(');
		if (Formula[i] == ')')
			if (st.Get() != '(')
				return -1;
	}
	if (st.IsEmpty()) return 0;
	else return -1;
}

int TFormula::FormulaConverter()
{
	if (FormulaChecker() == 0)
	{
		TStack st(DefMemSize);
		int c = 0;

		for (int i = 0; Formula[i] != '\0'; i++)
		{
			if (is_op(Formula[i]))
				PostfixForm[c++] = Formula[i];
			else
			{
				if (Formula[i] == '(')
					st.Put(Formula[i]);
				else
				{
					if (Formula[i] == ')')
					{
						for (int j = st.GetHi(); st[j] != '('; j--)
							PostfixForm[c++] = st.Get();
						st.Get();
					}
					else
					{
						if ((Get_Pr(Formula[i]) == 2) || (Get_Pr(Formula[i]) == 3))  PostfixForm[c++] = ' ';
						if (st.IsEmpty()) st.Put(Formula[i]);
						else
						{
							for (int j = st.GetHi(); ((j >= 0) && (Get_Pr(Formula[i]) <= Get_Pr(st[j]))); j--)
								PostfixForm[c++] = st.Get();
							st.Put(Formula[i]);
						}

					}
				}

			}
		}

		for (int j = st.GetHi(); j >= 0; j--)
		{
			if (st[j] == '(' || st[j] == ')') st.Get();
			else PostfixForm[c++] = st.Get();
		}

		PostfixForm[c] = '\0';
		if (PostfixForm[0] == '\0') throw - 1;
		return 0;
	}
	else throw - 1;
}

char* TFormula::GetPostfixForm()
{
	return PostfixForm;
}

int TFormula::GetSizePostfixForm()
{
	int i = 0;
	for (i; PostfixForm[i] != '\0'; i++);
	return i;
}

double TFormula::FormulaCalculator()
{
	FormulaConverter();
		TStack_d st(DefMemSize);
		char* tmp = new char[GetSizePostfixForm()];
		int j = 0;


		for (int i = 0; PostfixForm[i] != '\0'; i++)
		{
			if (is_op(PostfixForm[i]) && PostfixForm[i] != ' ')
				tmp[j++] = PostfixForm[i];

			else
			{
				if (j != 0)
				{
					tmp[j] = '\0';
					st.Put(strtod(tmp, NULL));
					j = 0;
				}

				switch (PostfixForm[i])
				{
				case '+':
					st.Put(st.Get() + st.Get());
					break;

				case '-':
					st.Put(-(st.Get()) + st.Get());
					break;

				case '*':
					st.Put(st.Get() * st.Get());
					break;

				case '/':
					if (st[st.GetHi()] == 0)
						throw - 1;
					st.Put((1 / st.Get()) * st.Get());
					break;

				default:
					if (st.GetRetCode() != DataOK) throw - 2;
					break;
				}
				if (st.GetRetCode() != DataOK) throw - 2;
			}
	    }
		if (st.IsEmpty()) return strtod(PostfixForm,NULL);
		else return st.Get();
}
