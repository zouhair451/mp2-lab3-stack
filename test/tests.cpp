#include "tformula.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
    TStack st(-1);
    EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, can_put_element_in_stack)
{
    TStack st(2);
    ASSERT_NO_THROW(st.Put(3));
    EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, cant_put_element_in_full_stack)
{
    TStack st(3);
    st.Put(1);
    st.Put(2);
    st.Put(3);
    st.Put(4);
    EXPECT_EQ(DataFull, st.GetRetCode());
}

TEST(TStack, top_elem_is_changing_after_putting_new_elem)
{
    TStack st(3);
    st.Put(1);
    st.Put(2);
    EXPECT_EQ(2, st.TopElem());
}

TEST(TStack, can_get_element_from_stack)
{
    TStack st(3);
    st.Put(1);
    ASSERT_NO_THROW(st.Get());
    EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, get_return_correct_element)
{
    TStack st(3);
    st.Put(1);
    st.Put(2);
    EXPECT_EQ(2, st.Get());
}

TEST(TStack, cant_get_element_in_empty_stack)
{
    TStack st(3);
    st.Get();
    EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, top_elem_is_changing_after_getting_new_elem)
{
    TStack st(3);
    st.Put(1);
    st.Put(2);
    st.Get();
    EXPECT_EQ(1, st.TopElem());
}

TEST(TStack, top_elem_does_not_change_after_put_in_full_stack)
{
    TStack st(3);
    st.Put(1);
    st.Put(2);
    st.Put(3);
    st.Put(4);
    EXPECT_EQ(3, st.TopElem());
}

TEST(TStack, cant_get_top_elem_in_empty_stack)
{
    TStack st(2);
    st.TopElem();
    EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TFormula, can_build_brakets_table)
{
    TFormula f("5+3-))(4*3)+4/(((3-2)))*7((-4");
    int Brackets[25];
    ASSERT_NO_THROW(f.FormulaChecker(Brackets, 25));
}

TEST(TFormula, formula_checker_build_correct_table)
{
    TFormula f("((5+2)/3)+(4)-5+(6*(5-3))))((");
    int CorrectBrackets[] = {2, 3, 1, 4, 5, 6, 8, 9, 7, 10, -1, 11, -1, 12, 14, -1, 13, -1};
    int Brackets[30];
    int size = f.FormulaChecker(Brackets, 30);
    for(int i = 0; i < size; i++)
        EXPECT_EQ(Brackets[i], CorrectBrackets[i]);
}

TEST(TFormula, correct_calculate_formula_with__no_operators_and_correct_brackets)
{
    TFormula f("(((4.3)))");
    EXPECT_DOUBLE_EQ(4.3, f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_formula_with_uncorrect_brackets)
{
    TFormula f(")(((4.3)))(()())(");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operator_plus)
{
    TFormula f("4+5");
    EXPECT_DOUBLE_EQ(9, f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operator_minus)
{
    TFormula f("9-3");
    EXPECT_DOUBLE_EQ(6, f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operator_multiple)
{
    TFormula f("3*7");
    EXPECT_DOUBLE_EQ(21, f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operator_divide)
{
    TFormula f("10/5");
    EXPECT_DOUBLE_EQ(2, f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operators_plus_with_correct_brackets)
{
    TFormula f("5.5+(4.4+3.3+2.2)");
    EXPECT_DOUBLE_EQ(15.4, f.FormulaCalculator());
}

TEST(TFormula, correct_calculate_simple_operators_minus_with_correct_brackets)
{
    TFormula f("5.5-(4.4-3.3)-2.2");
    EXPECT_DOUBLE_EQ(2.2, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_simple_operators_multiplicate_with_correct_brackets)
{
    TFormula f("(5.5*4.4)*(3.3*2.2)");
    EXPECT_DOUBLE_EQ(175.692, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_simple_operators_divide_with_correct_brackets)
{
    TFormula f("5.5/4.4/3.3/2.2");
    EXPECT_DOUBLE_EQ(5.5/4.4/3.3/2.2, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_formula_with_different_operators)
{
    TFormula f("5.5+4.4*3.3-2.2/1.1");
    EXPECT_DOUBLE_EQ(18.02, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_formula_with_different_operators_and_correct_brackets)
{
    TFormula f("(5.5+4.4)*((3.3-2.2*5/2)/1.1)");
    EXPECT_DOUBLE_EQ(-19.8, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_formula_with_different_operators_and_many_correct_brackets)
{
    TFormula f("(((((((5))))+((6.6)))/(5)+(4.4)*4.5-(3.5)))");
    EXPECT_DOUBLE_EQ(18.62, f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_formula_with_no_operators_and_uncorrect_brackets)
{
    TFormula f("((5+3)))");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_formula_with_not_enough_operands)
{
    TFormula f("5++5-4**3");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_formula_with_not_enough_operators)
{
    TFormula f("5 4.3 22+11");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, cant_calculate_formula_with_unknown_symbols)
{
    TFormula f("543 + 42 tf");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}


