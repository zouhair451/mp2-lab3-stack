const int MaxLen = 255;

class TFormula
{
private:
	char Formula[MaxLen];     // исходная формула
	char PostfixForm[MaxLen]; // постфиксная форма
public:
	TFormula(char *form);                                                    // конструктор
	int FormulaChecker(int brackets[], int size);                             // проверка корректности скобок
	int FormulaConverter();                                                  // преобразование в постфиксную форму
	double FormulaCalculator();                                              // вычисление формулы

	bool IsOperator(char str);                                               // проверка оператора
	int Priority(char str);                                                  // приоритет операции
};