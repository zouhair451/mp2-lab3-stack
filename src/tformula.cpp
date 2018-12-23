#include <cstdlib>
#include "tformula.h"
#include "tstack.h"
#include <iostream>

TFormula::TFormula(char* form) {
	char* ptr = form;
	while (*ptr) ++ptr;
	int len = ptr - form;
	if (len > MaxLen)
		len = MaxLen;
	for (int i = 0; i < len; ++i)
		this->Formula[i] = form[i];
	this->Formula[len] = 0;
	for (int i = 0; i < MaxLen; ++i)
		PostfixForm[i] = 0;
}

int TFormula::FormulaChecker(int Brackets[], int size) {
	for (int i = 0; i < size; ++i)
		Brackets[i] = 0;
	char* ptr = Formula;
	while (*ptr) ++ptr;
	int len = ptr - Formula;
	TStack s(MaxLen);
	int index = 1;
	for (int i = 0; i < len; ++i) {
		if (Formula[i] == '(') {
			s.Put(index);
			Brackets[index] = -1;
			++index;
		}
		else if (Formula[i] == ')') {
			if (s.IsEmpty()) {
				Brackets[index] = -1;
			}
			else {
				Brackets[s.Get()] = Brackets[index] = index;
			}
			++index;
		}
		if (index > size)
			throw - 1;
	}
	while (!s.IsEmpty())
		Brackets[s.Get()] = -1;
	int errors = 0;
	for (int i = 0; i < size; ++i)
		if (Brackets[i] == -1)
			++errors;
	return errors;
}

int priority(char c) {
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	return -1;
}

bool isOperator(char c) {
	return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

int TFormula::FormulaConverter() {
	char* ptr = Formula;
	while (*ptr) ++ptr;
	int len = ptr - Formula;
	for (int i = 0; i < len; ++i)
		if (!(Formula[i] >= '0' && Formula[i] <= '9') && !isOperator(Formula[i])
			&& Formula[i] != ' ' && Formula[i] != '.' && Formula[i] != '(' && Formula[i] != ')')
			throw 8;
	int chk[MaxLen];
	if (FormulaChecker(chk, MaxLen))
		throw 10;
	TStack s(MaxLen);
	int index = 0;
	int last = -1;
	for (int i = 0; i < len; ++i) {
		if (Formula[i] != ' ') {
			if (Formula[i] == '(') {
				if (last == 2)
					throw - 1;
				s.Put('(');
				last = 1;
			}
			else if (Formula[i] == ')') {
				if (last == 1 || last == 3)
					throw - 1;
				while (s.TopElem() != '(')
					PostfixForm[index++] = s.Get();
				s.Get();
				last = 2;
			}
			else if (isOperator(Formula[i])) {
				if (last == 1)
					throw - 1;
				char currentOperator = Formula[i];
				while (!s.IsEmpty() && priority(s.TopElem()) >= priority(Formula[i]))
					PostfixForm[index++] = s.Get();
				s.Put(currentOperator);
				last = 3;
			}
			else {
				PostfixForm[index++] = ' ';
				while (i < len && ((Formula[i] >= '0' && Formula[i] <= '9') || Formula[i] == '.'))
					PostfixForm[index++] = Formula[i++];
				--i;
				last = 4;
			}
		}
	}
	while (!s.IsEmpty())
		PostfixForm[index++] = s.Get();
	return 1;
}

double TFormula::FormulaCalculator() {
	FormulaConverter();
	char* ptr = PostfixForm;
	while (*ptr) ++ptr;
	int len = ptr - PostfixForm;
	TStack s(MaxLen);
	double res[MaxLen];
	int index = 0;
	for (int i = 0; i < len; ) {
		if (PostfixForm[i] != ' ') {
			if ((PostfixForm[i] >= '0' && PostfixForm[i] <= '9') || (PostfixForm[i] == '.')) {
				res[index++] = atof(PostfixForm + i);
				while ((PostfixForm[i] >= '0' && PostfixForm[i] <= '9') || (PostfixForm[i] == '.'))
					++i;
				continue;
			}
			else if (PostfixForm[i] == '+') {
				if (index < 2)
					throw 1;
				--index;
				res[index - 1] += res[index];
			}
			else if (PostfixForm[i] == '-') {
				if (index < 2)
					throw 2;
				--index;
				res[index - 1] -= res[index];
			}
			else if (PostfixForm[i] == '*') {
				if (index < 2)
					throw 3;
				--index;
				res[index - 1] *= res[index];
			}
			else if (PostfixForm[i] == '/') {
				if (index < 2)
					throw 4;
				--index;
				res[index - 1] /= res[index];
			}
			else
				throw 5;
			++i;
		}
		else
			++i;
	}
	if (index != 1)
		throw 6;
	return *res;
}