#include "tformula.h"
#include "tstack.h"
#include <cstdlib>

TFormula::TFormula(char * form)
{
	int i = 0;
	while ((form[i] != '\0') && (i < MaxLen - 1)) {
		Formula[i] = form[i];
		i++;
	}
	Formula[i] = '\0';

	for (int i = 0; i < MaxLen; ++i) 
		PostfixForm[i] = '\0';
//	FormulaConverter();   //
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	TStack s (MaxLen);
	int k = 0, index = 0, err = 0;
	//таблица
	for (int i = 0; i <   MaxLen; i++) {
		if (Formula[i] == '(') s.Put(++k);
		else if (Formula[i] == ')') {
			if (!s.IsEmpty())
				Brackets[index++] = s.Get();
			else {
				Brackets[index++] = 0;
				err++;
			}
		
			Brackets[index++] = i;
		}
	}
	while (!s.IsEmpty()) {
		Brackets[index++] = s.Get();
		Brackets[index++] = 0;
		err++;
	}

	return err;
}

int GetPriority(char c) {
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
bool IsOperation(char c) {
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
		return true;
	return false;
}  
//  +- */
bool IsOperand(char c) {
	if (((c >= '0') && (c <= '9')) || (c == '.')) return true;
	else return false;
}

int TFormula::FormulaConverter()
{
	int br[MaxLen];
	if (FormulaChecker(br, MaxLen)) throw -1;

	TStack st(MaxLen);
	int i = 0; // indx = 0; //indx_post_form
	int j = 0;

	{//while ((Formula[i] != '\0') && (i < MaxLen - 1)) {
	//	/*if (!(Formula[i] >= '0' && Formula[i] <= '9') && !IsOperation(Formula[i])
	//		&& (Formula[i] != ' ') && (Formula[i] != '.') && (Formula[i] != '(') && (Formula[i] != ')'))
	//		throw "Err_symbol";*/

	//	if (IsOperation(Formula[i]))  // ()+-*/
	//	{
	//		//Put
	//		if ((Formula[i] == '(') || ( GetPriority(Formula[i]) > GetPriority(st.TopElem()) ) || (st.IsEmpty()) )
	//		{
	//			st.Put(Formula[i]);
	//		}
	//		else //Get
	//		{
	//			if (Formula[i] == ')')
	//			{
	//				while (st.TopElem() != '(')
	//					PostfixForm[i] = st.Get();
	//				st.Get();
	//			}

	//			else
	//			{
	//				while (GetPriority(Formula[i]) <= (GetPriority(st.TopElem()))) //priority
	//				{
	//					PostfixForm[indx++] = st.Get();
	//				}
	//				
	//			}

	//		}
	//	}
	//	else if (IsOperand(Formula[i]))  //цифрa
	//	{
	//		while (IsOperand(Formula[i]))
	//		{
	//			PostfixForm[indx++] = Formula[i++];
	//		}
	//		PostfixForm[indx++] = ' ';
	//		
	//	}
	//}
	}
	
	while ((Formula[i] != '\0') && (i < MaxLen - 1))
	{
		if (Formula[i] == '(')
		{
			st.Put(Formula[i]);
		}

		  if (Formula[i] == ')')
		{
			while (st.TopElem() != '(')
			{
				PostfixForm[j] = st.Get();
				j++;
			}
			st.Get();
		}

		  if (IsOperand(Formula[i]))
		{
			PostfixForm[j] = Formula[i];
			j++;

			if ((IsOperation(Formula[i + 1])) || (Formula[i + 1] == ')'))
			{
				PostfixForm[j] = ' ';
				j++;
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
					PostfixForm[j] = st.Get();
					j++;
				}
				st.Put(Formula[i]);
			}
		}
		i++;
	}

	while (!st.IsEmpty())
	{
		PostfixForm[j] = st.Get();
		j++;
	}
	return 0; 
}

double TFormula::FormulaCalculator()
{
	if (PostfixForm[0] == '\0')
		this->FormulaConverter();

	double stack[MaxLen] = { 0 };
	TStack st(MaxLen);
	double res = 0;
	int i = 0;
	int top = -1;
//	char tmp;
	while ((PostfixForm[i]) && (i < MaxLen)) {

		if (IsOperand(PostfixForm[i])) {
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
