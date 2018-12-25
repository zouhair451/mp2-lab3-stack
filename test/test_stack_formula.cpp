#include "tformula.h"

#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_size)
{
	TStack_d s(5);
	EXPECT_EQ(DataOK, s.GetRetCode());
}

TEST(TStack, cant_create_stack_with_negative_size)
{
	TStack_d s(-5);
	EXPECT_EQ(DataErr, s.GetRetCode());
}

TEST(TStack, created_stack_is_empty)
{
	TStack_d s(5);
	
	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, can_set_and_get_element)
{
	TStack_d s(3);
	s.Put(9);
	
	EXPECT_EQ(9, s.Get());
}

TEST(TStack, replenished_stack_is_not_empty)
{
	TStack_d s(5);
	s.Put(7);
	
	EXPECT_EQ(false, s.IsEmpty());
}

TEST(TStack, stack_after_get_is_not_full)
{
	TStack_d s(3);
	s.Put(2); s.Put(3); s.Put(4);
	s.Get();
	
	EXPECT_EQ(false, s.IsFull());
}

TEST(TStack, stack_return_last_element)
{
	TStack_d s(3);
	s.Put(4); s.Put(5);
	
	EXPECT_EQ(5, s.Get());
}

TEST(TStack, cant_set_element_when_stack_is_full)
{
	TStack_d s(3);
	s.Put(2); s.Put(3); s.Put(4);
	s.Put(5);
	
	EXPECT_EQ(DataNoMem, s.GetRetCode());
}

TEST(TStack, cant_get_element_when_stack_is_empty)
{
	TStack_d s(3);
	s.Get();
	EXPECT_EQ(DataEmpty, s.GetRetCode());
}

TEST(TStack, stack_is_valid)
{
	TStack_d s(5);
	s.Put(2); s.Put(3); s.Put(4);
	
	EXPECT_EQ(0, s.IsValid());
}

TEST(TFormula, can_create_formula)
{
	const char* s = "(1+2)";
	TFormula f(s);

	EXPECT_EQ(0, strcmp(s, f.GetFormula()));
}

TEST(TFormula, can_check_formula_1)
{
	const char* s = "(1+2)/(3";
	TFormula f(s);
	
	EXPECT_EQ(-1, f.FormulaChecker());
}

TEST(TFormula, can_check_formula_2)
{
	const char* s = "(1+2)/3";
	TFormula f(s);

	EXPECT_EQ(0, f.FormulaChecker());
}

TEST(TFormula, cant_calculate_wrong_formula_1)
{
	const char* s = "(((1+23)*1-22)+5)*2-(7";
	TFormula f(s);
	
	ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_wrong_formula_2)
{
	const char* s = "1++1";
	TFormula f(s);
	
	ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_division_by_zero)
{
	const char* s = "1+8/(3-3)";
	TFormula f(s);
	
	ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, can_calculate_1)
{
	const char* s = "1+2";
	TFormula f(s);

	EXPECT_EQ(3, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_2)
{
	const char* s = "1+2*(3-2)-4";
	TFormula f(s);
	
	EXPECT_EQ(-1, f.FormulaCalculator()); 
}

TEST(TFormula, can_calculate_3)
{
	const char* s = "(((1+23)*1-22)+5)*2-7";
	TFormula f(s);
	
	EXPECT_EQ(7, f.FormulaCalculator()); 
}

TEST(TFormula, can_calculate_4)
{
	const char* s = "(1+2)/(3+4*6.7)-5.3*4.4";
	TFormula f(s);
	
	EXPECT_EQ(-23, (int)f.FormulaCalculator()); 
}

TEST(TFormula, formula_without_operators_is_true_1)
{
	const char* s = "372";
	TFormula f(s);

	EXPECT_EQ(372, f.FormulaCalculator());
}

TEST(TFormula, formula_without_operators_is_true_2)
{
	const char* s = "(372)";
	TFormula f(s);

	EXPECT_EQ(372, f.FormulaCalculator());
}

TEST(TFormula, formula_without_operands_is_false)
{
	const char* s = "(())()";
	TFormula f(s);

	ASSERT_ANY_THROW(f.FormulaCalculator());
}