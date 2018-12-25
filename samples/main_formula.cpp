
// this main_formula.cpp is a sample for tformula.cpp

#include <iostream>
#include <cstdlib>
//#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tformula.h"
#include "tformula.h"

using namespace std;

int main()
{
    char expression[] = "(a+b1)/2+6.5)*(4.8+sin(x)";
    TFormula f(expression);
    int Brackets[10] = {-1}, brsize = 10, res;
    res = f.FormulaChecker(Brackets, brsize);
    cout << res << endl;

    for (int i = 0; i < 9; i+=2)
    {
        cout << "(" << Brackets[i] << ", " << Brackets[i+1] << ") " << endl;
    }
    cout << "------FormulaChecker is not passed ----------" << endl;

    //===========NEXT SAMPLE================

    char expression2[] = "(12+12/(2+4*1)-5*4"; // supposed result is -16
    TFormula f2(expression2);
    int Brackets2[4] = {-1}, brsize2 = 4, res2;
    res2 = f2.FormulaChecker(Brackets2, brsize2);
    cout << res2 << endl;

    for (int i = 0; i < 3; i+=2)
    {
        cout << "(" << Brackets2[i] << ", " << Brackets2[i+1] << ") " << endl;
    }
    cout << "------FormulaChecker is not passed ----------" << endl;

    // let's try to parse it
    try{
        f2.FormulaConverter();
        double result2 = f2.FormulaCalculator();
        cout << result2 << endl;
    }
    catch (const char* excep)
    {
        cout << excep << endl;
    }
    cout <<"-----we can not parse incorrect expression. let's correct it----"<< endl;

    //===========NEXT SAMPLE================

    char expression3[] = "(12+12)/(2+4*1)-5*4";
    TFormula f3(expression3);
    f3.ShowFormula();
    int Brackets3[4] = {-1}, brsize3 = 4, res3;
    res3 = f3.FormulaChecker(Brackets3, brsize3);
    cout << res3 << endl;

    for (int i = 0; i < 3; i+=2)
    {
        cout << "(" << Brackets3[i] << ", " << Brackets3[i+1] << ") " << endl;
    }
    cout << "------FormulaChecker is passed ----------" << endl;

    // let's try to parse "(12+12)/(2+4*1)-5*4"
    try{
        f3.FormulaConverter();
        f3.ShowPostfixForm();
        double result3 = f3.FormulaCalculator();
        cout << "Result is: " << result3 << endl;
    }
    catch (const char* excep)
    {
        cout << excep << endl;
    }
    catch (char c)
    {
        cout << "Thrown symbol: ";
        cout << c << endl;
    }

    system("pause");
    return 0;
}

