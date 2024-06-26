/*
@author: Kendric Agdaca
@since: 06/06/24 ->

@purpose:
    -This is my very first time learning and using google test in order to mass unit test my code. I've kept it very simple and just used EXPECT_TRUE, EXPECT_FALSE, and EXPECT_EQ.

@notes:
    -#include "gtest/gtest.h" already included in pch.h
*/
#include "pch.h"
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.h"
#include "C:\Users\kenga\source\repos\C++\Scientific_Calculator_Rewrite/calculate.cpp"
using namespace std;

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






    EXPECT_TRUE(validateInput("sin(30)"));
    EXPECT_TRUE(validateInput("cos(60)"));
    EXPECT_TRUE(validateInput("tan(45)"));
    EXPECT_TRUE(validateInput("log(100)"));
    EXPECT_TRUE(validateInput("ln(2)"));
    EXPECT_TRUE(validateInput("sqrt(16)"));
    EXPECT_TRUE(validateInput("abs(-5)"));

    EXPECT_TRUE(validateInput("sin(cos(30))"));
    EXPECT_TRUE(validateInput("tan(log(100))"));
    EXPECT_TRUE(validateInput("sqrt(abs(-9))"));
    EXPECT_TRUE(validateInput("log(sqrt(100))"));

    EXPECT_TRUE(validateInput("3+sin(45)"));
    EXPECT_TRUE(validateInput("2*cos(60)"));
    EXPECT_TRUE(validateInput("tan(45)-1"));
    EXPECT_TRUE(validateInput("log(100)/2"));
    EXPECT_TRUE(validateInput("4*ln(2)"));
    EXPECT_TRUE(validateInput("sqrt(16)+2"));
    EXPECT_TRUE(validateInput("abs(-5)-3"));

    EXPECT_TRUE(validateInput("3+sin(cos(30))"));
    EXPECT_TRUE(validateInput("2*tan(log(100))"));
    EXPECT_TRUE(validateInput("sqrt(abs(-9))/3"));
    EXPECT_TRUE(validateInput("log(sqrt(100))-1"));

    EXPECT_TRUE(validateInput("sin(30)+cos(60)"));
    EXPECT_TRUE(validateInput("tan(45)*log(10)"));
    EXPECT_TRUE(validateInput("sqrt(16)/abs(-4)"));
    EXPECT_TRUE(validateInput("log(100)+ln(2)"));

    EXPECT_TRUE(validateInput("sin(30+45)"));
    EXPECT_TRUE(validateInput("cos(60-30)"));
    EXPECT_TRUE(validateInput("tan(45*2)"));
    EXPECT_TRUE(validateInput("log(100/10)"));
    EXPECT_TRUE(validateInput("sqrt(16+9)"));
    EXPECT_TRUE(validateInput("abs(-5-3)"));

    EXPECT_TRUE(validateInput("sin(0)"));
    EXPECT_TRUE(validateInput("cos(90)"));
    EXPECT_TRUE(validateInput("tan(0)"));
    EXPECT_TRUE(validateInput("log(1)"));
    EXPECT_TRUE(validateInput("ln(1)"));
    EXPECT_TRUE(validateInput("sqrt(0)"));
    EXPECT_TRUE(validateInput("abs(0)"));
    EXPECT_TRUE(validateInput("tan(45*log(10))"));
    EXPECT_TRUE(validateInput("abs(-5-3)"));
    EXPECT_TRUE(validateInput("sin(cos(tan(30)))"));
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



    EXPECT_FALSE(validateInput("sin()"));
    EXPECT_FALSE(validateInput("cos(60"));
    EXPECT_FALSE(validateInput("tan45)"));
    EXPECT_FALSE(validateInput("log(100"));
    EXPECT_FALSE(validateInput("ln2)"));
    EXPECT_FALSE(validateInput("sqrt16)"));
    EXPECT_FALSE(validateInput("abs(-5"));

    EXPECT_FALSE(validateInput("sin(cos(30)"));
    EXPECT_FALSE(validateInput("tan(log100))"));
    EXPECT_FALSE(validateInput("sqrt(abs-9))"));
    EXPECT_FALSE(validateInput("log(sqrt100)"));

    EXPECT_FALSE(validateInput("3+sin45)"));
    EXPECT_FALSE(validateInput("2*cos(60"));
    EXPECT_FALSE(validateInput("tan45)-1"));
    EXPECT_FALSE(validateInput("log100)/2"));
    EXPECT_FALSE(validateInput("4*ln2)"));
    EXPECT_FALSE(validateInput("sqrt16)+2"));
    EXPECT_FALSE(validateInput("abs(-5-3"));

    EXPECT_FALSE(validateInput("3+sin(cos(30)"));
    EXPECT_FALSE(validateInput("2*tan(log100))"));
    EXPECT_FALSE(validateInput("sqrt(abs-9))/3"));
    EXPECT_FALSE(validateInput("log(sqrt100)-1"));

    EXPECT_FALSE(validateInput("sin(30+cos(60)"));

    EXPECT_FALSE(validateInput("sqrt(16/abs(-4)"));
    EXPECT_FALSE(validateInput("log100+ln(2)"));

    EXPECT_FALSE(validateInput("sin30+45)"));
    EXPECT_FALSE(validateInput("cos60-30)"));
    EXPECT_FALSE(validateInput("tan(45*2"));
    EXPECT_FALSE(validateInput("log(100/10"));
    EXPECT_FALSE(validateInput("sqrt(16+9"));



    EXPECT_FALSE(validateInput("log(sqrt(abs(-16))))"));
    EXPECT_FALSE(validateInput("sin(cos(tan(30))"));
    EXPECT_FALSE(validateInput("log(sqrt(abs(-16))"));
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


    myStack = createStack({ "sin", "(", "45", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(45)"));

    myStack = createStack({ "cos", "(", "30", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("cos(30)"));

    myStack = createStack({ "tan", "(", "60", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("tan(60)"));

    myStack = createStack({ "log", "(", "100", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("log(100)"));

    myStack = createStack({ "ln", "(", "2.71828", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("ln(2.71828)"));

    myStack = createStack({ "sqrt", "(", "16", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(16)"));

    myStack = createStack({ "abs", "(", "-10", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("abs(-10)"));

    // Trigonometric functions with nested functions
    myStack = createStack({ "sin", "(", "cos", "(", "30", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(cos(30))"));

    myStack = createStack({ "tan", "(", "log", "(", "100", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("tan(log(100))"));

    myStack = createStack({ "sqrt", "(", "abs", "(", "-9", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(abs(-9))"));

    myStack = createStack({ "ln", "(", "sqrt", "(", "49", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("ln(sqrt(49))"));

    // Trigonometric functions with arithmetic operations
    myStack = createStack({ "sin", "(", "45", ")", "+", "cos", "(", "30", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(45)+cos(30)"));

    myStack = createStack({ "tan", "(", "60", ")", "-", "log", "(", "10", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("tan(60)-log(10)"));

    myStack = createStack({ "sqrt", "(", "16", ")", "*", "abs", "(", "-5", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(16)*abs(-5)"));

    myStack = createStack({ "ln", "(", "2.71828", ")", "/", "2" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("ln(2.71828)/2"));

    // Nested trigonometric functions with arithmetic operations
    myStack = createStack({ "sin", "(", "cos", "(", "30", ")", ")", "+", "tan", "(", "log", "(", "100", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(cos(30))+tan(log(100))"));

    myStack = createStack({ "sqrt", "(", "abs", "(", "-9", ")", ")", "-", "ln", "(", "sqrt", "(", "49", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(abs(-9))-ln(sqrt(49))"));

    // Trigonometric functions with complex arithmetic expressions
    myStack = createStack({ "sin", "(", "45", "*", "log", "(", "10", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(45*log(10))"));

    myStack = createStack({ "cos", "(", "30", "/", "2", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("cos(30/2)"));

    myStack = createStack({ "tan", "(", "60", "+", "15", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("tan(60+15)"));

    myStack = createStack({ "sqrt", "(", "16", "-", "4", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(16-4)"));

    myStack = createStack({ "abs", "(", "-10", "*", "2", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("abs(-10*2)"));

    // Edge cases
    myStack = createStack({ "sin", "(", "sin", "(", "30", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sin(sin(30))"));

    myStack = createStack({ "cos", "(", "cos", "(", "45", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("cos(cos(45))"));

    myStack = createStack({ "tan", "(", "tan", "(", "60", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("tan(tan(60))"));

    myStack = createStack({ "log", "(", "log", "(", "100", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("log(log(100))"));

    myStack = createStack({ "ln", "(", "ln", "(", "2.71828", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("ln(ln(2.71828))"));

    myStack = createStack({ "sqrt", "(", "sqrt", "(", "16", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("sqrt(sqrt(16))"));

    myStack = createStack({ "abs", "(", "abs", "(", "-10", ")", ")" });
    EXPECT_EQ(ReverseStack(myStack), Tokenize("abs(abs(-10))"));
}


/*
Format:
	expectedStack = ReverseStack(createStack({expected}));
	actualStack = ReverseStack(createStack({actual}));
	EXPECT_EQ(shuntingYard(expectedStack), actualStack);
*/
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



/*
Format: EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("equation"))), answer);
        EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize(""))), );
*/
TEST(evaluateEquationTest, validInput)
{
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("1+2"))), 3.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("3*4-5/6"))), 11.167);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("(7+8)*9"))), 135.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("10.5+3.2"))), 13.7);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("2^3-4*(5+6)/7"))), 1.714);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("-(3+4)"))), -7.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("2+(3*(4/5)^6)-7"))), -4.214);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("42"))), 42.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("-.5+2"))), 1.5);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("((2+3)*5)-6"))), 19.0);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("2*(3+(4-5))"))), 4);
    EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("2*(3+(-5))"))), -4);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}