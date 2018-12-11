// this main_formula.cpp is a sample for tformula.cpp

#include <iostream>
#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tformula.h"

using namespace std;

int main()
{
    char expression[] = "(12+12)/(2+4*1)-5*4"; // supposed result is -16
    TFormula f(expression);
    int Brackets[], brsize = 20;
    f.FormulaChecker(Brackets, brsize);

    return 0;
}
