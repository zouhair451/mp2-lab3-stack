const int MaxLen=255;

class TFormula
{
   private:
     char Formula[MaxLen];     // исходная формула
     char PostfixForm[MaxLen]; // постфиксная форма
   public:
     TFormula(char *form);                            // конструктор
     int FormulaChecker(int Brackets[],int size);     // проверка корректности скобок
     int FormulaConverter();                          // преобразование в постфиксную форму
     double FormulaCalculator();                      // вычисление формулы
     int Priority(char c); // priority of operation
     bool isOperation(char c); // check whether the symbol is (, ), +, -, * or /
     void ShowFormula();
     void ShowPostfixForm();
};
