#include "tstack.h"
const int MaxLen = 255;

#ifndef __TFORMULA_H__
#define __TFORMULA_H__

class TFormula
{
private:
	char Formula[MaxLen];     // исходная формула
	char PostfixForm[MaxLen]; // постфиксная форма
public:
	int GetSizePostfixForm();
	TFormula(const char* form);                            // конструктор
	char* GetFormula();
	int FormulaChecker();     // проверка корректности скобок
	int FormulaConverter();                          // преобразование в постфиксную форму
	char* GetPostfixForm();
	double FormulaCalculator();                      // вычисление формулы
};

#endif