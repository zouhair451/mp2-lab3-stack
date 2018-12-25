#include "tstack.h"
#include "tformula.h"

#include "gtest.h"

TEST(TStack, can_create_stack)
{
	TStack st(5);

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, cant_put_if_no_mem)
{
	TStack st(0);
	st.Put(5);

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_put_if_stack_full)
{
	TStack st(1);
	st.Put(5);
	st.Put(5);

	EXPECT_EQ(DataFull, st.GetRetCode());
}

TEST(TStack, can_put_if_ok_1)
{
	TStack st(1);
	st.Put(5);

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_put_if_ok_2)
{
	TStack st(1);
	st.Put(5);

	EXPECT_EQ(5, st.TopElem());
}

TEST(TStack, cant_get_if_no_mem)
{
	TStack st(0);
	st.Get();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_get_if_stack_empty)
{
	TStack st(1);
	st.Get();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_get_if_ok_1)
{
	TStack st(1);
	st.Put(5);
	st.Get();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_get_if_ok_2)
{
	TStack st(1);
	st.Put(5);
	int k = st.Get();

	EXPECT_EQ(5, k);
}

TEST(TStack, cant_top_elem_if_no_mem)
{
	TStack st(0);
	st.TopElem();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_top_elem_if_stack_empty)
{
	TStack st(1);
	st.TopElem();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_top_elem_if_ok_1)
{
	TStack st(1);
	st.Put(5);
	st.TopElem();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_top_elem_if_ok_2)
{
	TStack st(1);
	st.Put(5);
	int k = st.TopElem();

	EXPECT_EQ(5, k);
}

TEST(TFormula, can_create_formula)
{
	char formula[255] = "2+3";
	ASSERT_NO_THROW(TFormula F(formula));
}

TEST(TFormula, check_formula_with_correct_brackets_only)
{
	char formula[255] = "(()())";
	TFormula F(formula);
	int br[6];
	int s = 6;

	EXPECT_EQ(0, F.FormulaChecker(br, s));
}

TEST(TFormula, check_formula_with_wrong_brackets_only)
{
	char formula[255] = "))(()";
	TFormula F(formula);
	int br[5];
	int s = 5;

	EXPECT_EQ(3, F.FormulaChecker(br, s));
}

TEST(TFormula, check_formula_with_correct_brackets)
{
	char formula[255] = "(2+3)*(5.2-3.1)";
	TFormula F(formula);
	int br[4];
	int s = 4;

	EXPECT_EQ(0, F.FormulaChecker(br, s));
}

TEST(TFormula, check_formula_with_wrong_brackets)
{
	char formula[255] = "(9+2)-5)+(6.1+78.5";
	TFormula F(formula);
	int br[4];
	int s = 4;

	EXPECT_EQ(2, F.FormulaChecker(br, s));
}

TEST(TFormula, can_convert_formula_with_correct_brackets)
{
	char formula[255] = "(2+3)*(5.2-3.1)";
	TFormula F(formula);

	ASSERT_NO_THROW(F.FormulaConverter());
}

TEST(TFormula, cant_convert_formula_with_wrong_brackets)
{
	char formula[255] = "(9+2)-5)+(6.1+78.5";
	TFormula F(formula);

	ASSERT_ANY_THROW(F.FormulaConverter());	
}

TEST(TFormula, can_calculate_if_no_postfixform)
{
	char formula[255] = "(2+3)*(5.2-3.1)";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(10.5, F.FormulaCalculator());
}

TEST(TFormula, calculate_integer_without_brackets)
{
	char formula[255] = "2+3*4+5";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(19.0, F.FormulaCalculator());
}

TEST(TFormula, calculate_integer_with_brackets)
{
	char formula[255] = "(2+3)*(4+5)";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(45.0, F.FormulaCalculator());
}

TEST(TFormula, calculate_double_without_brackets)
{
	char formula[255] = "2.1+3*4+5.2";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(19.3, F.FormulaCalculator());
}

TEST(TFormula, calculate_double_with_brackets)
{
	char formula[255] = "(2.1+3)*(4+5.2)";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(46.92, F.FormulaCalculator());
}

TEST(TFormula, add_integer)
{
	char formula[255] = "15+37";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(52.0, F.FormulaCalculator());
}

TEST(TFormula, sub_integer)
{
	char formula[255] = "15-37";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(-22.0, F.FormulaCalculator());
}

TEST(TFormula, multi_integer)
{
	char formula[255] = "15*37";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(555.0, F.FormulaCalculator());
}

TEST(TFormula, div_integer)
{
	char formula[255] = "15/37";
	TFormula F(formula);

	EXPECT_NEAR(0.405405, F.FormulaCalculator(), 0.0000005);
}

TEST(TFormula, add_double)
{
	char formula[255] = "1.5+3.7";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(5.2, F.FormulaCalculator());
}

TEST(TFormula, sub_double)
{
	char formula[255] = "1.5-3.7";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(-2.2, F.FormulaCalculator());
}

TEST(TFormula, multi_double)
{
	char formula[255] = "1.5*3.7";
	TFormula F(formula);

	EXPECT_DOUBLE_EQ(5.55, F.FormulaCalculator());
}

TEST(TFormula, div_double)
{
	char formula[255] = "1.5/3.7";
	TFormula F(formula);

	EXPECT_NEAR(0.405405, F.FormulaCalculator(), 0.0000005);
}