#include <iostream>
#include "tstack.h"
#include "tformula.h"
#include "gtest.h"

TEST(Stack, can_put_in_stack)
{
	Stack st(2);
	st.Put(50);
	EXPECT_EQ(st.TopElem(),50);
}

TEST(Stack, check_RetCode)
{
	Stack st(2);
	EXPECT_EQ(st.GetRetCode(), DataOK);
}

TEST(Stack, can_get_from_stack)
{
	Stack st(2);
	st.Put(50);
	int t = st.Get();
	EXPECT_EQ(t, 50);
}

TEST(Stack, Stack_with_size_equal_0_get)
{
	Stack st(0);
	st.Get();
	EXPECT_EQ(st.GetRetCode(), DataNoMem);
}

TEST(Stack, Stack_with_size_equal_0_put)
{
	Stack st(0);
	st.Put(5);
	EXPECT_EQ(st.GetRetCode(), DataFull);
}

TEST(Stack, IsEmpty_is_correct)
{
	Stack st(0);
	EXPECT_EQ(st.IsEmpty(),1);
}

TEST(Stack, IsFull_is_correct)
{
	Stack st(20);
	for (int i = 0; i < 20; ++i)
		st.Put(i);
	EXPECT_EQ(st.IsFull(),1);
}

TEST(Stack, SetRetCode_is_correct_on_DataFull)
{
	Stack  st(5);
	for (int i = 0; i < 5; ++i) st.Put(i);
	st.Put(6);
	EXPECT_EQ(st.GetRetCode(), DataFull);
	
}

TEST(Stack, Check_IsValid)
{
	Stack st(0);
	EXPECT_EQ(st.IsValid(), 1);
}

TEST(Stack, cannot_put_in_stack_which_was_declare_with_size_equal_0)
{
	Stack st(0);
	st.Put(5);
	EXPECT_EQ(st.IsEmpty(), 1);
}

TEST(Stack, check_DefMemSize)
{
	Stack st;
	for (int i = 0; i < 25; ++i) st.Put(i);
	EXPECT_EQ(st.IsFull(), 1);
}

TEST(Stack, check_equal_between_put_and_get)
{
	Stack st(10);
	for (int i = 0; i < 10; ++i) st.Put(i);
	for (int i=9;i>=0;--i) EXPECT_EQ(st.Get(), i);
}

TEST(Stack, check_TopElem)
{
	Stack st(5);
	EXPECT_EQ(st.TopElem(), -1);
}

TEST(Stack, SetRetCode_is_correct_on_DataEmpty)
{
	Stack  st(1);
	st.Get();
	st.Get();
	EXPECT_EQ(st.GetRetCode(), DataEmpty);
}

TEST(TFormula, check_Formula_1)
{
	TFormula t("(1+2)/3");
	EXPECT_EQ(t.FormulaCalculator(), 1);
}

TEST(TFormula, check_Formula_2)
{
	TFormula t("16/(40/10)/2");
	EXPECT_EQ(t.FormulaCalculator(), 2.0);
}

TEST(TFormula, FormulaChecker_3)
{
	TFormula t("()(16/(40/10)/2)");
	int  c[255];
	EXPECT_EQ(t.FormulaChecker(c,255), 0);
}

TEST(TFormula, FormulaChecker_4)
{
	TFormula t("(()");
	int  c[255];
	EXPECT_EQ(t.FormulaChecker(c,255), 1);
	
}

TEST(TFormula, FormulaChecker_5)
{
	TFormula t("(()))");
	int c[255];
	EXPECT_EQ(t.FormulaChecker(c,255), 1);
	
}

TEST(TFormula, FormulaChecker_6)
{
	TFormula t("(())");
	int  c[255];
	EXPECT_EQ(t.FormulaChecker(c,255), 0);
	
}

TEST(TFormula, FormulaChecker_7)
{
	TFormula t(")(");
	int  c[255];
	EXPECT_FALSE(t.FormulaChecker(c,255)==0);
}

TEST(TFormula, check_Formula_8)
{
	TFormula t("(1)");
	EXPECT_EQ(t.FormulaCalculator(), 1);
	
}

