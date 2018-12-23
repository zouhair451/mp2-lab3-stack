#include "tformula.h"



#include "gtest.h"



TEST(TFormula, can_create_class_object)

{

    char *p="abacaba";

    ASSERT_NO_THROW(TFormula a(p););

}



TEST(TFormula, brackets_is_correct1)

{

    int b[25];

    TFormula a("((())()())(())");

    ASSERT_TRUE(a.FormulaChecker(b,25)==0);

}



TEST(TFormula, brackets_is_correct2)

{

    int b[25];

    TFormula a("(1+7)*((7/4)-5)");

    ASSERT_TRUE(a.FormulaChecker(b,25)==0);

}



TEST(TFormula, brackets_is_incorrect1)

{

    int b[25];

    TFormula a("((())(()())(())");

    ASSERT_FALSE(a.FormulaChecker(b,25)==0);

}



TEST(TFormula, brackets_is_incorrect2)

{

    int b[25];

    TFormula a("()))))");

    ASSERT_FALSE(a.FormulaChecker(b,25)==0);

}



TEST(TFormula, calculation_test1)

{

    TFormula a("(5) - (5) *3+(7+5.6+3.2+5.323+65)*6");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),506.738,0.0000001);

}



TEST(TFormula, calculation_test2)

{

    TFormula a("1+(1+(1+(1+(1))))");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),5.0,0.0000001);

}



TEST(TFormula, calculation_test3)

{

    TFormula a("2+2*2");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),6.0,0.0000001);

}



TEST(TFormula, calculation_test4)

{

    TFormula a("20/(4/(2))/2");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),5.0,0.0000001);

}



TEST(TFormula, calculation_test5)

{

    TFormula a("1");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),1.0,0.0000001);

}



TEST(TFormula, calculation_test6)

{

    TFormula a("0+4*(4-34)");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),-120.0,0.0000001);

}



TEST(TFormula, calculation_test7)

{

    TFormula a("1+1+1+1+5*2-44/11");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),10.0,0.0000001);

}



TEST(TFormula, calculation_test8)

{

    TFormula a("(((9)))");

    a.FormulaConverter();

    ASSERT_NEAR(a.FormulaCalculator(),9.0,0.0000001);

}



TEST(TFormula, wrong_formula1)

{

    TFormula a("9 8");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula2)

{

    TFormula a("*76");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula3)

{

    TFormula a("65+a");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula4)

{

    TFormula a("(56) 6");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula5)

{

    TFormula a("(4)(7)");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula6)

{

    TFormula a("(6-)");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula7)

{

    TFormula a("(11())");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula8)

{

    TFormula a("(3(-6))");

    EXPECT_NE(0,a.FormulaConverter());

}



TEST(TFormula, wrong_formula_calculating_is_not_awaliable)

{

    TFormula a("7+7*(6+5+4+3+2+1+)");

    a.FormulaConverter();

    ASSERT_ANY_THROW(a.FormulaCalculator());

}

