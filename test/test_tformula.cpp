#include <gtest.h>
#include "tformula.h"

TEST(TFormula, checking_brackets_succsess)
{
	char check[21] = "9/((2+4)-1*(3+5)-5)";
	int brackets[255];

	TFormula form(check);

	EXPECT_EQ(0, form.FormulaChecker(brackets, 255));
}

TEST(TFormula, checking_brackets_failure)
{
	char check[21] = "9/(2+4)-1*(3+5)-5)";
	int brackets[255];

	TFormula form(check);

	EXPECT_EQ(1, form.FormulaChecker(brackets, 255));
}

TEST(TFormula, can_convert_to_postfix_form)
{
	char check[21] = "9/((2+4)-1*(3+5)-5)";
	int brackets[255];

	TFormula form(check);

	EXPECT_EQ(0, form.FormulaConverter());
}

TEST(TFormula, can_calculate)
{
	char check[21] = "5+((2+4)-2*(3-5)*5)";
	int brackets[255];

	TFormula form(check);
	form.FormulaConverter();

	EXPECT_EQ(31, form.FormulaCalculator());
}