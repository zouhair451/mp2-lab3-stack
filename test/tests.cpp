#include "gtest.h"
#include "tstack.h"
#include "tformula.h"
#include <iostream>
using namespace std;


TEST(TStack, can_create_stack_with_positive_size) {
	 ASSERT_NO_THROW(TStack st(5));
}

TEST(TStack, cant_create_stack_with_negative_size) {
	 ASSERT_ANY_THROW(TStack st(-2));
}

TEST(TStack, can_put_new_value_else_stack_empty) {
	TStack st(2);
	ASSERT_NO_THROW(st.Put(5));
}

TEST(TStack, can_put_new_value) {
	TStack st(4);
	st.Put(3);
	st.Put(5);
	ASSERT_EQ(5,st.TopElem());
}

TEST(TStack, cant_put_new_value_else_stack_full) {
	TStack st(2);
	st.Put(3);
	st.Put(5);
	st.Put(5);
	ASSERT_EQ(DataFull, st.IsValid());
}

TEST(TStack, cant_put_new_value_else_stack_null) {
	TStack st(0);
	st.Put(3);
	ASSERT_EQ(DataNoMem, st.IsValid());
}

TEST(TStack, can_get_value_else_stack_no_empty) {
	TStack st(2);
	st.Put(3);
	ASSERT_EQ(3,st.Get());
}

TEST(TStack, cant_get_value_else_stack_empty) {
	TStack st(2);
	st.Get();
	ASSERT_EQ(DataEmpty, st.IsValid());
}

TEST(TStack, cant_get_value_else_stack_null) {
	TStack st(0);
	st.Get();
	ASSERT_EQ(DataNoMem, st.IsValid());
}

TEST(TStack, cant_check_top_element_else_stack_empty) {
	TStack st(2);
	ASSERT_ANY_THROW(st.TopElem());
}

TEST(TStack, cant_check_top_element_else_stack_null) {
	TStack st(0);
	ASSERT_ANY_THROW(st.TopElem());
}

TEST(TFormula, can_convert_formula_with_known_symbol) {
    TFormula f("1+4=");
    ASSERT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, cant_convert_formula_with_unknown_symbol) {
    TFormula f("1+j4=");
    ASSERT_ANY_THROW(f.FormulaConverter());
}


TEST(TFormula, can_check_brackets_one) {
    TFormula f("(1+5)=");
	int  str[255];
	ASSERT_EQ(1, f.FormulaChecker(str,255));
}


TEST(TFormula, can_check_brackets_two) {
    TFormula f("(1+5))=");
	int  str[255];
	ASSERT_EQ(0, f.FormulaChecker(str,255));
}

TEST(TFormula, can_check_brackets_three) {
    TFormula f("((1+5)=");
	int  str[255];
	ASSERT_EQ(0, f.FormulaChecker(str,255));
}

TEST(TFormula, cant_calculate_formula_with_misplaced_brackets) {
	TFormula f("(3*6)))=");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, can_check_brackets_four) {
    TFormula f("(2+7)*((((-3))))-56*(3-8)=");
	int  str[255];
	ASSERT_EQ(1, f.FormulaChecker(str,255));
}

TEST(TFormula, can_subtract_two_numbers) {
    TFormula f("7-1=");
    ASSERT_EQ(6, f.FormulaCalculator());
}

TEST(TFormula, can_multiply_two_numbers) {
    TFormula f("3*6=");
    ASSERT_EQ(18, f.FormulaCalculator());
}

TEST(TFormula, can_split_two_numbers) {
    TFormula f("4/2=");
    ASSERT_EQ(2, f.FormulaCalculator());
}

TEST(TFormula, check_first_formula) {
    TFormula f("4/2+5*3-2=");
    ASSERT_EQ(15, f.FormulaCalculator());
}

TEST(TFormula, check_second_formula) {
    TFormula f("23-8*6-6/2=");
    ASSERT_EQ(-28, f.FormulaCalculator());
}

TEST(TFormula, check_third_formula) {
    TFormula f("1-7*3-2+3+1=");
    ASSERT_EQ(-18, f.FormulaCalculator());
}

TEST(TFormula, check_first_formula_with_brackets) {
    TFormula f("4/2+5*(3-2)=");
    ASSERT_EQ(7, f.FormulaCalculator());
}

TEST(TFormula, check_second_formula_with_brackets) {
    TFormula f("23-8*(6-1)/2=");
    ASSERT_EQ(3, f.FormulaCalculator());
}

TEST(TFormula, check_third_formula_with_brackets) {
    TFormula f("6*8-(6-2)/2=");
    ASSERT_EQ(46, f.FormulaCalculator());
}

TEST(TFormula, check_double_result_one) {
    TFormula f("23/5+5/3*(8-2)=");
	const double result = 23./5.+5./3.*(8.-2.);
    ASSERT_EQ(result, f.FormulaCalculator());
}

TEST(TFormula, check_double_result_two) {
    TFormula f("10/(1+4+5+6)*(1-2)=");
	const double result = 10./(1.+4.+5.+6.)*(1.-2.);
    ASSERT_EQ(result, f.FormulaCalculator());
}

TEST(TFormula, check_double_result_three) {
    TFormula f("5/(6-2)*2.5=");
	const double result = 5./(6.-2.)*2.5;
    ASSERT_EQ(result, f.FormulaCalculator());
}




