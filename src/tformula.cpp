#include "tformula.h"

#include "tstack.h"

#include <stdlib.h>



TFormula::TFormula(char* form)

{

    int i=0;

    while ((form[i]!='\0')&&(i<MaxLen-1))

    {

        Formula[i]=form[i];

        ++i;

    }

    Formula[i]='\0';

    for (int j=0;j<MaxLen;++j)

        PostfixForm[j]='\0';

}



int TFormula::FormulaChecker(int Brackets[],int size)

{

    TStack br(MaxLen);

    int k=0;

    int err=0;

    for (int i=0;Formula[i]!='\0';++i)

    {

        if (Formula[i]=='(')

        {

            br.Put(k);

            k++;

        }

        else if (Formula[i]==')')

        {

            if (br.IsEmpty())

            {

                ++err;

                if (k<size)

                    Brackets[k]=-1;

            }

            else

            {

                if (k<size)

                    Brackets[k]=br.TopElem();

                if (br.TopElem()<size)

                    Brackets[br.Get()]=k;

            }

            k++;

        }

    }

    while (!br.IsEmpty())

    {

        Brackets[br.Get()]=-1;

        ++err;

    }

    return err;

}



int TFormula::FormulaConverter()

{

    TStack opr(MaxLen/2+1);

    int pfsiz=0;

    int prev_object=-1;

    char sym[4][2]={{'(','\0'},{')','\0'},{'+','-'},{'*','/'}};

    for (int i = 0; (i<MaxLen) && (Formula[i]!='\0'); ++i)

    {

        if ((Formula[i]==' ')||(Formula[i]=='\n')||(Formula[i]=='\t')||(Formula[i]=='\v'))

            continue;

        else if (((Formula[i]>='0')&&(Formula[i]<='9'))||(Formula[i]=='.'))

        {

            if ((prev_object==0)||(prev_object==2))

                return 1;

            while (((Formula[i]>='0')&&(Formula[i]<='9')))

                PostfixForm[pfsiz++]=Formula[i++];

            if (Formula[i]=='.')

                PostfixForm[pfsiz++]=Formula[i++];

            while (((Formula[i]>='0')&&(Formula[i]<='9')))

                PostfixForm[pfsiz++]=Formula[i++];

            PostfixForm[pfsiz++]=' ';

            --i;

            prev_object=0;

        }

        else if (Formula[i]=='(')

        {

            if ((prev_object==0)||(prev_object==2))

                return 2;

            opr.Put(0);

            prev_object=1;

        }

        else if (Formula[i]==')')

        {

            if ((prev_object!=0)&&(prev_object!=2))

                return 2;

            int val;

            while ((val=opr.Get())!=0)

                PostfixForm[pfsiz++]=sym[val/10][val%10];

            prev_object=2;

        }

        else

        {

            if ((prev_object!=0)&&(prev_object!=2))

                return 3;

            int val,val2;

            switch (Formula[i])

            {

                case '+':

                    val=20;

                    break;

                case '-':

                    val=21;

                    break;

                case '*':

                    val=30;

                    break;

                case '/':

                    val=31;

                    break;

                default:

                    return -1;

            }

            while ((!opr.IsEmpty())&&((val2=opr.TopElem())/10>=val/10))

            {

                PostfixForm[pfsiz++]=sym[val2/10][val2%10];

                opr.Get();

            }

            opr.Put(val);

            prev_object=3;

        }

    }

    while (!opr.IsEmpty())

    {

        PostfixForm[pfsiz++]=sym[opr.TopElem()/10][opr.TopElem()%10];

        opr.Get();

    }

    return 0;

}



double TFormula::FormulaCalculator()

{

    double st[MaxLen/2+1];

    int ps=0;

    if (PostfixForm[0]=='\0')

        FormulaConverter();

    int i=0;

    while (PostfixForm[i]!='\0')

    {

        if ((PostfixForm[i]==' ')||(PostfixForm[i]=='\n')||(PostfixForm[i]=='\t')||(PostfixForm[i]=='\v'))

        {

            ++i;

            continue;

        }

        else if (((PostfixForm[i]>='0')&&(PostfixForm[i]<='9'))||(PostfixForm[i]=='.'))

        {

            st[ps++]=atof(&PostfixForm[i]);

            while (((PostfixForm[i]>='0')&&(PostfixForm[i]<='9'))||(PostfixForm[i]=='.'))

                ++i;

        }

        else

        {

            if (ps<2)

                throw -1;

            switch (PostfixForm[i])

            {

                case '+':

                    st[ps-2]+=st[ps-1];

                    break;

                case '-':

                    st[ps-2]-=st[ps-1];

                    break;

                case '*':

                    st[ps-2]*=st[ps-1];

                    break;

                case '/':

                    st[ps-2]/=st[ps-1];

                    break;

                default:

                    throw -2;

            }

            --ps;

            ++i;

        }

        if (ps<1)

            throw -1;

    }

    if (ps!=1)

        throw -1;

    return st[ps-1];

}