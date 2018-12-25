#include "tstack.h"



#include "gtest.h"



TEST(TStack, can_crate_stack)

{

    ASSERT_NO_THROW(TStack a);

}



TEST(TStack, can_add_and_remove_element)

{

    TStack a;

    EXPECT_NO_THROW(a.Put(1));

    EXPECT_NO_THROW(a.Get());

}



TEST(TStack, cant_add_element_if_stack_has_no_data)

{

    TStack a(0);

    a.Put(1);

    EXPECT_EQ(DataNoMem,a.IsValid());

}



TEST(TStack, cant_remove_element_if_stack_has_no_data)

{

    TStack a(0);

    try

    {

        a.Get();

    }

    catch(int)

    {

        EXPECT_EQ(DataNoMem,a.IsValid());

    }

}



TEST(TStack, cant_add_element_if_stack_is_full)

{

    TStack a(1);

    a.Put(1);

    a.Put(1);

    EXPECT_EQ(DataFull,a.IsValid());

}



TEST(TStack, cant_remove_element_if_stack_is_empty)

{

    TStack a(1);

    try

    {

        a.Get();

    }

    catch(int)

    {

        EXPECT_EQ(DataEmpty,a.IsValid());

    }

}



TEST(TStack, cant_get_top_element_if_stack_has_no_data)

{

    TStack a(0);

    try

    {

        a.TopElem();

    }

    catch(int)

    {

        EXPECT_EQ(DataNoMem,a.IsValid());

    }

}



TEST(TStack, cant_get_top_element_if_stack_is_empty)

{

    TStack a(1);

    try

    {

        a.TopElem();

    }

    catch(int)

    {

        EXPECT_EQ(DataEmpty,a.IsValid());

    }

}

