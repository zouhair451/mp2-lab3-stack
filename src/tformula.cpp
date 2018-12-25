#include "tformula.h"
#include "tstack.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//CONSTRUCTOR
TFormula::TFormula(char *tmp)
{
	Size = strlen(tmp);
	for (int i = 0; i<Size; ++i)
	{
		Formula[i] = tmp[i];
	}
}
//CHECKER
int TFormula::FormulaChecker(int Brackets[], int size)
{
	Stack tmp(Size);
	int ch = 0, cnt = 0,err=0;
	for (int i = 0; i<Size; ++i)
	{
		if (Formula[i] != '('&&Formula[i] != ')') continue;
		ch++;
		if (ch > size) err++;
		if (Formula[i] == '(') tmp.Put(ch);
		else if (Formula[i] == ')')
		{
			if (tmp.IsEmpty()==0)
			{
				int t = tmp.Get();
				Brackets[cnt++] = (t);
				Brackets[cnt++] = (ch);
			}
			else
			{
				Brackets[cnt++] = 0;
				Brackets[cnt++] = ch;
				err++;
			}
		}
	}
	if (!tmp.IsEmpty())
	{
		while (tmp.IsEmpty() == 0)
		{
			int t = tmp.Get();
			Brackets[cnt++] = t;
			Brackets[cnt++] = 0;
			err++;
		}
	}
	cout << "         BRACKETS		" << endl;
	cout << "Open        |     Close " << endl;        
	for (int i = 0; i < cnt-1; ++i)
	{
		cout << Brackets[i]<<"           |           "<<Brackets[i+1]<< endl;
		i++;
	}
	return err;
}
//CONVERTER
int TFormula::FormulaConverter()
{
	int c[255];
	if (FormulaChecker(c,255) >=1) return 1;//Некорректная скобочная последовательность
	int p[50];
	Stack st(Size);
	p[40] = 0;
	p[41] = 1;
	p[43] = 2;
	p[45] = 2;
	p[47] = 3;
	p[42] = 3;
	int ch = 0;
	int k = 0;
	for (int i = 0; i<Size; ++i)
	{
		if ((Formula[i] >= '0'&&Formula[i] <= '9') || (Formula[i] == '.'))
		{
			while ((Formula[i] >= '0'&&Formula[i] <= '9') || (Formula[i] == '.'))
			{
				PostfixForm[ch++] = Formula[i];
				i++;
			}
			i--;
			PostfixForm[ch++] = ' ';
			continue;
		}
		else if (Formula[i]!=' ')
		{
			if (Formula[i] == '(' || st.IsEmpty() || (p[st.TopElem()]<p[Formula[i]]&&Formula[i]!=')'))
				st.Put(Formula[i]);
			else
			{
				if (Formula[i] != ')')
				{
					while (!st.IsEmpty() && p[st.TopElem()] >= p[Formula[i]])
					{
						PostfixForm[ch++] = st.Get();
					}
					st.Put(Formula[i]);
				}
				else
				{
					while (st.TopElem() != 40)
					{
						PostfixForm[ch++] = st.Get();
					}
					st.Get();
				}
			}
		}
	}

	while (!st.IsEmpty())
		PostfixForm[ch++] = st.Get();
	for (int i = 0; i<ch; ++i)
		cout << PostfixForm[i];
	cout << endl;
	PostfixForm[ch] = '\0';
	return 0;//Корректно выполнено
}

double TFormula::FormulaCalculator()
{
	double ans = 0;
	int c[255];
	if (FormulaConverter())
	{
		cout << "Your formula is wrong";
		throw - 1;
	}
	double * st = new double[strlen(PostfixForm)];
	int top = -1;
	//cout<<srtlen()
	int flag = 0;
	int pp =  strlen(PostfixForm);
	for (int i = 0; i<pp; ++i)
	{
		//cout << st[top] << endl;
		int j = i;
		if (PostfixForm[i] >= '0'&&PostfixForm[i] <= '9')
		{
			flag = 1;
			char tmp[255] = { ' ' };
			int ch = 0;
			while (PostfixForm[i] != ' ')
			{
				tmp[ch++] = PostfixForm[i];
				i++;
			}
			// cout<<tmp<<endl;
			double a = atof(tmp);
			st[++top] = a;
		}
		else
		{
			double a, b;
			a = st[top--];
			b = st[top--];
			switch (PostfixForm[j])
			{
			case '+':ans = a + b;
				break;
			case '-': ans = b - a;
				break;
			case '*': ans = a * b;
				break;
			case '/': ans = b / a;
				break;
			}
			//cout << ans << endl;
			st[++top] = ans;
			//cout << top <<" "<<st[top]<< endl;
		}
	}
	//cout << top << endl;
	if (flag==1) return ans = st[0];
	return 0.0;
}
