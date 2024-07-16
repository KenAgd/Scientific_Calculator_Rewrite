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
Template:     EXPECT_TRUE(validateEquation(""));
*/
TEST(validateEquationTest, validInput)
{
    EXPECT_TRUE(validateEquation("1+2"));
    EXPECT_TRUE(validateEquation("2*3-4/2"));
	EXPECT_TRUE(validateEquation("123.456"));
    EXPECT_TRUE(validateEquation("3*4-5/6"));
    EXPECT_TRUE(validateEquation("(7+8)*9"));
    EXPECT_TRUE(validateEquation("10.5+3.2"));
    EXPECT_TRUE(validateEquation("2^3-4*(5+6)/7"));
    EXPECT_TRUE(validateEquation("-(3+4)"));
    EXPECT_TRUE(validateEquation("2+(3*(4/5)^6)-7"));
    EXPECT_TRUE(validateEquation("42"));
    EXPECT_TRUE(validateEquation("-.5+2"));
    EXPECT_TRUE(validateEquation("((2+3)*5)-6"));
    EXPECT_TRUE(validateEquation("2*(3+(4-5))"));
    EXPECT_TRUE(validateEquation("5%2"));
    EXPECT_TRUE(validateEquation("12%5+1"));
    EXPECT_TRUE(validateEquation("10%3-1"));
    EXPECT_TRUE(validateEquation("3+4%2"));
    EXPECT_TRUE(validateEquation("2^2%10"));
    EXPECT_TRUE(validateEquation("(2+3)%2"));
    EXPECT_TRUE(validateEquation("-5+3"));        
    EXPECT_TRUE(validateEquation("2*(-4)"));      
    EXPECT_TRUE(validateEquation("-(-2)"));       
    EXPECT_TRUE(validateEquation("-(3+4)"));     
    EXPECT_TRUE(validateEquation("5+-7"));       
    EXPECT_TRUE(validateEquation("2*-(-4)"));    






    EXPECT_TRUE(validateEquation("sin(30)"));
    EXPECT_TRUE(validateEquation("cos(60)"));
    EXPECT_TRUE(validateEquation("tan(45)"));
    EXPECT_TRUE(validateEquation("log(100)"));
    EXPECT_TRUE(validateEquation("ln(2)"));
    EXPECT_TRUE(validateEquation("sqrt(16)"));
    EXPECT_TRUE(validateEquation("abs(-5)"));

    EXPECT_TRUE(validateEquation("sin(cos(30))"));
    EXPECT_TRUE(validateEquation("tan(log(100))"));
    EXPECT_TRUE(validateEquation("sqrt(abs(-9))"));
    EXPECT_TRUE(validateEquation("log(sqrt(100))"));

    EXPECT_TRUE(validateEquation("3+sin(45)"));
    EXPECT_TRUE(validateEquation("2*cos(60)"));
    EXPECT_TRUE(validateEquation("tan(45)-1"));
    EXPECT_TRUE(validateEquation("log(100)/2"));
    EXPECT_TRUE(validateEquation("4*ln(2)"));
    EXPECT_TRUE(validateEquation("sqrt(16)+2"));
    EXPECT_TRUE(validateEquation("abs(-5)-3"));

    EXPECT_TRUE(validateEquation("3+sin(cos(30))"));
    EXPECT_TRUE(validateEquation("2*tan(log(100))"));
    EXPECT_TRUE(validateEquation("sqrt(abs(-9))/3"));
    EXPECT_TRUE(validateEquation("log(sqrt(100))-1"));

    EXPECT_TRUE(validateEquation("sin(30)+cos(60)"));
    EXPECT_TRUE(validateEquation("tan(45)*log(10)"));
    EXPECT_TRUE(validateEquation("sqrt(16)/abs(-4)"));
    EXPECT_TRUE(validateEquation("log(100)+ln(2)"));

    EXPECT_TRUE(validateEquation("sin(30+45)"));
    EXPECT_TRUE(validateEquation("cos(60-30)"));
    EXPECT_TRUE(validateEquation("tan(45*2)"));
    EXPECT_TRUE(validateEquation("log(100/10)"));
    EXPECT_TRUE(validateEquation("sqrt(16+9)"));
    EXPECT_TRUE(validateEquation("abs(-5-3)"));

    EXPECT_TRUE(validateEquation("sin(0)"));
    EXPECT_TRUE(validateEquation("cos(90)"));
    EXPECT_TRUE(validateEquation("tan(0)"));
    EXPECT_TRUE(validateEquation("log(1)"));
    EXPECT_TRUE(validateEquation("ln(1)"));
    EXPECT_TRUE(validateEquation("sqrt(0)"));
    EXPECT_TRUE(validateEquation("abs(0)"));
    EXPECT_TRUE(validateEquation("tan(45*log(10))"));
    EXPECT_TRUE(validateEquation("abs(-5-3)"));
    EXPECT_TRUE(validateEquation("sin(cos(tan(30)))"));


    EXPECT_TRUE(validateEquation("e"));
    EXPECT_TRUE(validateEquation("e^1"));
    EXPECT_TRUE(validateEquation("e^0"));
    EXPECT_TRUE(validateEquation("e^-1"));
    EXPECT_TRUE(validateEquation("e^.5"));
    EXPECT_TRUE(validateEquation("e^-0.5"));
    EXPECT_TRUE(validateEquation("e^e"));
    EXPECT_TRUE(validateEquation("e+1"));
    EXPECT_TRUE(validateEquation("e-1"));
    EXPECT_TRUE(validateEquation("e*2"));
    EXPECT_TRUE(validateEquation("e/2"));
    EXPECT_TRUE(validateEquation("2*e"));
    EXPECT_TRUE(validateEquation("10/e"));
    EXPECT_TRUE(validateEquation("e^2+e^3"));
    EXPECT_TRUE(validateEquation("-e^-2--e^-3"));
    EXPECT_TRUE(validateEquation("e^(1/2)"));
    EXPECT_TRUE(validateEquation("e^1/2+3"));

}


