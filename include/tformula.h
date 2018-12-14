const int MaxLen=255;

class TFormula
{
   private:
     char Formula[MaxLen];     // исходная формула
     char PostfixForm[MaxLen]; // постфиксная форма
	 int formulaLength;
	 int postfixFormulaLength = 0;
   public:
     TFormula(char *form);                            // конструктор
     int FormulaChecker();     // проверка корректности скобок
     int FormulaConverter();                          // преобразование в постфиксную форму
     double FormulaCalculator();                      // вычисление формулы
	 int Priority(char sign);
};
