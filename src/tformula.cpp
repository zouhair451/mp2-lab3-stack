#include "tformula.h"

#include <iostream>

using namespace std;

TFormula::TFormula(const char *form)
{
    int i = 0;
    while(form[i])
    {
        if(i == MaxLen)
            throw -1;
        Formula[i] = form[i];
        i++;
    }
    Formula[i] ='\0';
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
    TStack st(size);
    int k = 0;
    int id = 0;
    int i = 0;
    while(Formula[i])
    {
        if(!(Formula[i]>='0' && Formula[i] <= '9') && Formula[i] != '.' && Formula[i] != '(' && Formula[i] != ')' && Formula[i] != '+'
            && Formula[i] != '-' && Formula[i] != '*' && Formula[i] != '/' && Formula[i] != ' ')
            throw -1;
        if(Formula[i] == '(')
        {
            ++k;
            st.Put(k);
        }
        if(Formula[i] == ')')
        {
            ++k;
            if(st.IsEmpty())
                Brackets[id++] = -1;
            else
            {
                Brackets[id++] = st.Get();
            }
            Brackets[id++] = k;
        }
        i++;
    }
    while(!st.IsEmpty())
    {
        Brackets[id++] = st.Get();
        Brackets[id++] = -1;
    }
    return id;
}

int TFormula::FormulaConverter()
{
    int i = 0;
    int id = 0;
    int Brackets[260];
    int kol = FormulaChecker(Brackets, 260);
    for(int i = 0; i < kol; i++)
    {
        if(Brackets[i] == -1)
            throw -1;
    }
    i = 0;
    TStack st1(260), st2(260);
    while(Formula[i])
    {
        int k = i;
        while(((Formula[i] >= '0' && Formula[i] <= '9') || Formula[i] == '.') && Formula[i] != '\0')
        {
            PostfixForm[id++] = Formula[i];
            i++;
        }
        if(k != i)
            PostfixForm[id++] = ' ';
        switch(Formula[i])
        {
            case '(':
                st1.Put(0), st2.Put('(');
                break;
            case ')':
                while(st1.TopElem() != 0)
                {
                    st1.Get();
                    PostfixForm[id++] = st2.Get();
                }
                st1.Get();
                st2.Get();
                break;
            case '+':
                while(!st1.IsEmpty() && st1.TopElem() >= 2)
                {
                    st1.Get();
                    int k = st2.Get();
                    if(k != '(')
                        PostfixForm[id++] = k;
                }
                st1.Put(2), st2.Put('+');
                break;
            case '-':
                while(!st1.IsEmpty() && st1.TopElem() >= 2)
                {
                    st1.Get();
                    int k = st2.Get();
                    if(k != '(')
                        PostfixForm[id++] = k;
                }
                st1.Put(2), st2.Put('-');
                break;
            case '*':
                while(!st1.IsEmpty() && st1.TopElem() >= 3)
                {
                    st1.Get();
                    int k = st2.Get();
                    if(k != '(')
                        PostfixForm[id++] = k;
                }
                st1.Put(3), st2.Put('*');
                break;
            case '/':
                while(!st1.IsEmpty() && st1.TopElem() >= 3)
                {
                    st1.Get();
                    int k = st2.Get();
                    if(k != '(')
                        PostfixForm[id++] = k;
                }
                st1.Put(3), st2.Put('/');
                break;
        }
        i++;
    }
    while(!st1.IsEmpty())
    {
        st1.Get();
        int k = st2.Get();
        if(k != '(')
            PostfixForm[id++] = k;
    }
    PostfixForm[id++] = '\0';
    return id;
}

double TFormula::FormulaCalculator()
{
    FormulaConverter();
    int i = 0;
    double DoubleStack[260];
    int top = -1;
    while(PostfixForm[i])
    {
        if((PostfixForm[i] >= '0' && PostfixForm[i] <= '9') || PostfixForm[i] == '.')
        {
            DoubleStack[++top] = atof(PostfixForm + i);;
            while(PostfixForm[i] != ' ')
                i++;
            i++;
            continue;
        }
        double t1 = DoubleStack[top--];
        double t2 = DoubleStack[top--];
        if(top < -1)
            throw -1;
        switch(PostfixForm[i])
        {
            case '+':
                DoubleStack[++top] = t2+t1;
                break;
            case '-':
                DoubleStack[++top] = t2-t1;
                break;
            case '*':
                DoubleStack[++top] = t2*t1;
                break;
            case '/':
                DoubleStack[++top] = t2/t1;
                break;
        }
        i++;
    }
    if(top != 0)
        throw -1;
    return DoubleStack[top];
}
