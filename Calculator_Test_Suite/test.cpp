#include "pch.h"
//#include "gtest/gtest.h" already included in pch.h
using namespace std;
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.h"
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.cpp"
//#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/main.cpp"
//#include <stack>
#include <iostream>

/*
Template:     EXPECT_TRUE(validateInput(""));
*/
TEST(validateInputTest, validInput)
{
    EXPECT_TRUE(validateInput("1+2"));
    EXPECT_TRUE(validateInput("2*3-4/2"));
	EXPECT_TRUE(validateInput("123.456"));
    EXPECT_TRUE(validateInput("3*4-5/6"));
    EXPECT_TRUE(validateInput("(7+8)*9"));
    EXPECT_TRUE(validateInput("10.5+3.2"));
    EXPECT_TRUE(validateInput("2^3-4*(5+6)/7"));
    EXPECT_TRUE(validateInput("-(3+4)"));
    EXPECT_TRUE(validateInput("2+(3*(4/5)^6)-7"));
    EXPECT_TRUE(validateInput("42"));
    EXPECT_TRUE(validateInput("-.5+2"));
    EXPECT_TRUE(validateInput("((2+3)*5)-6"));
    EXPECT_TRUE(validateInput("2*(3+(4-5))"));
    EXPECT_TRUE(validateInput("5%2"));
    EXPECT_TRUE(validateInput("12%5+1"));
    EXPECT_TRUE(validateInput("10%3-1"));
    EXPECT_TRUE(validateInput("3+4%2"));
    EXPECT_TRUE(validateInput("2^2%10"));
    EXPECT_TRUE(validateInput("(2+3)%2"));
    EXPECT_TRUE(validateInput("-5+3"));        
    EXPECT_TRUE(validateInput("2*(-4)"));      
    EXPECT_TRUE(validateInput("-(-2)"));       
    EXPECT_TRUE(validateInput("-(3+4)"));     
    EXPECT_TRUE(validateInput("5+-7"));       
    EXPECT_TRUE(validateInput("2*-(-4)"));    
}


/*
Template:     EXPECT_FALSE(validateInput(""));
*/
TEST(validateInputTest, invalidInput)
{
    EXPECT_FALSE(validateInput("1+1a"));
    EXPECT_FALSE(validateInput("!2*3"));
    EXPECT_FALSE(validateInput(""));
    EXPECT_FALSE(validateInput(" "));
    EXPECT_FALSE(validateInput("1++2"));
    EXPECT_FALSE(validateInput("1 ++ 2"));
    EXPECT_FALSE(validateInput("1+*2"));
    EXPECT_FALSE(validateInput("1+2 "));
    EXPECT_FALSE(validateInput("1+ 2"));
    EXPECT_FALSE(validateInput("1 +2"));
    EXPECT_FALSE(validateInput(" 1+2"));
    EXPECT_FALSE(validateInput("+123"));
    EXPECT_FALSE(validateInput("123+"));
	EXPECT_FALSE(validateInput("123*"));
    EXPECT_FALSE(validateInput("*123"));
    EXPECT_FALSE(validateInput("/123"));
    EXPECT_FALSE(validateInput("123/"));
    EXPECT_FALSE(validateInput("("));
    EXPECT_FALSE(validateInput(")"));
    EXPECT_FALSE(validateInput("()"));
    EXPECT_FALSE(validateInput("(1+2"));
    EXPECT_FALSE(validateInput("1+2)"));
    EXPECT_FALSE(validateInput("a+b"));
    EXPECT_FALSE(validateInput("1+2+"));
    EXPECT_FALSE(validateInput("1..2+3"));
    EXPECT_FALSE(validateInput("1.2.3+4"));
    EXPECT_FALSE(validateInput("1/0"));
    EXPECT_FALSE(validateInput("2^"));
    EXPECT_FALSE(validateInput("-"));
    EXPECT_FALSE(validateInput("2*(3+4))"));
    EXPECT_FALSE(validateInput("((2+3)"));
    EXPECT_FALSE(validateInput("2*(3+())"));
	EXPECT_FALSE(validateInput("5.%2"));
	EXPECT_FALSE(validateInput("5%2."));
    EXPECT_FALSE(validateInput("%5"));
    EXPECT_FALSE(validateInput("5%"));
    EXPECT_FALSE(validateInput("5.%2"));
    EXPECT_FALSE(validateInput("12+%5"));
    EXPECT_FALSE(validateInput("5%a"));
    EXPECT_FALSE(validateInput("5%%2"));
    EXPECT_FALSE(validateInput("5%+2"));
    EXPECT_FALSE(validateInput("2+-"));        
    EXPECT_FALSE(validateInput("2*-*3"));    




}


