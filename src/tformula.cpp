#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>
#include <cstring>
#include "tformula.h"

TFormula::TFormula(const char* form)
{
    formulaLength = std::strlen(form);
    postfixFormulaLength = 0;

    if (formulaLength == 0) 
        throw std::range_error("Unexpected formula length");

    std::strcpy(Formula, form);
}

int TFormula::FormulaChecker()
{
  TStack stack(formulaLength);
  int* Brackets = new int[formulaLength * 2]{};
  int bracketsCount = 0;
  int bracketsArrIndex = 0;
  int errIndex = 0;

  for (auto i = 0; i < formulaLength; i++)                            // поиск пар скобок
  {
    if (Formula[i] == '(')
      stack.Put(++bracketsCount);
    else
      {
        if (Formula[i] == ')')
        {
          Brackets[++bracketsArrIndex] = ++bracketsCount;

          if (stack.IsEmpty())
          {
            Brackets[--bracketsArrIndex] = 0;
            bracketsArrIndex += 2;
            errIndex++;
          }
          else
          {
            Brackets[--bracketsArrIndex] = stack.Get();
            bracketsArrIndex += 2;
          }
        }
        else
          continue;
      }
  }

  if (!stack.IsEmpty())                                                // запись оставшихся в стеке открывающих скобок
  {
    while (!stack.IsEmpty())
    {
      Brackets[bracketsArrIndex++] = stack.Get();
      Brackets[bracketsArrIndex++] = 0;
      errIndex++;
    }
  }

  std::cout << "\033[91m\t BRACKETS \n  Opening   |   Closing\033[0m" << std::endl;  // вывод таблицы
  for (auto i = 0; i < bracketsArrIndex;)
  {
    if ((i + 1) % 2 != 0)
      if (Brackets[i] == 0)
      {
        std::cout << "     " << "-" << "      |      ";
        i++;
      }
      else
        std::cout << "     " << Brackets[i++] << "      |      ";
    else
      if (Brackets[i] == 0)
      {
        std::cout << "-" << std::endl;
        i++;
      }
      else
        std::cout << Brackets[i++] << std::endl;;
  }

  std::cout << std::endl << "\033[91m  Errors: \033[0m" << errIndex << std::endl;

  return errIndex;
}

int TFormula::FormulaConverter()
{
  TStack stack(formulaLength);

  for (auto i = 0; i < formulaLength; i++)
  {
    if (isdigit(Formula[i]))
    {
      PostfixForm[postfixFormulaLength++] = Formula[i];
    }
    else  if (Formula[i] != ')')
          {
            if ((!stack.IsEmpty() && (Priority(Formula[i]) == 0 || 
                  Priority(Formula[i]) > Priority(stack.TopElem()))) || 
                  stack.IsEmpty())
              stack.Put(Formula[i]);
            
            else
            {
              while (!stack.IsEmpty() && 
                      Priority(stack.TopElem()) >= Priority(Formula[i]))
                PostfixForm[postfixFormulaLength++] = stack.Get();
              
              stack.Put(Formula[i]);
            }
          }
          else
          {
            while (!stack.IsEmpty() && 
                    Priority(stack.TopElem()) != Priority('('))
              PostfixForm[postfixFormulaLength++] = stack.Get();

            stack.Get();
          }
    }

  while (!stack.IsEmpty())
    PostfixForm[postfixFormulaLength++] = stack.Get();

  return 0;
}

double TFormula::FormulaCalculator()
{
  TStack stack(formulaLength);
  int leftOperator = 0;
  int rightOperator = 0;

  if (FormulaChecker() != 0)                                                        //проверка скобок
  {
    throw std::logic_error("Incorrect formula");
    return -1;
  }

  std::cout << std::endl << "\033[91m \t ORIGINAL FORMULA: \033[0m";                //вывод исходной формулы
  for (auto i = 0; i < formulaLength; i++)
  {
    std::cout << Formula[i];
  }
  std::cout << std::endl;

  if (postfixFormulaLength == 0)                                                    //перевод в постфиксную форму
    FormulaConverter();

  std::cout << std::endl << "\033[91m \t POSTFIX FORMULA: \033[0m";                 //вывод постфиксной формы
  for (auto i = 0; i < postfixFormulaLength; i++)
  {
    std::cout << PostfixForm[i];
  }
  std::cout << std::endl;

  for (auto i = 0; i < postfixFormulaLength; i++)                                   //подсчет формулы
  {
    if (isdigit(PostfixForm[i]))
    {
      stack.Put(PostfixForm[i] - '0');
    }
    else
    {
      leftOperator = stack.Get();
      rightOperator = stack.Get();

      switch (PostfixForm[i])
      {
        case '+' : 
          stack.Put(rightOperator + leftOperator);
          break;
        case '-' : 
          stack.Put(rightOperator - leftOperator);
          break;
        case '*' : 
          stack.Put(rightOperator * leftOperator);
          break;
        case '/' : 
          stack.Put(rightOperator / leftOperator);
          break;
      }
    }
  }

  std::cout << std::endl << "\033[91m \t RESULT: \033[0m" << stack.TopElem() << std::endl;  

  return stack.Get();
}

int TFormula::Priority(char sign)
{
  switch (sign)
  {
    case '(' : return 0;
    case ')' : return 1;
    case '+' : return 2;
    case '-' : return 2;
    case '*' : return 3;
    case '/' : return 3;
    default : return -1;
  }
}