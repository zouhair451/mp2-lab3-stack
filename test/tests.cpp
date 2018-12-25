#include "tformula.h"

#include "gtest.h"

TEST(TStack, cant_create_stack_with_negative_size)
{
	TStack stack(-5);

	EXPECT_EQ(stack.GetRetCode(), DataErr);
}

TEST(TStack, can_create_stack_with_positive_size)
{
	TStack stack(5);

	EXPECT_EQ(stack.GetRetCode(), DataOK);
}

TEST(TStack, can_create_stack_with_zero_size)
{
	TStack stack(0);

	EXPECT_EQ(stack.GetRetCode(), DataOK);
}

TEST(TStack, can_put_element_in_not_full_stack)
{
	TStack stack(5);
	stack.Put(0);

	EXPECT_EQ(stack.GetRetCode(), DataOK);
	EXPECT_EQ(stack.TopElem(), 0);

	stack.Put(1);

	EXPECT_EQ(stack.GetRetCode(), DataOK);
	EXPECT_EQ(stack.TopElem(), 1);
}

TEST(TStack, cant_put_element_in_full_stack)
{
	TStack stack(5);
	stack.Put(0);
	stack.Put(1);
	stack.Put(2);
	stack.Put(3);
	stack.Put(4);
	stack.Put(5);

	EXPECT_EQ(stack.GetRetCode(), DataFull);
}

TEST(TStack, cant_put_element_in_zero_stack)
{
	TStack stack(0);
	stack.Put(0);

	EXPECT_EQ(stack.GetRetCode(), DataNoMem);
}

TEST(TStack, cant_get_element_from_empty_stack)
{
	TStack stack(5);
	stack.Get();

	EXPECT_EQ(stack.GetRetCode(), DataEmpty);
}

TEST(TStack, cant_get_element_from_zero_stack)
{
	TStack stack(0);
	stack.Get();

	EXPECT_EQ(stack.GetRetCode(), DataNoMem);
}

TEST(TStack, can_get_element_from_not_empty_stack)
{
	TStack stack(5);
	stack.Put(0);
	stack.Put(1);
	stack.Put(2);

	EXPECT_EQ(stack.Get(), 2);
	EXPECT_EQ(stack.GetRetCode(), DataOK);
}

TEST(TStack, cant_check_top_element_from_empty_stack)
{
	TStack stack(5);
	stack.TopElem();

	EXPECT_EQ(stack.GetRetCode(), DataEmpty);
}

TEST(TStack, cant_check_top_element_from_zero_stack)
{
	TStack stack(0);
	stack.TopElem();

	EXPECT_EQ(stack.GetRetCode(), DataNoMem);
}

TEST(TStack, can_check_top_element_from_not_empty_stack)
{
	TStack stack(5);
	stack.Put(0);
	stack.Put(1);
	stack.Put(2);

	EXPECT_EQ(stack.TopElem(), 2);
	EXPECT_EQ(stack.GetRetCode(), DataOK);
}

TEST(TFormula, cant_create_formula_with_form_len_more_maxlen)
{
	char *form = new char[260];
	form[259] = '\0';

	EXPECT_ANY_THROW(TFormula f(form));

	delete[] form;
}

TEST(TFormula, can_create_formula_with_form_len_less_or_eq_maxlen)
{
	EXPECT_NO_THROW(TFormula("(9+5.4(37.6-7))+6/2"));

	char *form = new char[256];
	form[255] = '\0';

	EXPECT_NO_THROW(TFormula f(form));

	delete[] form;
}

TEST(TFormula, checker_returns_correct_number_of_errs)
{
	int Brackets[255];
	TFormula f1("(9+5.4(37.6-7))+6/2)"); // 1
	TFormula f2("(9+5.4(37.6-7))+6/(2"); // 1
	TFormula f3("(9+5.4(37.6-7))+6/2"); // 0
	TFormula f4("))((9+5.4(37.6-7))+6/2"); // 3

	EXPECT_EQ(f1.FormulaChecker(Brackets, 255), 1);
	EXPECT_EQ(f2.FormulaChecker(Brackets, 255), 1);
	EXPECT_EQ(f3.FormulaChecker(Brackets, 255), 0);
	EXPECT_EQ(f4.FormulaChecker(Brackets, 255), 3);
}

TEST(TFormula, checker_returns_correct_arr_of_brackets)
{
	int Brackets[255];
	TFormula f("(9+3-4.5+4.5+1)/(4+(2-4))");
	f.FormulaChecker(Brackets, 255);

	EXPECT_EQ(Brackets[0], 1);
	EXPECT_EQ(Brackets[1], 2);
	EXPECT_EQ(Brackets[2], 4);
	EXPECT_EQ(Brackets[3], 5);
	EXPECT_EQ(Brackets[4], 3);
	EXPECT_EQ(Brackets[5], 6);
}

TEST(TFormula, throw_when_form_contains_incorrect_chars)
{
	int Brackets[255];
	TFormula f("Hello world!");

	EXPECT_ANY_THROW(f.FormulaChecker(Brackets, 255));
}

TEST(TFormula, cant_convert_invalid_form)
{
	TFormula f("6/)(3+2)");

	EXPECT_ANY_THROW(f.FormulaConverter());
}

TEST(TFormula, can_convert_correct_form)
{
	TFormula f1("6/3+(2.5-1.5+(4-3))-0.5+0.5");
	TFormula f2("(5-30.5)+0.5");
	TFormula f3("10-5-3+1/1");

	EXPECT_NO_THROW(f1.FormulaConverter());
	EXPECT_NO_THROW(f2.FormulaConverter());
	EXPECT_NO_THROW(f3.FormulaConverter());
}

TEST(TFormula, can_correctly_calculate)
{
	TFormula f1("6/3+(2.5-1.5+(4-3))-0.5+0.5");
	TFormula f2("(5-30.5)+0.5");
	TFormula f3("10-5-3+1/1");

	f1.FormulaConverter();
	f2.FormulaConverter();
	f3.FormulaConverter();

	EXPECT_EQ(f1.FormulaCalculator(), 4.0);
	EXPECT_EQ(f2.FormulaCalculator(), -25.0);
	EXPECT_EQ(f3.FormulaCalculator(), 3.0);
}

TEST(TFormula, can_calculate_form_without_operators)
{
	TFormula f("12345.6");

	EXPECT_NO_THROW(f.FormulaConverter());
	EXPECT_EQ(f.FormulaCalculator(), 12345.6);
}

TEST(TFormula, can_calculate_empty_form)
{
	TFormula f("");

	EXPECT_NO_THROW(f.FormulaConverter());
	EXPECT_EQ(f.FormulaCalculator(), 0.0);
}

TEST(TFormula, testing_all_operators)
{
	TFormula f("1+6/3-3*3");

	f.FormulaConverter();
	EXPECT_EQ(f.FormulaCalculator(), -6.0);
}