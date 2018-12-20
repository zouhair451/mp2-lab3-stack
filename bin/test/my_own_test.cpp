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

