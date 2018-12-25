#include "gtest.h"
#include "tstack.h"
#include "tformula.h"
#include <iostream>
using namespace std;


TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack(5));
}

TEST(TStack, cant_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack(-10));
}

TEST(TStack, can_put_and_get_element)
{
	TStack s(10);
	s.Put(1);
	s.Put(2);
	EXPECT_EQ(2, s.Get());
}

TEST(TStack, can_create_stack_without_parametres)
{
	ASSERT_NO_THROW(TStack());
}

TEST(TStack, topelem_error_for_empty_stack)
{
	TStack s(10);
	s.TopElem();
	EXPECT_EQ(DataEmpty, s.GetRetCode());
}

TEST(TStack, topelem_return_correct_element)
{
	TStack s(10);
	s.Put(7);
	s.Put(11);
	EXPECT_EQ(11, s.TopElem());
}

TEST(TStack, get_return_correct_element)
{
	TStack s(3);
	s.Put(5);
	s.Put(2);
	EXPECT_EQ(2, s.Get());
}

TEST(TStack, get_change_top_element)
{
	TStack s(10);
	s.Put(5);
	s.Put(2);
	s.Put(10);
	int t = s.Get();
	EXPECT_EQ(2, s.TopElem());
}

TEST(TStack, cant_get_element_in_empty_stack)
{
	TStack s(3);
	s.Get();
	EXPECT_EQ(DataEmpty, s.GetRetCode());
}

TEST(TStack, cant_put_element_in_full_stack)
{
	TStack s(3);
	s.Put(2);
	s.Put(2);
	s.Put(2);
	s.Put(2);
	EXPECT_EQ(DataFull, s.GetRetCode());
}

TEST(TFormula, can_create_formula)
{
	ASSERT_NO_THROW(TFormula f("(2+3)"));	
}

TEST(TFormula, check_true_brackets)
{
	char* s1 = "(())";
	int br1[4] = {0};
	TFormula f1(s1);
	EXPECT_EQ(0, f1.FormulaChecker(br1, 4));
}

TEST(TFormula, check_true_brackets_in_formula)
{
	char* s = "(2+3)/8*(4/(5-7))";
	TFormula f(s);
	int br[6] = {0};
	EXPECT_EQ(0, f.FormulaChecker(br, 6));
}

TEST(TFormula, check_wrong_brackets_in_formula)
{
	char* s = "(1+3)*9))-(7+6)/13";
	TFormula f(s);

	int br[7] = {0};

	EXPECT_EQ(2, f.FormulaChecker(br, 7));
}

TEST(TFormula, can_convert_formula_with_correct_brackets)
{
	char* s = "(1+3)*9/15 ";
	TFormula f(s);
	ASSERT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, cant_convert_formula_with_wrong_brackets)\
{
	char* s = "(1+3))*9-(7+6)/13";
	TFormula f(s);
	ASSERT_ANY_THROW(f.FormulaConverter());
}

TEST(TFormula, can_calculate_formula)
{
	char *s = "(2+3)/(3+7)";
	TFormula f(s);
	EXPECT_EQ(0.5, f.FormulaCalculator());
}

TEST(TFormula, add_integer)
{
	char *s = "10+12";
	TFormula f(s);
	EXPECT_DOUBLE_EQ(22.0, f.FormulaCalculator());
}

TEST(TFormula, sub_integer)
{
	char *s = "10-12";
	TFormula f(s);
	EXPECT_DOUBLE_EQ(-2, f.FormulaCalculator());
}

TEST(TFormula, multi_integer)
{
	char *s = "10*12";
	TFormula f(s);
	EXPECT_DOUBLE_EQ(120, f.FormulaCalculator());
}

TEST(TFormula, div_integer)
{
	char *s = "10/40";
	TFormula f(s);
	EXPECT_DOUBLE_EQ(0.25, f.FormulaCalculator());
}
