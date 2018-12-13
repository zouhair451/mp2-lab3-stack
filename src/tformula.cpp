#include <stdio.h>
#include <iostream>
#include <string.h>
#include "TStack.h"
#include "TFormula.h"


TFormula :: TFormula (char *form)                            // конструктор
{
	int size = strlen(form)+1;
	if (size>=MaxLen) throw -1;
	for (int i=0; i<size; i++)
		Formula[i] = form[i];
}

int TFormula :: FormulaChecker(int Brackets[],int size)     // проверка корректности скобок
{

	int s = 0;
	while (Formula[s] != '=') s++;

	TStack st(s);

	for (int i=0; i<s; i++)
	{
		if (Formula[i]=='(') 
			st.Put(i);
		if (Formula[i]==')') 
		{
			if (st.IsEmpty()) return 0;
			st.Get();
		}
	}
	if (st.IsEmpty()) 
		return 1;
	else 
		return 0;
}

int TFormula :: FormulaConverter()                          // преобразование в постфиксную форму
{
	int ch[MaxLen];
    if (FormulaChecker(ch, MaxLen)==0)
        throw -1;

	int s = 0;
	while (Formula[s] != '=') s++;
	TStack st(s);

	int Index = 0; //Длина постфиксной формы
	int Priority = -1;		//Приоритет операции
	int PriorityStackOp = -1; //Приоритет последней операции в стеке

	for (int i=0; i<s; i++)
	{
		if ((Formula[i] >= '0')&&(Formula[i] <= '9')||(Formula[i] == '.'))
		{
			PostfixForm[Index] = Formula [i];
			Index++;
			//std::cout<<Formula [i];
		}
		if ((Formula[i] == '+')||(Formula[i] == '-')||(Formula[i] == '*')||(Formula[i] == '/')
			||(Formula[i] == '(')||(Formula[i] == ')'))
		{
			switch (Formula[i])
			{
				case '+': 
				{
					PostfixForm[Index] = ' ';
					//std::cout<<PostfixForm[Index];
					Index++;
					Priority = 2;
					while (Priority<=PriorityStackOp)
						{
							PostfixForm[Index] = st.Get();
							//std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							//std::cout<<PostfixForm[Index];
							Index++;
							if (!st.IsEmpty()) {
								if ((st.TopElem()=='*')||(st.TopElem()=='/')) PriorityStackOp = 3;
								if ((st.TopElem()=='+')||(st.TopElem()=='-')) PriorityStackOp = 2;
								if (st.TopElem()=='(') PriorityStackOp = 0;
							}
							if (st.IsEmpty()) break;
						}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))					//если больше
					{
						st.Put('+');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '-':
				{
					PostfixForm[Index] = ' ';
					//std::cout<<PostfixForm[Index];
					Index++;
					Priority = 2;
					while (Priority<=PriorityStackOp)
						{
							PostfixForm[Index] = st.Get();
							//std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							//std::cout<<PostfixForm[Index];
							Index++;
							if (!st.IsEmpty()) {
								if ((st.TopElem()=='*')||(st.TopElem()=='/')) PriorityStackOp = 3;
								if ((st.TopElem()=='+')||(st.TopElem()=='-')) PriorityStackOp = 2;
								if (st.TopElem()=='(') PriorityStackOp = 0;
							}
							if (st.IsEmpty()) break;
						}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('-');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '*': 
				{
					PostfixForm[Index] = ' ';
					//std::cout<<PostfixForm[Index];
					Index++;
					Priority = 3;
						while (Priority<=PriorityStackOp)
						{
							PostfixForm[Index] = st.Get();
							//std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							//std::cout<<PostfixForm[Index];
							Index++;
							if (!st.IsEmpty()) {
								if ((st.TopElem()=='*')||(st.TopElem()=='/')) PriorityStackOp = 3;
								if ((st.TopElem()=='+')||(st.TopElem()=='-')) PriorityStackOp = 2;
								if (st.TopElem()=='(') PriorityStackOp = 0;
							}
							if (st.IsEmpty()) break;
						}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('*');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '/' :
				{
					PostfixForm[Index] = ' ';
					//std::cout<<PostfixForm[Index];
					Index++;
					Priority = 3;
					while (Priority<=PriorityStackOp)
						{
							PostfixForm[Index] = st.Get();
							//std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							//std::cout<<PostfixForm[Index];
							Index++;
							if (!st.IsEmpty()) {
								if ((st.TopElem()=='*')||(st.TopElem()=='/')) PriorityStackOp = 3;
								if ((st.TopElem()=='+')||(st.TopElem()=='-')) PriorityStackOp = 2;
								if (st.TopElem()=='(') PriorityStackOp = 0;
							}
							if (st.IsEmpty()) break;
						}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('/');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '(' :
				{
					Priority = 0;
					PriorityStackOp = Priority;
					st.Put('(');
					break;
				}
				case ')' :
				{
					PostfixForm[Index] = ' ';
					//std::cout<<PostfixForm[Index];
					Index++;
					Priority = 1;
					PriorityStackOp = Priority;
					while (st.TopElem()!='(')
						{
							PostfixForm[Index] = st.Get();
							//std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							//std::cout<<PostfixForm[Index];
							Index++;
						}
					st.Get();
					if (!st.IsEmpty()) {
								if ((st.TopElem()=='*')||(st.TopElem()=='/')) PriorityStackOp = 3;
								if ((st.TopElem()=='+')||(st.TopElem()=='-')) PriorityStackOp = 2;
								if (st.TopElem()=='(') PriorityStackOp = 0;
					}
					break;
				}
			}
		}
		if (!((Formula[i] >= '0')&&(Formula[i] <= '9')||(Formula[i] == '.'))&&(!((Formula[i] == '+')||(Formula[i] == '-')||(Formula[i] == '*')||(Formula[i] == '/')
			||(Formula[i] == '(')||(Formula[i] == ')'))))
			throw -1;
	}
	while(!st.IsEmpty()) {
		PostfixForm[Index] = ' ';
		//std::cout<<PostfixForm[Index];
		Index++;
		PostfixForm[Index] = st.Get();
		//std::cout<<PostfixForm[Index];
		Index++;
	}
	PostfixForm[Index++] = ' ';
	PostfixForm[Index] = '\0';
	//std::cout<<std::endl;
	return 1;
}

double TFormula :: FormulaCalculator()                      // вычисление формулы
{
	double str [MaxLen] = {0};
	char y [MaxLen];

	double result = 0;
	FormulaConverter();

	int ind = 0; //индекс в str
	int i = 0; //индекс в PostfixForm

	int s = 0;
	while (Formula[s] != '=') s++;

	while (PostfixForm[i]!='\0')
	{
		if ((PostfixForm[i] >= '0')&&(PostfixForm[i] <= '9')) 
		{
			int j = 0;
			while (PostfixForm[i] != ' ') {
				y[j] = PostfixForm[i];
				i++; j++;
			}
			y[j] = 0;
			str [ind] = atof(y);
			ind++;
		}
		switch (PostfixForm[i])
		{
			case '+' :
				{
					double top_el = str[--ind]; //запоминаем элемент на вершине
					str[ind] = 0; //обнуляем
					result = str [--ind] + top_el; //складываем с предыдущим
					str[ind] = result; //кладем результат
					ind++; //перемещаем индекс на cлед позицию
					break;
				}
			case '-' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] - top_el;
					str[ind] = result;
					ind++;
					break;
				}
			case '*' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] *  top_el;
					str[ind] = result;
					ind++;
					break;
				}
			case '/' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] / top_el;
					str[ind] = result;
					ind++;
					break;
				}
		}
		i++;
	}

	return str [--ind];
}