#include "tstack.h"
#include "gtest.h"

TEST(TStack, can_create_tstack)
{
	ASSERT_NO_THROW(TStack(10));
}

TEST(TStack, cant_create_tstack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack St(-10));
}


TEST(TStack, can_put_element)
{
	TStack St(10);
	ASSERT_NO_THROW(St.Put(1));
}

TEST(TStack, can_get_element)
{
	TStack St(10);
	St.Put(1);
	ASSERT_NO_THROW(St.Get());
}

TEST(TStack, get_element_is_correct)
{
	TStack St(10);
	St.Put(1);
	St.Put(5);
	EXPECT_EQ(5, St.Get());
}

TEST(TStack, can_change_retcode_when_get_element_in_empty_stack)
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

TEST(TStack, top_elememt_can_change_after_put_element)
{
	TStack St(10);
	St.Put(1);
	St.Put(5);
	ASSERT_EQ(5, St.TopElem());
}


TEST(TStack, top_element_can_change_after_get_element)
{
	TStack St(10);
	St.Put(1);
	St.Put(5);	
	St.Get();
	ASSERT_EQ(1, St.TopElem());
}

TEST(TStack, top_element_cant_change_when_put_element_in_full_stack)
{
	TStack St(2);
	St.Put(1);
	St.Put(2);
	St.Put(3);
	ASSERT_EQ(2, St.TopElem());
}

TEST(TStack, can_change_retcode_when_get_top__element_in_empty_tstack)
{
	TStack St(10);
	St.TopElem();
	ASSERT_EQ(DataEmpty, St.GetRetCode());
}
