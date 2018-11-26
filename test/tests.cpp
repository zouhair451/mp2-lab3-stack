#include<gtest.h>
#include"tstack.h"
#include"tformula.h"
TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack(-1));
}
TEST(TStack, can_create_copied_stack)
{
	TStack temp(3);
	ASSERT_NO_THROW(TStack st(temp));
}
TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack temp(3);
	temp.Put(4);
	TStack st(temp);
	EXPECT_EQ(temp.Get(),st.Get());
}
TEST(TStack, copied_stack_have_its_own_memory)
{
	TStack temp(3);
	temp.Put(4);
	TStack st(temp);
	EXPECT_NE(&temp, &st);
}
TEST(TStack, can_stack_get_its_size)
{
	TStack temp(3);
	temp.Put(4);
	EXPECT_EQ(3,temp.GetSize());
}
TEST(TStack, can_get_and_set_element)
{
	TStack temp(3);
	temp.Put(4);
	EXPECT_EQ(4,temp.Get());
}
TEST(TStack, cant_get_elment_from_empty_stack)
{
	TStack temp(4);
	ASSERT_ANY_THROW(temp.Get());
}
TEST(TStack, cant_pop_elment_from_empty_stack)
{
	TStack temp(4);
	ASSERT_ANY_THROW(temp.Pop());
}
TEST(TStack, cant_get_elment_from_stack_without_mem)
{
	TStack temp(0);
	ASSERT_ANY_THROW(temp.Get());
}
TEST(TStack, cant_pop_elment_from_stack_without_mem)
{
	TStack temp(0);
	ASSERT_ANY_THROW(temp.Pop());
}
TEST(TStack, can_pop_element)
{
	TStack temp(3);
	temp.Put(4);
	temp.Put(1);
	temp.Pop();
	EXPECT_NE(1, temp.Get());
}
TEST(TStack, can_get_its_size)
{
	TStack temp(3);
	temp.Put(4);
	EXPECT_EQ(3, temp.GetSize());
}
TEST(TStack, can_detect_if_stack_is_empty)
{
	TStack temp(3);
	EXPECT_EQ(1, temp.IsEmpty());
}
TEST(TStack, can_detect_if_stack_is_not_empty)
{
	TStack temp(3);
	temp.Put(11);
	EXPECT_EQ(0, temp.IsEmpty());
}
TEST(TStack, can_detect_if_stack_is_not_full)
{
	TStack temp(3);
	temp.Put(11);
	EXPECT_EQ(0, temp.IsFull());
}
TEST(TStack, can_detect_if_stack_is_full)
{
	TStack temp(1);
	temp.Put(8);
	EXPECT_EQ(1, temp.IsFull());
}
TEST(TStack, pop_throws_when_stack_is_empty)
{
	TStack temp(3);
	ASSERT_ANY_THROW(temp.Pop());
}
TEST(TStack, put_throws_when_stack_is_full)
{
	TStack temp(2);
	temp.Put(10);
	temp.Put(12);
	ASSERT_ANY_THROW(temp.Put(1));
}
TEST(TStack, can_resize_stack)
{
	TStack temp(3);
	temp.Resize(6);
	for (int i = 0; i < 6; i++)
		temp.Put(i);
	EXPECT_EQ(6,temp.GetSize());
}
TEST(TStack, can_resize_stack_to_zero)
{
	TStack temp(3);
	temp.Resize(0);
	EXPECT_EQ(0, temp.GetSize());
}
TEST(TStack, stack_is_valid)
{
	TStack temp(3);
	temp.Resize(6);
	for (int i = 0; i < 6; i++)
		temp.Put(i);
	EXPECT_EQ(1, temp.IsValid());
}
TEST(TStack, can_print_values)
{
	TStack temp(3);
	for (int i = 0; i < 3; i++)
		temp.Put(i);
	ASSERT_NO_THROW(temp.Print());
}
TEST(TFormula, can_check_proper_formula)
{
	std::string str1 = "(2+3)*6*4/8-(2+5)/16";
	int size = str1.length() * 2;
	int* brackets = new int[size];
	TFormula f(str1);
	EXPECT_EQ(0, f.FormulaChecker(brackets, size));
	delete[] brackets;
}
TEST(TFormula, can_check_wrong_formula)
{
	std::string str1 = "(2+3)*6*4/8-(2+5)/16))";
	int size = str1.length() * 2;
	int* brackets = new int[size];
	TFormula f(str1);
	EXPECT_EQ(2, f.FormulaChecker(brackets, size));
	delete[] brackets;
}
TEST(TFormula, can_calculate_proper_formula)
{
	std::string str1 = "(2+3)*6*4/8-(2+5)/16";
	TFormula f(str1);
	EXPECT_EQ(0, f.FormulaConverter());
}
TEST(TFormula, throw_when_calculate_wrong_formula)
{
	std::string str1 = "))(2+3)*6*4/8-(2+5)/16))";
	TFormula f(str1);
	ASSERT_ANY_THROW(f.FormulaCalculator());
}
TEST(TFormula, throw_when_create_empty_formula)
{
	std::string str1 = "";
	ASSERT_ANY_THROW(TFormula f((char*)str1.c_str()));
}