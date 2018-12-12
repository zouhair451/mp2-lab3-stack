#include"tformula.h"
#include"tstack.h"
#include"templateStack.h"
//#include<cstring>
#include<locale>
#include<vector>

int op_priority(char);
bool piece_of_number(char);

TFormula::TFormula(char *form)
{
  if (strlen(form) >= MaxLen)
    throw "buffer_overflow";
  strcpy(Formula, form);
  for(int i = 0; i < MaxLen; ++i)
    PostfixForm[i] = 0;
}

int TFormula::FormulaChecker(int Brackets[], int Size)
{
  int err = 0, index = 0, bracket_number = 1;
  char *pSym = Formula;
  TStack stack_brackets(Size);

  for (int i = 0; i < Size; ++i)
    Brackets[i] = -1;

  do
  {
    switch (*pSym)
    {
    case '(':
      stack_brackets.Put(bracket_number++);
      break;
    case ')':
      if (stack_brackets.IsEmpty())
      {
        Brackets[index++] = 0;
        Brackets[index++] = bracket_number++;
        ++err;
      }
      else
      {
        Brackets[index++] = stack_brackets.Get();
        Brackets[index++] = bracket_number++;
      }
      break;
    }
  } while (*++pSym);

  while (!stack_brackets.IsEmpty())
  {
    Brackets[index++] = stack_brackets.Get();
    Brackets[index++] = 0;
    ++err;
  }

  return err;
}

int TFormula::FormulaConverter()
{
  char *pSym = Formula;
  int index = 0, priority;
  TStack stack_operators(MaxLen);

  int brackets[MaxLen * 2];
  if (FormulaChecker(brackets, MaxLen * 2) != 0)
    return 0;

  do
  {
    priority = op_priority(*pSym);

    if (priority == -2)
      continue;                                                      //если встречаем пробел в исходной строке - едем дальше

    if (priority == 2 || priority == 3)
      PostfixForm[index++] = ' ';                                    //разделяем операнды пробелом в выходной строке

    if (*pSym == ')')                                                //специальная обработка '('
    {
      while (stack_operators.TopElem() != '(')                       //
        PostfixForm[index++] = stack_operators.Get();                //
      stack_operators.Get();                                         //выписываем из стека все операторы до '(' включительно
      continue;
    }

    if (priority == -1)
      PostfixForm[index++] = *pSym;                                  //записываем операнд в постфиксную строку
    else if (priority == 0 || stack_operators.IsEmpty())
      stack_operators.Put(*pSym);                                    //
    else if ( priority > op_priority(stack_operators.TopElem()) )           
      stack_operators.Put(*pSym);                                    //Кладем оператор в стек, если надо
    else
    {
      while (priority <= op_priority(stack_operators.TopElem()))
      {
        PostfixForm[index++] = stack_operators.Get();                //выписываем из стека нужные операторы
        if (stack_operators.IsEmpty())
          break;
      }
      stack_operators.Put(*pSym);                                    //кладем новый оператор
    }

  } while (*++pSym);

  while (!stack_operators.IsEmpty())
    PostfixForm[index++] = stack_operators.Get();                    //выписывем оставшиеся операторы из стека

  return 1;
}

double TFormula::FormulaCalculator()
{
  char *pSym = PostfixForm, operand_str[MaxLen];
  int s;
  Stack<double> stack_operands(MaxLen);

  do
  {
    if (op_priority(*pSym) == -2)
      continue;                                                      //пропускаем пробелы

    if (piece_of_number(*pSym))                                      //если наткнулись на цифру или точку
    {
      std::vector<char> tmp_vec;
      do
      {
        tmp_vec.push_back(*pSym);                                    //посимвольно считываем операнд и записываем во временный вектор
      } while (piece_of_number(*++pSym));
      tmp_vec.push_back('\0');
      --pSym;

      copy(tmp_vec.begin(), tmp_vec.end(), operand_str);

      stack_operands.Push(atof(operand_str));                        //переводим строку в число и кладем в стек
    }
    else
    {
      double op2 = stack_operands.Pop();                             //
      double op1 = stack_operands.Pop();                             //достаем операторы

      double result;

      switch (*pSym)                                                 //записываем результат соответствующей операции
      {
      case '+':
        result = op1 + op2;
        break;
      case '-':
        result = op1 - op2;
        break;
      case '/':
        result = op1 / op2;
        break;
      case '*':
        result = op1 * op2;
        break;
      }

      stack_operands.Push(result);                                   //кладем результат в стек
    }

  } while (*++pSym);

  return stack_operands.Pop();
}



int op_priority(char ch)
{
  switch (ch)
  {
  case '(':
    return 0;
  case ')':
    return 1;
  case '+':
  case '-':
    return 2;
  case '*':
  case '/':
    return 3;
  case ' ':
  case '\t':
    return -2;
  default:
    return -1;
  }
}

bool piece_of_number(char ch)
{
  return isdigit(ch) || ch == '.';
}