#include "tformula.h"
#include "gtest.h"

TEST(TFormula, can_check_formula)
{
	TFormula f("(1*2)+((3-4*5)/(6-7))+(8*9)");
	int Br[255];
	ASSERT_NO_THROW(f.FormulaChecker(Br, 255));
}

TEST(TFormula, formula_checker_is_correct)
{
	TFormula f("(1*2)+((3-4");
	int Br1[] = {1,2,0,0};
	int Br2[10];
	f.FormulaChecker(Br2, 30);
	for (int i = 0; i<4; i++)
		ASSERT_EQ(Br1[i], Br2[i]);
}

TEST(TFormula, can_check_formula_without_brackets)
{
	TFormula f("1 + 2");
	int Br[10];	
	ASSERT_NO_THROW(f.FormulaChecker(Br, 30););

}

TEST(TFormula, can_convert_empty_formul)
{
	TFormula f("");
	ASSERT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, cant_convert_formul_with_wrong_symbols)
{
	TFormula f("dgsdsh");
	ASSERT_ANY_THROW(f.FormulaConverter());
}


TEST(TFormula, can_calculate_sum)
{
	TFormula f("2+1");
	ASSERT_DOUBLE_EQ(3, f.FormulaCalculator());
}


TEST(TFormula, can_calculate_difference)
{
	TFormula f("10-3");
	ASSERT_DOUBLE_EQ(7, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_multipling)
{
	TFormula f("3*2");
	ASSERT_DOUBLE_EQ(6, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_divide)
{
	TFormula f("50/5");
	ASSERT_DOUBLE_EQ(10, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_sum_with_brackets)
{
	TFormula f("(1+2)+(3+4)");
	ASSERT_DOUBLE_EQ(10, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_diff_with_brackets)
{
	TFormula f("(5-4)-(3-2)");
	ASSERT_DOUBLE_EQ(0, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_multiplying_with_brackets)
{
	TFormula f("(2*3)*(1*5)");
	ASSERT_DOUBLE_EQ(30, f.FormulaCalculator());
}

TEST(TFormula, can_divide_with_brackets)
{
	TFormula f("(10/2)/(25/5)");
	EXPECT_DOUBLE_EQ(1, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_multiple_operators)
{
	TFormula f("10+5*3-5/5");
	EXPECT_DOUBLE_EQ(24, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_multiple_different_with_brackets)
{
	TFormula f("(10+5)*3-5/5");
	EXPECT_DOUBLE_EQ(44, f.FormulaCalculator());
}


TEST(TFormula, cant_calculate_formula_with_wrong_symbols)
{
	TFormula f("fghdfigh");
	ASSERT_ANY_THROW(f.FormulaCalculator());
}