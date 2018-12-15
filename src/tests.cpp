
#include "gtest.h"
//#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tstack.h"
//#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab3-stack\include\tformula.h"
#include "stack.h"
#include "tformula.h"

TEST(TStack, can_create_stack_with_positive_size)
{
    ASSERT_NO_THROW(TStack(10));
}

TEST(TStack, throws_when_create_stack_with_negative_size)
{
    ASSERT_ANY_THROW(TStack(-4));
}

TEST(TStack, can_put_a_value)
{
    TStack st(2);
    ASSERT_NO_THROW(st.Put(3));
}

TEST(TStack, can_put_a_value_max_times)
{
    TStack st(2);
    st.Put(10);
    ASSERT_NO_THROW(st.Put(10));
}

TEST(TStack, throws_when_stack_is_full)
{
    TStack st(2);
    st.Put(10);
    st.Put(10);
    ASSERT_ANY_THROW(st.Put(10));
}

TEST(TStack, can_get_a_value)
{
    TStack st(2);
    st.Put(5);
    ASSERT_NO_THROW(st.Get());
}

TEST(TStack, can_correctly_get_a_value)
{
    TStack st(2);
    st.Put(5);
    EXPECT_EQ(5, st.Get());
}

TEST(TStack, throws_when_stack_is_empty)
{
    TStack st(2);
    ASSERT_ANY_THROW(st.Get());
}

TEST(TStack, can_get_top_elem)
{
    TStack st(2);
    st.Put(5);
    ASSERT_NO_THROW(st.TopElem());
}

TEST(TStack, can_correctly_get_top_elem)
{
    TStack st(2);
    st.Put(5);
    EXPECT_EQ(5, st.TopElem());
}

TEST(TStack, is_valid)
{
    TStack st(2);
    EXPECT_EQ(1, st.IsValid());
}

TEST(TStack, can_print_stack)
{
    TStack st(2);
    st.Put(3);
    st.Put(4);
    ASSERT_NO_THROW(st.Print());
}
// in total 12 tests of TStack

TEST(TFormula, can_create_formula)
{
    ASSERT_NO_THROW(TFormula f = "1+2");
}

TEST(TFormula, throws_when_creating_too_large_formula)
{
    ASSERT_ANY_THROW(TFormula f = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
}

TEST(TFormula, correctness_of_formula_checker_1)
{
    TFormula f = "1+2+3";
    int Brackets[10], size = 10, res = -1;
	res = f.FormulaChecker(Brackets, size);
    EXPECT_EQ(0, res);
}

TEST(TFormula, correctness_of_formula_checker_2)
{
    TFormula f = "(a+b1)/2+6.5)*(4.8+sin(x)";
    int Brackets[10], size = 10, res = -1;
	res = f.FormulaChecker(Brackets, size);
    EXPECT_EQ(2, res);
}

TEST(TFormula, correctness_of_formula_checker_3)
{
    TFormula f = "(12+12/(2+4*1)-5*4";
    int Brackets[10], size = 10, res = -1;
	res = f.FormulaChecker(Brackets, size);
    EXPECT_EQ(1, res);
}

TEST(TFormula, correctness_of_formula_checker_4)
{
    TFormula f = "(12+12)/(2+4*1)-5*4";
    int Brackets[10], size = 10, res = -1;
	res = f.FormulaChecker(Brackets, size);
    EXPECT_EQ(0, res);
}

TEST(TFormula, correctness_of_formula_checker_5)
{
    TFormula f = "()())";
    int Brackets[10], size = 10, res = -1;
	res = f.FormulaChecker(Brackets, size);
    EXPECT_EQ(1, res);
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_1)
{
    TFormula f = "(12+12/(2+4*1)-5*4";
    ASSERT_ANY_THROW(f.FormulaConverter());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_2)
{
    TFormula f = "(12+12)/(2+4*1)-5*4";
    f.FormulaConverter();
	ASSERT_FLOAT_EQ(-16, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_3)
{
	TFormula f = "4.5 * 3.1";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(13.95, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_4)
{
	TFormula f = "1.2+3.6*20-1";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(72.2, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_5)
{
	TFormula f = "1.2 + 3.6 * 20 - 1 "; // with spaces
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(72.2, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_6)
{
	TFormula f = "(1.2+3.6)*(20-1)";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(91.2, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_7)
{
	TFormula f = "1.2+3.6*(20-1)";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(69.6, f.FormulaCalculator());
}
/*
TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_8)
{
	TFormula f = "10";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(10, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_9)
{
	TFormula f = "(((1000)))";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(1000, f.FormulaCalculator());
}

TEST(TFormula, correctness_of_FormulaConverter_and_FormulaCalculator_10)
{
	TFormula f = "-1*(2+3)";
	f.FormulaConverter();
	ASSERT_FLOAT_EQ(-5, f.FormulaCalculator());
}
*/

TEST(TFormula, priority_test)
{
	TFormula f = "(";
	EXPECT_EQ(0, f.Priority('('));
}

TEST(TFormula, is_operation_test)
{
	TFormula f = "1";
	EXPECT_EQ(false, f.isOperation('&'));
}
// 16 tests of TFormula. In total 28 tests.
