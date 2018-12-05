#include "tformula.h"
#include "tstack.h"

#include "gtest.h"

//тестируем стэк
TEST(TStack, can_create_stack_with_positive_length)
{
	TStack st(5);
	
	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, create_empty_stack)
{
	TStack st(3);

	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, cant_put_with_no_mem)
{
	TStack st(0);

	st.Put(3);

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_put_if_full)
{
	TStack st(1);

	st.Put(1);
	st.Put(2);

	EXPECT_EQ(DataFull, st.GetRetCode());
}

TEST(TStack, can_put_if_ok)
{
	TStack st(3);

	st.Put(3);

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, have_value_when_put)
{
	TStack st(2);

	st.Put(4);

	EXPECT_EQ(4, st.TopElem());
}

TEST(TStack, cant_get_with_no_mem)
{
	TStack st(0);

	st.Get();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_get_if_empty)
{
	TStack st(3);

	st.Get();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_get_if_have_value)
{
	TStack st(3);

	st.Put(4);
	st.Get();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_get_true_value)
{
	TStack st(3);

	st.Put(3);
	
	EXPECT_EQ(3, st.Get());
}

TEST(TStack, empty_stack_after_get_first_element)
{
	TStack st(2);

	st.Put(5);
	st.Get();

	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, cant_topelem_when_no_mem)
{
	TStack st(0);

	st.TopElem();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_topelem_if_empty)
{
	TStack st(5);

	st.TopElem();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_topelem)
{
	TStack st(3);

	st.Put(9);
	st.TopElem();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_topelem_true_value)
{
	TStack st(3);

	st.Put(4);

	EXPECT_EQ(4, st.TopElem());
}


// тестируем tformula