/*
Template:     EXPECT_FALSE(validateEquation(""));
*/
TEST(validateEquationTest, invalidInput)
{
    EXPECT_FALSE(validateEquation("1+1a"));
    EXPECT_FALSE(validateEquation("!2*3"));
    EXPECT_FALSE(validateEquation(""));
    EXPECT_FALSE(validateEquation(" "));
    EXPECT_FALSE(validateEquation("1++2"));
    EXPECT_FALSE(validateEquation("1 ++ 2"));
    EXPECT_FALSE(validateEquation("1+*2"));
    EXPECT_FALSE(validateEquation("1+2 "));
    EXPECT_FALSE(validateEquation("1+ 2"));
    EXPECT_FALSE(validateEquation("1 +2"));
    EXPECT_FALSE(validateEquation(" 1+2"));
    EXPECT_FALSE(validateEquation("+123"));
    EXPECT_FALSE(validateEquation("123+"));
	EXPECT_FALSE(validateEquation("123*"));
    EXPECT_FALSE(validateEquation("*123"));
    EXPECT_FALSE(validateEquation("/123"));
    EXPECT_FALSE(validateEquation("123/"));
    EXPECT_FALSE(validateEquation("("));
    EXPECT_FALSE(validateEquation(")"));
    EXPECT_FALSE(validateEquation("()"));
    EXPECT_FALSE(validateEquation("(1+2"));
    EXPECT_FALSE(validateEquation("1+2)"));
    EXPECT_FALSE(validateEquation("a+b"));
    EXPECT_FALSE(validateEquation("1+2+"));
    EXPECT_FALSE(validateEquation("1..2+3"));
    EXPECT_FALSE(validateEquation("1.2.3+4"));
    EXPECT_FALSE(validateEquation("1/0"));
    EXPECT_FALSE(validateEquation("2^"));
    EXPECT_FALSE(validateEquation("-"));
    EXPECT_FALSE(validateEquation("2*(3+4))"));
    EXPECT_FALSE(validateEquation("((2+3)"));
    EXPECT_FALSE(validateEquation("2*(3+())"));
	EXPECT_FALSE(validateEquation("5.%2"));
	EXPECT_FALSE(validateEquation("5%2."));
    EXPECT_FALSE(validateEquation("%5"));
    EXPECT_FALSE(validateEquation("5%"));
    EXPECT_FALSE(validateEquation("5.%2"));
    EXPECT_FALSE(validateEquation("12+%5"));
    EXPECT_FALSE(validateEquation("5%a"));
    EXPECT_FALSE(validateEquation("5%%2"));
    EXPECT_FALSE(validateEquation("5%+2"));
    EXPECT_FALSE(validateEquation("2+-"));        
    EXPECT_FALSE(validateEquation("2*-*3"));
    EXPECT_FALSE(validateEquation("sin()"));
    EXPECT_FALSE(validateEquation("cos(60"));
    EXPECT_FALSE(validateEquation("tan45)"));
    EXPECT_FALSE(validateEquation("log(100"));
    EXPECT_FALSE(validateEquation("ln2)"));
    EXPECT_FALSE(validateEquation("sqrt16)"));
    EXPECT_FALSE(validateEquation("abs(-5"));
    EXPECT_FALSE(validateEquation("sin(cos(30)"));
    EXPECT_FALSE(validateEquation("tan(log100))"));
    EXPECT_FALSE(validateEquation("sqrt(abs-9))"));
    EXPECT_FALSE(validateEquation("log(sqrt100)"));
    EXPECT_FALSE(validateEquation("3+sin45)"));
    EXPECT_FALSE(validateEquation("2*cos(60"));
    EXPECT_FALSE(validateEquation("tan45)-1"));
    EXPECT_FALSE(validateEquation("log100)/2"));
    EXPECT_FALSE(validateEquation("4*ln2)"));
    EXPECT_FALSE(validateEquation("sqrt16)+2"));
    EXPECT_FALSE(validateEquation("abs(-5-3"));
    EXPECT_FALSE(validateEquation("3+sin(cos(30)"));
    EXPECT_FALSE(validateEquation("2*tan(log100))"));
    EXPECT_FALSE(validateEquation("sqrt(abs-9))/3"));
    EXPECT_FALSE(validateEquation("log(sqrt100)-1"));
    EXPECT_FALSE(validateEquation("sin(30+cos(60)"));
    EXPECT_FALSE(validateEquation("sqrt(16/abs(-4)"));
    EXPECT_FALSE(validateEquation("log100+ln(2)"));
    EXPECT_FALSE(validateEquation("sin30+45)"));
    EXPECT_FALSE(validateEquation("cos60-30)"));
    EXPECT_FALSE(validateEquation("tan(45*2"));
    EXPECT_FALSE(validateEquation("log(100/10"));
    EXPECT_FALSE(validateEquation("sqrt(16+9"));
    EXPECT_FALSE(validateEquation("log(sqrt(abs(-16))))"));
    EXPECT_FALSE(validateEquation("sin(cos(tan(30))"));
    EXPECT_FALSE(validateEquation("log(sqrt(abs(-16))"));
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




string stackToString(std::stack<std::string> s) {
    std::ostringstream oss;
    while (!s.empty()) {
        oss << s.top() << " ";
        s.pop();
    }
    std::string result = oss.str();
    if (!result.empty()) {
        result.pop_back();  // Remove the trailing space
    }
    return result;
}




/*
Format:
	expectedStack = ReverseStack(createStack({expected}));
	actualStack = ReverseStack(createStack({actual}));
	EXPECT_EQ(shuntingYard(expectedStack), actualStack);


@notes:
    -EXPECT_EQ(shuntingYard(expectedStack), actualStack) << "actual stack " << stackToString(actualStack) << endl << "expected stack " << stackToString(expectedStack);
        This is how you go about error printing to see expected and actual. Cant just call testPrint since its a void that returns nothing.
        stackToString had to be made since it returns a string, which is printable using cout.
    -*******The way EXPECT_EQ compares stacks is by popping and comparing top elements. Loading stacks using ({}) loads the stack from
        left to right, bottom to top. BASICALLY RIGHT SIDE OF ({}) STACK IS THE TOP.
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


    expectedStack = ReverseStack(createStack({ "7", "-", "5", "+", "2" }));
    actualStack = ReverseStack(createStack({ "7", "5", "-", "2", "+" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "8", "+", "(", "3", "*", "2", ")", "-", "4" }));
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


    expectedStack = ReverseStack(createStack({ "sin", "(", "2", "+", "3", ")" }));
    actualStack = ReverseStack(createStack({ "2", "3", "+", "sin" }));
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "cos", "(", "90", ")" }));
    actualStack = createStack({ "cos", "90" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "tan", "(", "30", ")" }));
    actualStack = createStack({ "tan", "30" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "log", "(", "100", ")" }));
    actualStack = createStack({ "log", "100" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "ln", "(", "2", ")" }));
    actualStack = createStack({ "ln", "2" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "sqrt", "(", "4", ")" }));
    actualStack = createStack({ "sqrt", "4" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "abs", "(", "-5", ")" }));
    actualStack = createStack({ "abs", "-5" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "sin", "(", "cos", "(", "30", ")", ")" }));
    actualStack = createStack({ "sin", "cos", "30" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "tan", "(", "45", "*", "log", "(", "10", ")", ")" }));
    actualStack = createStack({ "tan", "*", "log", "10", "45" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "abs", "(", "-5", "-", "3", ")" }));
    actualStack = createStack({ "abs", "-", "3", "-5" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "sin", "(", "cos", "(", "tan", "(", "30", ")", ")", ")" }));
    actualStack = createStack({ "sin", "cos", "tan", "30" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);


    expectedStack = ReverseStack(createStack({ "sqrt", "(", "abs", "(", "-5", "+", "3", ")", ")" }));
    actualStack = createStack({ "sqrt", "abs", "+", "3", "-5" });
    EXPECT_EQ(shuntingYard(expectedStack), actualStack);
}



/*
Format: EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize("equation"))), answer);
        EXPECT_EQ(evaluateEquation(shuntingYard(Tokenize(""))), );
*/
TEST(evaluateEquationTest, validRadInput)
{
    
    double Result = 0.0;
    
    evaluateEquation(shuntingYard(Tokenize("1+2")), 0, Result);
    EXPECT_EQ(Result, 3.0);

    evaluateEquation(shuntingYard(Tokenize("3*4-5/6")), 0, Result);
	EXPECT_EQ(Result, 11.167);
   
    evaluateEquation(shuntingYard(Tokenize("(7+8)*9")), 0, Result);
    EXPECT_EQ(Result, 135.0);

    evaluateEquation(shuntingYard(Tokenize("10.5+3.2")), 0, Result);
    EXPECT_EQ(Result, 13.7);

    evaluateEquation(shuntingYard(Tokenize("2^3-4*(5+6)/7")), 0, Result);
    EXPECT_EQ(Result, 1.714);

    evaluateEquation(shuntingYard(Tokenize("-(3+4)")), 0, Result);
    EXPECT_EQ(Result, -7.0);

    evaluateEquation(shuntingYard(Tokenize("2+(3*(4/5)^6)-7")), 0, Result);
    EXPECT_EQ(Result, -4.214);

    evaluateEquation(shuntingYard(Tokenize("42")), 0, Result);
    EXPECT_EQ(Result, 42.0);

    evaluateEquation(shuntingYard(Tokenize("-.5+2")), 0, Result);
    EXPECT_EQ(Result, 1.5);

    evaluateEquation(shuntingYard(Tokenize("((2+3)*5)-6")), 0, Result);
    EXPECT_EQ(Result, 19.0);

    evaluateEquation(shuntingYard(Tokenize("2*(3+(4-5))")), 0, Result);
    EXPECT_EQ(Result, 4.0);

    evaluateEquation(shuntingYard(Tokenize("2*(3+(-5))")), 0, Result);
    EXPECT_EQ(Result, -4.0);

    evaluateEquation(shuntingYard(Tokenize("sin(30)")), 0, Result);
    EXPECT_EQ(Result, -0.988);

    evaluateEquation(shuntingYard(Tokenize("cos(45)")), 0, Result);
    EXPECT_EQ(Result, 0.525);

    evaluateEquation(shuntingYard(Tokenize("tan(60)")), 0, Result);
    EXPECT_EQ(Result, 0.320);

    evaluateEquation(shuntingYard(Tokenize("log(100)")), 0, Result);
    EXPECT_EQ(Result, 2.000);

    evaluateEquation(shuntingYard(Tokenize("ln(2.718)")), 0, Result);
    EXPECT_EQ(Result, 1.000);

    // Test cases for nested trigonometric functions
    evaluateEquation(shuntingYard(Tokenize("sin(cos(30))")), 0, Result);
    EXPECT_EQ(Result, 0.154);

    evaluateEquation(shuntingYard(Tokenize("tan(log(100))")), 0, Result);
    EXPECT_EQ(Result, -2.185);

    // Edge cases
    evaluateEquation(shuntingYard(Tokenize("sin(0)")), 0, Result);
    EXPECT_EQ(Result, 0.000);

    evaluateEquation(shuntingYard(Tokenize("sin(90)")), 0, Result);
    EXPECT_EQ(Result, 0.894);

    evaluateEquation(shuntingYard(Tokenize("cos(0)")), 0, Result);
    EXPECT_EQ(Result, 1.000);

    evaluateEquation(shuntingYard(Tokenize("cos(180)")), 0, Result);
    EXPECT_EQ(Result, -0.598);

    // Mixed trigonometric and arithmetic operations
    evaluateEquation(shuntingYard(Tokenize("sin(45)+cos(45)")), 0, Result);
    EXPECT_EQ(Result, 1.376);

    evaluateEquation(shuntingYard(Tokenize("tan(30)*log(100)")), 0, Result);
    EXPECT_EQ(Result, -12.811);

    evaluateEquation(shuntingYard(Tokenize("sin(60)/cos(30)")), 0, Result);
    EXPECT_EQ(Result, -1.976);
}


TEST(evaluateEquationTest, validDegInput)
{
    double Result = 0.0;

    evaluateEquation(shuntingYard(Tokenize("1+2")), 1, Result);
    EXPECT_EQ(Result, 3.0);

    evaluateEquation(shuntingYard(Tokenize("3*4-5/6")), 1, Result);
    EXPECT_EQ(Result, 11.167);

    evaluateEquation(shuntingYard(Tokenize("(7+8)*9")), 1, Result);
    EXPECT_EQ(Result, 135.0);

    evaluateEquation(shuntingYard(Tokenize("10.5+3.2")), 1, Result);
    EXPECT_EQ(Result, 13.7);

    evaluateEquation(shuntingYard(Tokenize("2^3-4*(5+6)/7")), 1, Result);
    EXPECT_EQ(Result, 1.714);

    evaluateEquation(shuntingYard(Tokenize("-(3+4)")), 1, Result);
    EXPECT_EQ(Result, -7.0);

    evaluateEquation(shuntingYard(Tokenize("2+(3*(4/5)^6)-7")), 1, Result);
    EXPECT_EQ(Result, -4.214);

    evaluateEquation(shuntingYard(Tokenize("42")), 1, Result);
    EXPECT_EQ(Result, 42.0);

    evaluateEquation(shuntingYard(Tokenize("-.5+2")), 1, Result);
    EXPECT_EQ(Result, 1.5);

    evaluateEquation(shuntingYard(Tokenize("((2+3)*5)-6")), 1, Result);
    EXPECT_EQ(Result, 19.0);

    evaluateEquation(shuntingYard(Tokenize("2*(3+(4-5))")), 1, Result);
    EXPECT_EQ(Result, 4.0);

    evaluateEquation(shuntingYard(Tokenize("2*(3+(-5))")), 1, Result);
    EXPECT_EQ(Result, -4.0);

    evaluateEquation(shuntingYard(Tokenize("sin(30)")), 1, Result);
    EXPECT_EQ(Result, 0.500);

    evaluateEquation(shuntingYard(Tokenize("cos(45)")), 1, Result);
    EXPECT_EQ(Result, 0.707);

    evaluateEquation(shuntingYard(Tokenize("tan(60)")), 1, Result);
    EXPECT_EQ(Result, 1.732);

    evaluateEquation(shuntingYard(Tokenize("log(100)")), 1, Result);
    EXPECT_EQ(Result, 2.000);

    evaluateEquation(shuntingYard(Tokenize("ln(2.718)")), 1, Result);
    EXPECT_EQ(Result, 1.000);

    // Test cases for nested trigonometric functions
    evaluateEquation(shuntingYard(Tokenize("sin(cos(30))")), 1, Result);
    EXPECT_EQ(Result, 0.015);

    evaluateEquation(shuntingYard(Tokenize("tan(log(100))")), 1, Result);
    EXPECT_EQ(Result, 0.035);

    // Edge cases
    evaluateEquation(shuntingYard(Tokenize("sin(0)")), 1, Result);
    EXPECT_EQ(Result, 0.000);

    evaluateEquation(shuntingYard(Tokenize("sin(90)")), 1, Result);
    EXPECT_EQ(Result, 1.000);

    evaluateEquation(shuntingYard(Tokenize("cos(0)")), 1, Result);
    EXPECT_EQ(Result, 1.000);

    evaluateEquation(shuntingYard(Tokenize("cos(180)")), 1, Result);
    EXPECT_EQ(Result, -1.000);

    // Mixed trigonometric and arithmetic operations
    evaluateEquation(shuntingYard(Tokenize("sin(45)+cos(45)")), 1, Result);
    EXPECT_EQ(Result, 1.414);

    evaluateEquation(shuntingYard(Tokenize("tan(30)*log(100)")), 1, Result);
    EXPECT_EQ(Result, 1.155);

    evaluateEquation(shuntingYard(Tokenize("sin(60)/cos(30)")), 1, Result);
    EXPECT_EQ(Result, 1.000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}