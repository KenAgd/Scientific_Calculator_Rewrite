#include "pch.h"
//#include "gtest/gtest.h" already included in pch.h
using namespace std;
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.h"
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.cpp"

/*
static TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}*/


TEST(validateInputTest, validInput)
{
    string validInput;

    validInput = "1+2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2*3-4/2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "123.456";
	EXPECT_TRUE(validateInput(validInput));

    validInput = "3*4-5/6";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "(7+8)*9";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "10.5+3.2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2^3-4*(5+6)/7";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "-(3+4)";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2+(3*(4/5)^6)-7";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "42";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "-.5+2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "((2+3)*5)-6";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2*(3+(4-5))";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2*(3+(-5))";
    EXPECT_TRUE(validateInput(validInput));
}


TEST(ValidateInputTest, invalidInput) {
    string invalidInput;
       
    
    invalidInput = "1+1a";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "!2*3";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = " ";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1++2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1 ++ 2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1+*2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1+2 ";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1+ 2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1 +2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = " 1+2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "+123";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "123+";
    EXPECT_FALSE(validateInput(invalidInput));

	invalidInput = "123*";
	EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "*123";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "/123";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "123/";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "(";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = ")";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "()";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "(1+2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1+2)";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "a+b";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1+2+";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1..2+3";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1.2.3+4";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "1/0";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "2^";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "-";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "2*(3+4))";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "((2+3)";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "2*(3+())";
    EXPECT_FALSE(validateInput(invalidInput));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}