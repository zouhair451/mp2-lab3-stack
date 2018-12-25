#include "gtest.h"
#include "tstack.h"
#include "tformula.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack(10));
}

TEST(TStack, created_empty_stack_is_valid)
{
	TStack s;
	EXPECT_EQ(true, s.IsValid());
}

TEST(TStack, stack_with_negative_length_is_not_valid)
{
	TStack s(-1);
	EXPECT_EQ(false, s.IsValid());
}

TEST(TStack, stack_with_null_length_is_not_valid)
{
	TStack s(0);
	EXPECT_EQ(false, s.IsValid());
}

TEST(TStack, overflowed_stack_is_not_valid)
{
	TStack s(1);
	s.Put(1);
	s.Put(2);
	s.Put(3);

	EXPECT_EQ(false, s.IsValid());
}

TEST(TFormula, can_create_formula)
{
	ASSERT_NO_THROW(TFormula("1+1"));
}

TEST(TFormula, formula_with_one_number_is_number)
{
	TFormula f("(223)");
	EXPECT_EQ(223, f.FormulaCalculator());
}

TEST(TFormula, check_formula_with_correct_brackets)
{
	TFormula f("(2+(4*(25-2)+ 3)/(5-4)+(2-2))");
	int brs[10];
	int size = 10;
	EXPECT_EQ(0, f.FormulaChecker(brs, size));
}

TEST(TFormula, check_formula_with_one_brackets_error)
{
	TFormula f("((2+2)");
	int brs[3];
	int size = 3;
	EXPECT_EQ(1, f.FormulaChecker(brs, size));
}

TEST(TFormula, check_formula_with_two_brackets_errors)
{
	TFormula f("((");
	int brs[2];
	int size = 2;
	EXPECT_EQ(2, f.FormulaChecker(brs, size));
}

TEST(TFormula, check_formula_with_three_brackets_errors)
{
	TFormula f("())((");
	int brs[5];
	int size = 5;
	EXPECT_EQ(3, f.FormulaChecker(brs, size));
}

TEST(TFormula, can_convert_formula_with_correct_brackets)
{
	TFormula f("(5/2)*(2+3+3-4)");

	ASSERT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, cant_convert_formula_with_wrong_brackets)
{
	TFormula f("()5/2)*(2+3+3-4)");

	ASSERT_ANY_THROW(f.FormulaConverter());
}

TEST(TFormula, can_calc_formula_with_correct_brackets)
{
	TFormula f("(5/2)*(2+3+3-4)");

	ASSERT_NO_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_calc_formula_with_wrong_brackets)
{
	TFormula f("()5/2)*(2+3+3-4)");

	ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, calc_formula_with_correct_brackets)
{
	TFormula f("(5/2)*(2+3+3-4)");

	EXPECT_DOUBLE_EQ(((double)5 / 2)*(double)(2 + 3 + 3 - 4), f.FormulaCalculator());
}

TEST(TFormula, calc_double_formula_with_correct_brackets)
{
	TFormula f("2.3*(2.4/1.2)");

	EXPECT_DOUBLE_EQ(2.3 * (2.4 / 1.2), f.FormulaCalculator());
}

TEST(TFormula, calc_double_formula_without_brackets)
{
	TFormula f("2.3+2.4/1.2");

	EXPECT_DOUBLE_EQ(2.3 + 2.4 / 1.2, f.FormulaCalculator());
}

TEST(TFormula, calc_double_formula_with_many_brackets)
{
	TFormula f("(((2.3*(2.4/1.2)) + 1.3) * 23.57)");

	EXPECT_DOUBLE_EQ((((2.3*(2.4 / 1.2)) + 1.3) * 23.57), f.FormulaCalculator());
}

TEST(TFormula, calc_double_formula_with_big_accuracy)
{
	TFormula f("3.333333333333333333/2.34545");

	EXPECT_DOUBLE_EQ(3.333333333333333333 / 2.34545, f.FormulaCalculator());
}

TEST(TFormula, calc_int_formula)
{
	TFormula f("(238+29323)*23 - 240/12");

	EXPECT_EQ((238 + 29323) * 23 - 240 / 12, f.FormulaCalculator());
}