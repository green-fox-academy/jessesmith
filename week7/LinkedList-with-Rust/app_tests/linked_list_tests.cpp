//
// Created by Jesse Smith on 2019-05-16.
//


#include "gtest/gtest.h"

extern "C" {
#include "linked_list.h"

    class LinkedListTest : public ::testing::Test {
        protected:
            void SetUp() override {
                list = &list_obj;
                initialize_linked_list(list);
            }

            // void TearDown() override {}

            LinkedList list_obj;
            LinkedList* list;

            Data data1 = { .number = 1 };
            Data data2 = { .number = 2 };
            Data data3 = { .number = 3 };
            Data data4 = { .number = 4 };
    };


    TEST_F(LinkedListTest, SizeAndInsert) {
        EXPECT_EQ(size(list), 0);
        insert(list, data1);
        EXPECT_EQ(size(list), 1);
        insert(list, data1);
        EXPECT_EQ(size(list), 2);
        insert(list, data1);
        EXPECT_EQ(size(list), 3);
    }

    TEST_F(LinkedListTest, Get) {
        insert(list, data1);
        insert(list, data2);
        insert(list, data3);
        insert(list, data4);
        EXPECT_EQ(get(list, 0)->number, 1);
        EXPECT_EQ(get(list, 1)->number, 2);
        EXPECT_EQ(get(list, 2)->number, 3);
        EXPECT_EQ(get(list, 3)->number, 4);
    }

    TEST_F(LinkedListTest, InsertFirst) {
        EXPECT_EQ(size(list), 0);
        insert(list, data1);
        EXPECT_EQ(size(list), 1);
        insertFirst(list, data2);
        EXPECT_EQ(size(list), 2);
        insert(list, data3);
        EXPECT_EQ(size(list), 3);
        insertFirst(list, data4);
        EXPECT_EQ(size(list), 4);
        EXPECT_EQ(get(list, 0)->number, 4);
        EXPECT_EQ(get(list, 1)->number, 2);
        EXPECT_EQ(get(list, 2)->number, 1);
        EXPECT_EQ(get(list, 3)->number, 3);
    }


    TEST_F(LinkedListTest, Pop) {
        EXPECT_EQ(size(list), 0);
        EXPECT_EQ(pop(list, 0), nullptr);

        insert(list, data1);
        EXPECT_EQ(size(list), 1);
        EXPECT_EQ(pop(list, 0)->number, 1);
        EXPECT_EQ(size(list), 0);

        insert(list, data1);
        insert(list, data2);
        EXPECT_EQ(size(list), 2);
        EXPECT_EQ(pop(list, 1)->number, 2);
        EXPECT_EQ(size(list), 1);
        EXPECT_EQ(pop(list, 0)->number, 1);
        EXPECT_EQ(size(list), 0);


        insert(list, data1);
        insert(list, data2);
        insert(list, data3);
        insert(list, data4);
        EXPECT_EQ(size(list), 4);
        EXPECT_EQ(pop(list, 2)->number, 3);
        EXPECT_EQ(size(list), 3);
        EXPECT_EQ(pop(list, 0)->number, 1);
        EXPECT_EQ(size(list), 2);
        EXPECT_EQ(pop(list, 1)->number, 4);
        EXPECT_EQ(size(list), 1);
        EXPECT_EQ(pop(list, 0)->number, 2);
        EXPECT_EQ(size(list), 0);
    }
}