/*
@purpose: 
	-creates a stack from an initializer_list
@param: 
	-const initializer_list<string>& elements: The elements to be added to the stack. Look at shuntingYardTest for syntax use and examples.
@returns: 
	-Returns a stack<string> with the elements in the initializer_list.

@note:
	-initializer_list is similar to parameterized constructors where the stack is declared and initialized with a list of elements in the same line.
*/
stack<string> createStack(const initializer_list<string>& elements) {
    return stack<string>(elements);
}

/*
Template:     myStack = createStack({expected})
              EXPECT_EQ(ReverseStack(myStack), Tokenize("actual"));
                                     
              myStack = createStack({});
              EXPECT_EQ(ReverseStack(myStack), Tokenize(""));


@note:
    -myStack has to be reversed because stacks are LIFO. "actual" is reversed through the tokenize function so the top of the stack is -3.5, 
        HOWEVER, myStack is not reversed and by initializing using ({}),the top of the myStack is 2. Using ({}) pushes each index onto the 
        stack from left to right.

*/
TEST(tokenizeTest, validInput)
{
    stack<string>myStack;

    myStack = createStack({ "-3.5", "+", "(", "-2.1", "*", "-4.2", ")", "/", "2" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("-3.5+(-2.1*-4.2)/2"));

    myStack = createStack({ "1", "+", "2", "*", "3" });
	EXPECT_EQ(ReverseStack(myStack), Tokenize("1+2*3"));

    myStack = createStack({ "10", "-", "5", "/", "2.5" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("10-5/2.5"));

	myStack = createStack({ "(", "6.1", "+", "4.2", ")", "*", "3" });
	EXPECT_EQ(ReverseStack(myStack), Tokenize("(6.1+4.2)*3"));

	myStack = createStack({ "1", "-",  "-2" });
	EXPECT_EQ(ReverseStack(myStack), Tokenize("1--2"));
}


TEST(shuntingYardTest, validInput)
{
    stack<string>expectedStack;
    stack<string>actualStack;

	expectedStack = ReverseStack(createStack({ "-3.5", "+", "(", "-2.1", "*", "-4.2", ")", "/", "2" }));
    actualStack = ReverseStack(createStack({"-3.5", "-2.1", "-4.2", "*", "2", "/", "+"}));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);

    expectedStack = ReverseStack(createStack({ "7", "+", "8", "*", "9" }));
    actualStack = ReverseStack(createStack({ "7", "8", "9", "*", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "15", "-", "4", "/", "2" }));
    actualStack = ReverseStack(createStack({ "15", "4", "2", "/", "-" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "(", "5", "+", "6", ")", "*", "2" }));
    actualStack = ReverseStack(createStack({ "5", "6", "+", "2", "*" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);



    expectedStack = ReverseStack(createStack({ "12", "/", "3", "+", "1" }));
    actualStack = ReverseStack(createStack({ "12", "3", "/", "1", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "9", "*", "(", "3", "+", "4", ")" }));
    actualStack = ReverseStack(createStack({ "9", "3", "4", "+", "*" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "7", "-", "5", "+", "2" }));//
    actualStack = ReverseStack(createStack({ "7", "5", "-", "2", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "8", "+", "(", "3", "*", "2", ")", "-", "4" }));//
    actualStack = ReverseStack(createStack({ "8", "3", "2", "*", "+", "4", "-" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "6", "*", "2", "+", "3" }));
    actualStack = ReverseStack(createStack({ "6", "2", "*", "3", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "14", "/", "(", "7", "-", "3", ")" }));
    actualStack = ReverseStack(createStack({ "14", "7", "3", "-", "/" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "(", "8", "+", "2", ")", "*", "(", "5", "-", "1", ")" }));
    actualStack = ReverseStack(createStack({ "8", "2", "+", "5", "1", "-", "*" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "-3.5", "+", "(", "-2.1", "*", "-4.2", ")", "/", "2" }));
    actualStack = ReverseStack(createStack({ "-3.5", "-2.1", "-4.2", "*", "2", "/", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);

}





TEST(evaluateEquationTest, validInput)
{
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("1+2"))), 3.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("1+2+3"))), 6.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("1+2*3"))), 7.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("1*2+3"))), 5.0);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}