#include "gtest/gtest.h"
#include "Calculator.h"

TEST(Calculator, IsTrue) {
    Calculator calculator;

    calculator.input("1");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("2 + 2");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("3-3");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("4.4 / 44.44");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("5 + (5 + 5)");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("(((6*6)*6)*6)");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("7 -7");
    ASSERT_TRUE(calculator.isTrue());
    calculator.input("(-8) + 8/(-8)");
    ASSERT_TRUE(calculator.isTrue());

    calculator.input("1 -");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("2 + 2 -");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("((3 + 3) + 3");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("((4 + 4))) + ( 4");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("5 - - 5");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("6/-6");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("");
    ASSERT_FALSE(calculator.isTrue());
    calculator.input("8 8");
    ASSERT_FALSE(calculator.isTrue());
}
TEST(Calculator, ToPolish) {
    Calculator calculator;

    calculator.input("1 + 2");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 +");
    calculator.input("1 + 2 - 3");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 + 3 -");
    calculator.input("1 + (2 - 3)");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 3 - +");
    calculator.input("1 + 2 * 3");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 3 * +");
    calculator.input("1 + (2 - 4) * 5");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 4 - 5 * +");
    calculator.input("1 + (2 - 4) * (5 + 6 / 7)");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "1 2 4 - 5 6 7 / + * +");
    calculator.input("(2 + 7 - 1) / (5 - 2 + 8)");
    calculator.createPolish();
    ASSERT_EQ(calculator.polishToString(), "2 7 + 1 - 5 2 - 8 + /");
}
TEST(Calculator, Calculate) {
    Calculator calculator;

    calculator.input("1 + 2 + 3");
    ASSERT_EQ(calculator.calculate(), 6);
    calculator.input("2 + (4 - 3)");
    ASSERT_EQ(calculator.calculate(), 3);
    calculator.input("7 * 2 - 1");
    ASSERT_EQ(calculator.calculate(), 13);
    calculator.input("4 / 1 + 3 * 3");
    ASSERT_EQ(calculator.calculate(), 13);
    calculator.input("5 * (2 + 3 + 1) / 3");
    ASSERT_EQ(calculator.calculate(), 10);
    calculator.input("(2 - 3 * 4) / (-5)");
    ASSERT_EQ(calculator.calculate(), 2);
}