TEST(TFormula, check_Formula_9)
{
	TFormula t("(1+2)/(3+4*6.7)-5.3*4.4");
	ASSERT_EQ(t.FormulaCalculator(), (1 + 2) / (3 + 4 * 6.7) - 5.3*4.4);
}

TEST(TFormula, check_Formula_10)
{
	TFormula t("8-6/2");
	ASSERT_EQ(t.FormulaCalculator(), 8 - 6 / 2);
}

TEST(TFormula, check_Formula_11)
{
	TFormula t("(0-4)+5");
	ASSERT_EQ(t.FormulaCalculator(), (-4) + 5);
}

TEST(TFormula, check_Formula_12)
{
	TFormula t("1/(3+1)");
	ASSERT_EQ(t.FormulaCalculator(), 1.0/(3 + 1));
}

TEST(TFormula, check_Formula_13)
{
	TFormula t("1/2/3/4/5");
	ASSERT_EQ(t.FormulaCalculator(), 1.0 / 2 / 3 / 4 / 5);
}

TEST(TFormula, check_Formula_14)
{
	TFormula t("1/2+2/1");
	ASSERT_EQ(t.FormulaCalculator(), 1.0 / 2 + 2.0 / 1);
	
}

TEST(TFormula, check_Formula_15)
{
	TFormula t("1-8-1+8");
	ASSERT_EQ(t.FormulaCalculator(), 1 - 8 - 1 + 8);
}

TEST(TFormula, check_Formula_16)
{
	TFormula t("2.34-1.5*4/6");
	ASSERT_EQ(t.FormulaCalculator(), 2.34 - 1.5 * 4 / 6);
	
}

TEST(TFormula, check_Formula_17)
{
	TFormula t("1.33333333333333*3-4");
	ASSERT_EQ(t.FormulaCalculator(), 1.33333333333333 * 3 - 4);
}

TEST(TFormula, check_Formula_18)
{
	TFormula t("(5)-(5)");
	ASSERT_EQ(t.FormulaCalculator(), (5) - (5));
}

TEST(TFormula, check_Formula_19)
{
	TFormula t("1.6180339887*(1.6180339887-1)");
	ASSERT_EQ(t.FormulaCalculator(), 1.6180339887 * (1.6180339887 - 1));
}

TEST(TFormula, check_Formula_20)
{
	TFormula t("1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1+1-1");
	ASSERT_EQ(t.FormulaCalculator(), 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1 + 1 - 1);
}

TEST(TFormula, check_FormulaChecker_21)
{
	TFormula t("((1+34+5*5.5-45/2)))");
	ASSERT_ANY_THROW(t.FormulaCalculator());
}

TEST(TFormula, check_FormulaChecker_22)
{
	TFormula t("(()))");
	int g[255];
	t.FormulaChecker(g, 100);
	ASSERT_EQ(g[0], 2);
	ASSERT_EQ(g[1], 3);
}

TEST(TFormula, check_FormulaChecker_23)
{
	TFormula t("(1         +     2)/    3");
	ASSERT_EQ(t.FormulaCalculator(), (1 + 2) / 3);
}

TEST(TFormula, check_FormulaChecker_24)
{
	TFormula t("(1)+(3)+(4)-(5)");
	EXPECT_EQ(t.FormulaCalculator(), (1) + (3) + (4) - (5));
}

TEST(TFormula, check_FormulaChecker_25)
{
	TFormula t("2- (6)/   (5) +1/(1230.23-9)");
	EXPECT_EQ(t.FormulaCalculator(), 2 - (6.0) / (5) + 1 / (1230.23 - 9));
	
}

TEST(TFormula, check_FormulaChecker_26)
{
	TFormula t("1                                  -1");
	EXPECT_EQ(t.FormulaCalculator(), 0);
}

TEST(TFormula, check_FormulaChecker_27)
{
	TFormula t("1               ()                   -1");
	EXPECT_EQ(t.FormulaCalculator(), 0);
}

TEST(TFormula, check_FormulaChecker_q_errors_28)
{
	TFormula t("(()");
	int g[255];
	ASSERT_EQ(t.FormulaChecker(g,255),1);
	
}
