#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>
#include "tformula.h"
#include "tstack.h"

TFormula::TFormula(const char* form)
{
    formulaLength = strlen(form);
    postfixFormulaLength = 0;

    if (formulaLength == 0) 
        throw std::range_error("Unexpected formula length");

    strcpy(Formula, form);
}

int TFormula::FormulaChecker(int* Brackets, int size)
{
  TStack stack(formulaLength);
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

  std::cout << "\t BRACKETS \n  Opening   |   Closing" << std::endl;  // вывод таблицы
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

  std::cout << "  Errors: " << errIndex << std::endl;

  return errIndex;
}

int TFormula::FormulaConverter()
{
  return -1;
}

double TFormula::FormulaCalculator()
{
  int* Brackets = new int[formulaLength * 2];

  if (FormulaChecker(Brackets, formulaLength * 2) != 0)
  {
    throw std::logic_error("Incorrect formula");
    return -1;
  }

  return 0;
}

int Priority(char sign)
{
  switch (sign)
  {
    case '(' : return 0;
    case ')' : return 1;
    case '+' || '-' :  return 2;
    case '*' : return 3;
    case '/' : return 3;
    default : return -1;
  }
}