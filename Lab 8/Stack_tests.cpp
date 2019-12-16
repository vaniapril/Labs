#include "gtest/gtest.h"
#include "Stack.h"


TEST(Stack, PushPop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    ASSERT_EQ(stack.pop(), 4);
    ASSERT_EQ(stack.pop(), 3);
    stack.push(5);
    stack.push(6);
    ASSERT_EQ(stack.pop(), 6);
    ASSERT_EQ(stack.pop(), 5);
    ASSERT_EQ(stack.pop(), 2);
    ASSERT_EQ(stack.pop(), 1);
}
TEST(Stack, SizeIsEmplty) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    ASSERT_EQ(stack.size(), 4);
    ASSERT_EQ(stack.isEmpty(), false);
    stack.push(5);
    stack.push(6);
    ASSERT_EQ(stack.size(), 6);
    ASSERT_EQ(stack.isEmpty(), false);
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    ASSERT_EQ(stack.size(), 0);
    ASSERT_EQ(stack.isEmpty(), true);
}
TEST(Stack, OperatorInOut) {
    Stack<int> stack;
    stack<<1;
    stack<<2;
    stack<<3;
    stack<<4;
    int i;
    stack>>i;
    ASSERT_EQ(i, 4);
    stack>>i;
    ASSERT_EQ(i, 3);
    stack<<5;
    stack<<6;
    stack>>i;
    ASSERT_EQ(i, 6);
    stack>>i;
    ASSERT_EQ(i, 5);
    stack>>i;
    ASSERT_EQ(i, 2);
    stack>>i;
    ASSERT_EQ(i, 1);

}
TEST(Stack, OperatorIndexRemove) {
    Stack<int> stack ={7,6,5,4,3,2,1};
    ASSERT_EQ(stack[0], 1);
    ASSERT_EQ(stack[2], 3);
    ASSERT_EQ(stack[6], 7);
    stack.push(9);
    stack.push(10);
    ASSERT_EQ(stack[0], 10);
    ASSERT_EQ(stack[1], 9);
    stack.remove(5);
    ASSERT_EQ(stack[5], 5);
    stack.remove(2);
    ASSERT_EQ(stack[2], 2);
    stack.remove(0);
    ASSERT_EQ(stack[4], 6);
}
TEST(Stack, OperatorComp) {
    Stack<int> stack ={1,2,3,4};
    Stack<int> stack1 ={1,2,3,4};
    Stack<int> stack2 ={1,2,3};
    Stack<int> stack3 ={1,2,3,4,5};
    Stack<int> stack4 ={2,2,3,4};
    Stack<int> stack5 ={0,2,3,4};

    ASSERT_EQ(stack == stack1, true);
    ASSERT_EQ(stack > stack2, true);
    ASSERT_EQ(stack < stack3, true);
    ASSERT_EQ(stack < stack4, true);
    ASSERT_EQ(stack > stack5, true);

    ASSERT_EQ(stack != stack1, false);
    ASSERT_EQ(stack < stack2, false);
    ASSERT_EQ(stack > stack3, false);
    ASSERT_EQ(stack > stack4, false);
    ASSERT_EQ(stack < stack5, false);
}