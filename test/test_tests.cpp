#include "gtest.h"
#include "tformula.h"

TEST (TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack(5));
}

TEST (TStack, cant_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack(-1));
}

TEST (TStack, can_put_and_get_element)
{
	TStack temp(3);
	temp.Put(4);

	ASSERT_NO_THROW(temp.Get());
}

TEST (TStack, stack_getter_returns_putted_element)
{
	TStack temp(3);
	temp.Put(4);

	EXPECT_EQ(temp.Get(), 4);
}

TEST (TStack, throws_when_get_elment_from_empty_stack)
{
	TStack temp(4);

	ASSERT_ANY_THROW(temp.Get());
}

TEST (TStack, throws_when_get_element_form_stack_with_no_memory)
{
	TStack temp(0);

	ASSERT_ANY_THROW(temp.Get());
}

TEST (TStack, can_detect_if_stack_is_empty)
{
	TStack temp(3);

	EXPECT_EQ(1, temp.IsEmpty());
}

TEST (TStack, can_detect_if_stack_is_not_empty)
{
	TStack temp(3);
	temp.Put(11);

	EXPECT_EQ(0, temp.IsEmpty());
}

TEST (TStack, can_detect_if_stack_is_not_full)
{
	TStack temp(3);
	temp.Put(11);

	EXPECT_EQ(0, temp.IsFull());
}
TEST (TStack, can_detect_if_stack_is_full)
{
	TStack temp(1);
	temp.Put(8);

	EXPECT_EQ(1, temp.IsFull());
}
TEST (TStack, get_throws_when_stack_is_empty)
{
	TStack temp(3);

	ASSERT_ANY_THROW(temp.Get());
}
TEST (TStack, put_throws_when_stack_is_full)
{
	TStack temp(2);
	temp.Put(10);
	temp.Put(12);

	ASSERT_ANY_THROW(temp.Put(1));
}

TEST (TStack, can_print_stack)
{
	TStack temp(3);
	for (int i = 0; i < 3; i++)
	    temp.Put(i);

	ASSERT_NO_THROW(temp.Print());
}
TEST (TFormula, proper_formula_passes_checking)
{
	char* formula = (char*)"((3+4)*6-3*(4-6))-5";
	TFormula formula_check(formula);

	EXPECT_EQ(0, formula_check.FormulaChecker());
}
TEST (TFormula, corrupted_formula_fails_checking)
{
	char* formula = (char*)"(3+4)*6-3*(4-6))-5";
	TFormula formula_check(formula);

	EXPECT_EQ(1, formula_check.FormulaChecker());
}
TEST (TFormula, can_calculate_proper_formula)
{
	char* formula = (char*)"((3+4)*6-3*(4-6))-5";
	TFormula formula_calc(formula);

	EXPECT_EQ(43, formula_calc.FormulaCalculator());
}
TEST (TFormula, throws_when_calculating_wrong_formula)
{
	char* formula = (char*)"(3+4)*6-3*(4-6))-5";
	TFormula formula_calc(formula);

	ASSERT_ANY_THROW(formula_calc.FormulaCalculator());
}
TEST (TFormula, throw_when_create_empty_formula)
{
	ASSERT_ANY_THROW(TFormula empty_formula(""));
}