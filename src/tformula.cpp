#include <stdio.h>
#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tformula.h"
#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tstack.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

     TFormula::TFormula(char *form)
     {
         int i = 0;
         for (int j = 0; j < MaxLen; j++) // fill the arrays with '\0' symbol to indicate the end of the expression later.
         {
             Formula[j] = '\0';
             PostfixForm[j] = '\0';
         }
         while(form[i])
         {
             if (i >= MaxLen)
                throw "TooLargeFormula";
             Formula[i] = form[i];
             i++;
         }
     }

     int TFormula::FormulaChecker(int Brackets[],int size) // checker of brackets sequence' correctness
     {
         int i = 0; // index for Formula
         int errors = 0;
         int number = 0; // number of each bracket
         TStack BracketsStack(size);  // Stack for opening brackets
         int j = 0; // index for Brackets[]
         // Brackets[] is the resulting table

         while (Formula[i])
         {
             if (Formula[i] == '(')
             {
                 number++;
                 BracketsStack.Put(number);
             }

             if (Formula[i] == ')')
             {
                 number++;
                 if (BracketsStack.IsEmpty()) // put (0, number)
                 {
                     if (j < size - 1)
                     {
                        Brackets[j++] = 0;
                        Brackets[j++] = number;
                     }
                     else
                        throw "OutOfOder";
                     errors++;  // the opening bracket is absent for current closing one
                 }
                 else if (j < size) // if stack is not empty, put a pair
                 {
                    Brackets[j++] = BracketsStack.Get();
                    Brackets[j++] = number; // we put a pair of opening and closing bracket (their numbers) to the resulting table
                 }
                 else
                    throw "OutOfOder";

             }
             i++;
         }

         if (!BracketsStack.IsEmpty()) // if stack is not empty after parsing of the formula. there are numbers of opening brackets (without pair) in the stack
         {
             if (j < size)
             {
                Brackets[j++] = BracketsStack.Get();
                Brackets[j++] = 0;
                errors++; // the closing bracket is absent for current opening one
             }
             else
                    throw "OutOfOder";
         }

         return errors;
     }

     int TFormula::FormulaConverter() // the formula is supposed to be correct!
     {
         int i = 0; // index for Formula[]
         int j = 0; // index for PostfixForm[]
         TStack OperationsStack(MaxLen); // stack for operations (, ), +, -, * or /

         int Brackets[MaxLen];
         if (FormulaChecker(Brackets, MaxLen) != 0) // if there are any errors
            throw "incorrect formula (brackets' checker returns errors)";
         int counter = 0;
         while (Formula[i])
         {
             if (!isOperation(Formula[i])) // if symbol is operand
             {
                 if (j >= MaxLen)
                    throw "TooLargePostfixForm";
                 PostfixForm[j++] = Formula[i]; // put the operand in the output expression
                 counter++;
             }
             else // if symbol is operation (, ), +, -, * or /
             {
                 if (counter)
                 {
                     AddSpaceAfterOperand(j);
                     counter = 0;
                 }
                 if (Priority(Formula[i]) == 0) // symbol is '('
                    OperationsStack.Put(Formula[i]);
                 else if (OperationsStack.IsEmpty()) // if stack is empty
                    OperationsStack.Put(Formula[i]);
                 else if (Priority(Formula[i]) > Priority(OperationsStack.TopElem())) // if priority of the current operation MORE than priority of the operation in the top of the stack
                        OperationsStack.Put(Formula[i]);
                 else if (Priority(Formula[i]) == 1) // symbol is ')'
                 {
                     while (OperationsStack.TopElem() != '(')
                        PostfixForm[j++] = OperationsStack.Get(); // put all operations in the output until the opening bracket in the stack
                     OperationsStack.Get(); // we kick out the opening bracket from the stack, but not put it in the output expression.
                 }
                 else
                 {
                     while (!(OperationsStack.IsEmpty()) && (Priority(Formula[i]) <= Priority(OperationsStack.TopElem())))
                        PostfixForm[j++] = OperationsStack.Get(); // put all operations (from the stack) with >= priority than current in the output expression.
                     OperationsStack.Put(Formula[i]); // then put the current operation in the stack
                 }
             }
             i++;
         }

         // we have parsed the input Formula. now we have to get all remaining operations (there are no brackets and operands already) from the stack and put them in the output expression.
         while (!OperationsStack.IsEmpty())
            PostfixForm[j++] = OperationsStack.Get();

        return 1; // OK
     }

     int TFormula::Priority(char c) // priority of operation
     {
         switch (c)
         {
             case '(':
                    return 0;
                    break;
             case ')':
                    return 1;
                    break;
             case '+':
                    return 2;
                    break;
             case '-':
                    return 2;
                    break;
             case '*':
                    return 3;
                    break;
             case '/':
                    return 3;
                    break;
             default:
                    throw c;
                    //throw "IncorrectOperation";
         }
     }

     bool TFormula::isOperation(char c) // check whether the symbol is (, ), +, -, * or /
     {
         if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
            return true;
         else
            return false;
     }

     double TFormula::FormulaCalculator()
     {
         int i = 0; // index for PostfixForm[]
         int j = 0; // index for StrOperand
         int counter = 0; // number of symbols of operand
         //TStack OperandsStack(MaxLen); // TStack is developed for char elements, that's why we can not use it for double operands
         double OperandsStack[MaxLen]; // array, actually
         int TopOfOperandsStack = -1; // "stack", which is actually array, is empty yet
         char StrOperand[MaxLen] = ""; // temporary variable for converting the operand from array of char to double
         double DoubleOperand; // operand after it has been converted
         double op1, op2, opRes;

         while (PostfixForm[i])
         {

             if (!isOperation(PostfixForm[i])) // if the symbol is operand or ' '
             {
                 // collect operand in the variable StrOperand
                 if (PostfixForm[i] != ' ')
                 {
                     StrOperand[j++] = PostfixForm[i];
                     counter++;
                     i++;
                     continue; // to the next step of loop (because we need to collect operand, which may consist of several symbols
                 }
             }

             //try to convert collected operand to number
           //  if (!DoubleOperand = atof(StrOperand))
           //     throw "Operand is not a number"; // what if operand is 0 ???
           if (counter != 0)
             {
                 DoubleOperand = atof(StrOperand); // convert
                 cout << "Operand: " << DoubleOperand << endl;
                 //OperandsStack.Put(DoubleOperand); // put operand in stack
                 if (TopOfOperandsStack == MaxLen)
                    throw "TopOfOperandsStackIsOutOfRange(ArrayIndexInFormulaCalculator)";
                 OperandsStack[++TopOfOperandsStack] = DoubleOperand;
                 for (int m = 0; m < j; m++)
                    StrOperand[m] = '\0'; // for the next step of loop
                 j = 0; // for the next step of loop
                 counter = 0;
             }

             if (isOperation(PostfixForm[i])) // if the symbol is operation +, -, *, /
             {
                 //op2 = OperandsStack.Get();
                 //op1 = OperandsStack.Get();
                 if (TopOfOperandsStack == -1)
                    throw "OperandsStackIsEmpty(ArrayInFormulaCalculator)";
                 op2 = OperandsStack[TopOfOperandsStack--];
                 if (TopOfOperandsStack == -1)
                    throw "OperandsStackIsEmpty(ArrayInFormulaCalculator)";
                 op1 = OperandsStack[TopOfOperandsStack--];

                 switch (PostfixForm[i])
                 {
                     case '+': opRes = op1 + op2; break;
                     case '-': opRes = op1 - op2; break;
                     case '*': opRes = op1 * op2; break;
                     case '/': opRes = op1 / op2; break;
                     default:
                         throw PostfixForm[i];
                        //throw "incorrect operation during formula calculation";
                 }
                 cout << "Res: " << opRes << endl;

                 //OperandsStack.Put(opRes);
                if (TopOfOperandsStack == MaxLen)
                    throw "TopOfOperandsStackIsOutOfRange(ArrayIndexInFormulaCalculator)";
                OperandsStack[++TopOfOperandsStack] = opRes;
             }

             i++;
         }
         if (TopOfOperandsStack == -1)
                    throw "OperandsStackIsEmpty(ArrayInFormulaCalculator)";
         return OperandsStack[TopOfOperandsStack--]; //OperandsStack.Get(); // return the result after parsing of the expression
     }

     void TFormula::ShowFormula()
     {
         int i = 0;
         cout << "Formula[]: ";
         while (Formula[i])
         {
             cout << Formula[i];
             i++;
         }
         cout << endl;

     }

     void TFormula::ShowPostfixForm()
     {
         int i = 0;
         cout << "PostfixForm[]: ";
         while (PostfixForm[i])
         {
             cout << PostfixForm[i];
             i++;
         }
         cout << endl;
     }

     void TFormula::AddSpaceAfterOperand(int & j)
     {
         if (j >= MaxLen)
                    throw "TooLargePostfixFormDuringTryingToAddSpace";
         PostfixForm[j++] = ' ';
     }
