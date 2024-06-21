#include "pch.h"
//#include "gtest/gtest.h" already included in pch.h
using namespace std;
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.h"
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.cpp"




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

    validInput = "5%2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "12%5+1";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "10%3-1";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "3+4%2";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "2^2%10";
    EXPECT_TRUE(validateInput(validInput));

    validInput = "(2+3)%2";
    EXPECT_TRUE(validateInput(validInput));

    EXPECT_TRUE(validateInput("-5+3"));        // Valid expression with unary minus
    EXPECT_TRUE(validateInput("2*(-4)"));      // Valid expression with unary minus in parentheses
    EXPECT_TRUE(validateInput("-(-2)"));         // Valid nested unary minus
    EXPECT_TRUE(validateInput("-(3+4)"));      // Valid unary minus before parentheses
    EXPECT_TRUE(validateInput("5+-7"));        // Valid expression with space-separated unary minus
    EXPECT_TRUE(validateInput("2*-(-4)"));     // Valid nested unary minus with space-separated operator



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

	invalidInput = "5.%2";
	EXPECT_FALSE(validateInput(invalidInput));

	invalidInput = "5%2.";
	EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "%5";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "5%";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "5.%2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "12+%5";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "5%a";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "5%%2";
    EXPECT_FALSE(validateInput(invalidInput));

    invalidInput = "5%+2";
    EXPECT_FALSE(validateInput(invalidInput));

    EXPECT_FALSE(validateInput("2+-"));        // Unary minus without operand
    EXPECT_FALSE(validateInput("2*-*3"));    // Invalid sequence of operators with unary minus




}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}