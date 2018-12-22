#include<string>
const int MaxLen = 255;

class TFormula
{
private:
	char Formula[MaxLen];     // исходная формула
	char PostfixForm[MaxLen]; // постфиксная форма
	int lenghtFormula; // длина формулы
	int lenghtPostfixForm;
public:
	TFormula(char *form);                            // конструктор
	TFormula(std::string form);                            // конструктор преобразования типа
	int FormulaChecker(int Brackets[], int size);     // проверка корректности скобок
	int FormulaConverter();                          // преобразование в постфиксную форму
	double FormulaCalculator();                      // вычисление формулы
};
int PriorityOper(char sign);