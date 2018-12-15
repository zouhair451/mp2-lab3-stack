#include "gtest.h"
#include "TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> a(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> a(-5));
}
TEST(TStack, function_IsFull_return_right_value)
{
	TStack<int> a(1);
	EXPECT_EQ(0, a.IsFull());
	a.Put(1);
	EXPECT_EQ(1, a.IsFull());
}
TEST(TStack, function_IsEmpty_return_right_value)
{
	TStack<int> a(1);
	EXPECT_EQ(1, a.IsEmpty());
	a.Put(1);
	EXPECT_EQ(0, a.IsEmpty());
}
TEST(TStack, can_put_any_value_into_stack)
{
	TStack<int> a(2);
	ASSERT_NO_THROW(a.Put(5));
	ASSERT_NO_THROW(a.Put(2));
	EXPECT_EQ(0, a.IsEmpty());
}
TEST(TStack, can_get_any_value_from_stack)
{
	TStack<int> a(2);
	a.Put(5);
	a.Put(2);
	EXPECT_EQ(2, a.Get());
	EXPECT_EQ(5, a.Get());
	EXPECT_EQ(1, a.IsEmpty());
}