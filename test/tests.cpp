#include "tformula.h"
#include "tstack.h"
#include "gtest.h"

TEST(TStack, can_create_Stack)
{
	ASSERT_NO_THROW(TStack st(10));
}

TEST(TStack, cannot_create_Stack_with_negativ_length)
{
	ASSERT_ANY_THROW(TStack st(-10));
}

TEST(TStack, can_put_elem)
{
	TStack st(10);
	ASSERT_NO_THROW(st.Put(3));
}

TEST(TStack, can_get_elem)
{
	TStack st(10);
	st.Put(1);
	ASSERT_NO_THROW(st.Get());
}

TEST(TStack, can_get_elem_is_correct)
{
	TStack st(10);
	st.Put(1);
	EXPECT_EQ(1, st.Get());
}

TEST(TStack, retcode_when_stack_empty)
{
	TStack St(10);
	St.Get();
	EXPECT_EQ(DataEmpty, St.GetRetCode());
}

TEST(TStack, can_change_retcode_when_put_in_full_tstack)
{
	TStack St(2);
	St.Put(1);
	St.Put(2);
	St.Put(3);
	ASSERT_EQ(DataFull, St.GetRetCode());
}

TEST(TStack, top_elememt_after_put_element)
{
	TStack St(10);
	St.Put(1);
	St.Put(5);
	ASSERT_EQ(5, St.TopElem());
}

TEST(TStack, top_element_cant_change_when_put_element_in_full_stack)
{
	TStack St(2);
	St.Put(1);
	St.Put(2);
	St.Put(3);
	ASSERT_EQ(2, St.TopElem());
}

TEST(TFormula, can_create_formula)
{
	ASSERT_NO_THROW(TFormula f("(1+2)"));
}

TEST(TFormula, can_check_formula)
{
	TFormula f("(1+2)*((3-4)/(5+6))+7");
	int br[255];
	ASSERT_NO_THROW(f.FormulaChecker(br, 255));
}

TEST(TFormula, check_wrong_brackets)
{
	TFormula f("(1*2)+((3-4");
	int br[4] = { 0 };
	EXPECT_EQ(1, f.FormulaChecker(br, 4));
}

TEST(TFormula, check_right_brackets)
{
	TFormula f("1*2+3-4");
	int br[4] = { 0 };
	EXPECT_EQ(0, f.FormulaChecker(br, 4));
}

TEST(TFormula, can_calculate_formula)
{
	TFormula f("(1*2)+(3-4)");
	EXPECT_EQ(1, f.FormulaCalculator());
}

TEST(TFormula, add_integer)
{
	TFormula f("23+32");
	EXPECT_DOUBLE_EQ(55.0, f.FormulaCalculator());
}

TEST(TFormula, sub_integer)
{
	TFormula f("23-32");
	EXPECT_DOUBLE_EQ(-9, f.FormulaCalculator());
}

TEST(TFormula, multi_integer)
{
	TFormula f("23*32");
	EXPECT_DOUBLE_EQ(736, f.FormulaCalculator());
}

TEST(TFormula, div_integer)
{
	TFormula f("32/64");
	EXPECT_DOUBLE_EQ(0.5, f.FormulaCalculator());
}