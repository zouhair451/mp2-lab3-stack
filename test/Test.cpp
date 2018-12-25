#include <../gtest/gtest.h>
#include <tstack.h>
#include <tformula.h>



TEST (TStack, can_create_stack) {
	ASSERT_NO_THROW(TStack a());
}

TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack(10));
}

TEST(TStack, can_print_stack)
{
	TStack st(2);
	st.Put(3);
	st.Put(4);
	ASSERT_NO_THROW(st.Print());
}

TEST(TStack, throws_when_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack(-4));
}

TEST(TStack, can_put_value)
{
	TStack st(2);
	ASSERT_NO_THROW(st.Put(3));
}

TEST(TStack, can_put_value_twice)
{
	TStack st(2);
	st.Put(10);
	ASSERT_NO_THROW(st.Put(10));
}

TEST(TStack, can_get_value)
{
	TStack st(2);
	st.Put(7);
	ASSERT_NO_THROW(st.Get());
}

TEST(TStack, can_correctly_get_value)
{
	TStack st(2);
	st.Put(7);
	EXPECT_EQ(7, st.Get());
}

TEST(TStack, can_get_top_elem)
{
	TStack st(2);
	st.Put(7);
	ASSERT_NO_THROW(st.TopElem());
}

TEST(TStack, can_correctly_get_top_elem)
{
	TStack st(2);
	st.Put(7);
	EXPECT_EQ(7, st.TopElem());
}

TEST(TStack, cant_get_elem_when_stack_is_empty)
{
	TStack st(2);
	ASSERT_ANY_THROW(st.Get());
}

TEST(TStack, cant_put_elem_when_stack_is_full)
{
	TStack st(2);
	st.Put(10);
	st.Put(10);
	ASSERT_ANY_THROW(st.Put(10));
}

TEST(TStack, stack_is_not_empty_after_put_operation) {
	TStack s(4);
	s.Put(5);
	ASSERT_NE(true, s.IsEmpty());
}

TEST(TStack, get_function_deletes_top_element) {
	TStack s(4);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	for (int i = 0; i < 3; ++i)
		s.Get();
	ASSERT_EQ(true, s.IsEmpty());
}

TEST(TStack, TopElem_function_doesnt_delete_top_element) {
	TStack s(4);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	for (int i = 0; i < 3; ++i)
		s.TopElem();
	ASSERT_NE(true, s.IsEmpty());
}

// 15 tests from TStack


TEST(TFormula, can_create_tformula_1) {
	ASSERT_NO_THROW(TFormula f("(1+2+3)"));
}

TEST(TFormula, can_create_tformula_2) {
	char c[] = "(1+2)*2";
	ASSERT_NO_THROW(TFormula f(c));
}

TEST(TFormula, formula_checker_can_build_brakets_table)
{
	TFormula f("5+3-))(4*3)+4/(((3-2)))*7((-4");
	int Brackets[25];
	ASSERT_NO_THROW(f.FormulaChecker(Brackets, 25));
}

TEST(TFormula, formula_checker_build_correct_table)
{
	TFormula f("(())())");
	int CorrectBrackets[] = { 2,3,1,4,5,6,0,7 };
	int Brackets[30];
	EXPECT_EQ(1,f.FormulaChecker(Brackets, 8));
}

TEST(TFormula, formula_checker_can_correctly_check_brackets) {
	TFormula f("(())()()");
	int CorrectBrackets[] = { 2,3,1,4,5,6,0,7,8 };
	int Brackets[30];
	EXPECT_EQ(0, f.FormulaChecker(Brackets, 8));
}

TEST(TFormula, formula_checker_can_correctly_check_brackets_1) {
	TFormula f("((1+2))(3*4)/(1)");
	int CorrectBrackets[] = { 2,3,1,4,5,6,0,7,8 };
	int Brackets[30];
	EXPECT_EQ(0, f.FormulaChecker(Brackets, 8));
}

TEST(TFormula, formula_checker_can_correctly_check_brackets_2)
{
	char formula[] = "(7+3)-5)+(1.4+82.3";
	TFormula F(formula);
	int br[6];
	int s = 6;

	EXPECT_EQ(2, F.FormulaChecker(br, s));
}

TEST(TFormula, cant_convert_formula_with_wrong_brackets)
{
	char formula[255] = "(9+2)-5)+(6.1+78.5";
	TFormula F(formula);

	ASSERT_ANY_THROW(F.FormulaConverter());
}

TEST(TFormula, can_convert_formula_with_correct_brackets)
{
	TFormula f("(1+2+3-4)");
	EXPECT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, can_convert_formula_with_correct_brackets_1)
{
	TFormula f("12+3-(4*(2+1))*14");
	EXPECT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, can_calculate_formula)
{
	TFormula f("12+3-(4*(2+1))*14");
	EXPECT_NO_THROW(f.FormulaCalculator());
}

TEST(TFormula, can_corectly_calculate_formula_1)
{
	TFormula f("2+2*2");
	EXPECT_EQ(6, f.FormulaCalculator());
}

TEST(TFormula, can_corectly_calculate_formula_2)
{
	TFormula f("(2+2)*2");
	EXPECT_EQ(8, f.FormulaCalculator());
}

TEST(TFormula, can_corectly_calculate_formula_3)
{
	TFormula f("(11+2)-(3+4*6.7)+5.3*4.4");
	EXPECT_EQ(6.52, f.FormulaCalculator());
}

TEST(TFormula, can_corectly_calculate_formula_4)
{
	TFormula f("(1+2)/(3+4*6.7)-5.3*4.4");
	double res = (1 + 2) / (3 + 4 * 6.7) - 5.3*4.4;
	EXPECT_DOUBLE_EQ(res, f.FormulaCalculator());
}

// 15 tests from TFormula