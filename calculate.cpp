/*
@author: Kendric Agdaca
@since: 06/06/24 ->

@purpose:
	-This is the main driver of the Scientific Calculator. It contains all the functions that are used to evaluate the equation.


*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include "calculate.h"
using namespace std;

/*
@purpose:
	-Prints the stack passed into it.
@param:
	-stack<string> Stack: The stack to be printed. 

@return:
	-None. 

@notes:
	-The stack has already been reversed so it just needs to be printed.
*/
void testPrint(stack<string> Stack)
{
	while (!Stack.empty())
	{
		cout << '"' << Stack.top() << '"' << ',' << " ";
		Stack.pop();
	}
	cout << endl;
}



/*
@purpose:
	-Checks if a character is an operator.

@param:
	-char Token: Character to be checked.

@return:
	-Returns true if the character is an operator.
	-Returns false if the character is not an operator.

@notes:
	-
*/
bool isOperator(char Token)
{
	if (Token == '+' || Token == '-' || Token == '*' || Token == '/' || Token == '^' || Token == '%')
	{
		return true;
	}
	else
	{
		return false;
	}
}



/*
@purpose:
	-Checks if a Token is a trig function.

@param:
	-string str: Token to be checked.

@return:
	-Returns true if the token is a trig function.
	-Returns false if the token is not a trig function.

@notes:
	-
*/
bool isFunction(const string& str) {
	static const unordered_set<string> functions = { "sin", "cos", "tan", "log", "ln", "sqrt", "abs" };

	if (functions.find(str) != functions.end()) {
		return true;
	}
	else {
		return false;
	}
}



/*
@purpose:
	-Reverse the stack passed into it. This is used in Shunting Yard and Tokenize function because after each function call, the equation within the stacks is in reverse order.

@param:
	-stack<string> tokenStack: Stack that will be reversed.

@return:
	-Return reversed stack.

@notes:
	-This was created since stack reversing was used in more than one function. Cleans up Shunting Yard and Tokenize functions.
*/
stack<string> ReverseStack(stack<string> tokenStack)
{
	stack<string> reverseStack;
	while (!tokenStack.empty())
	{
		reverseStack.push(tokenStack.top());
		tokenStack.pop();
	}

	return reverseStack;
}



/*
@purpose:
	-Validates user input to make sure all operators are used correctly and parentheses are balanced.

@param:
	-string &input: User equation input.

@return:
	-Returns true if equation is valid, prints error message and returns false if equation is invalid.

@notes:
	-
*/
bool validateInput(const string& input) {
	stack<char> Parentheses;  // Stack to track parentheses for balancing
	bool expectOperator = false;
	bool allowUnary = true;
	bool hasDecimal = false;
	string Token;
	size_t i = 0;

	if (input.empty())
	{
		cout << "Error: Empty input. Please try again." << endl;
		return false;
	}

	if (input.length() == 1 && isOperator(input[0]))
	{
		cout << "Error: Single operator detected. Please try again." << endl;
		return false;
	}

	while (i < input.length())
	{
		char ch = input[i];

		if (isspace(ch))
		{
			cout << "Error: Whitespace detected. Please try again." << endl;
			return false;
		}

		// Handle numbers, operators, and parentheses. In this context, ch is the current character and input[i] is the next character.
		if (isdigit(ch) || ch == '.')
		{
			hasDecimal = false;

			if (ch == '.')
			{
				hasDecimal = true;
			}
			i++;

			if (ch == '.' && (i >= input.length() || !isdigit(input[i])))//Ensures that a decimal is followed by a number.
			{
				cout << "Error: Invalid decimal usage." << endl;
				return false;
			}

			while (i < input.length() && (isdigit(input[i]) || input[i] == '.'))//Prevent multiple decimals.
			{
				if (input[i] == '.')
				{
					if (hasDecimal)
					{
						cout << "Error: Multiple decimal points detected. Please try again." << endl;
						return false;
					}
					hasDecimal = true;
				}
				i++;
			}

			expectOperator = true; // After a number, we expect an operator next but not unary.
			allowUnary = false;
		}

		// Handle operators
		else if (isOperator(ch))
		{
			if (ch == '-' && allowUnary)
			{
				i++;
				continue;
			}

			if (expectOperator == false)
			{
				cout << "Error: Operator detected at the beginning of the expression (except unary minus). Please try again." << endl;
				return false;
			}

			if (ch == '/' && i + 1 < input.length() && input[i + 1] == '0')
			{
				cout << "Error: Division by zero detected. Please try again." << endl;
				return false;
			}

			if (isOperator(input.back()) || input.back() == '.')
			{
				cout << "Error: Operator detected at the end of the expression. Please try again." << endl;
				return false;
			}

			if (ch == '%')
			{
				//Checks that % has an integer in both operands.
				if (i == 0 || (!isdigit(input[i - 1]) && input[i - 1] != ')')
					|| (i + 1 >= input.length()
						|| (!isdigit(input[i + 1]) && input[i + 1] != '(')))
				{
					cout << "Error: Invalid use of modulus operator." << endl;
					return false;
				}
			}

			expectOperator = false;
			allowUnary = true; // After an operator, unary is allowed
			i++;
		}

		else if (ch == '(')
		{
			Parentheses.push(ch);
			expectOperator = false; // After '(', we do not expect an operator but allow unary.
			allowUnary = true;
			i++;
		}

		else if (ch == ')')
		{
			if (Parentheses.empty() || !expectOperator)
			{
				cout << "Error: Unbalanced parentheses. Please try again." << endl;
				return false; // Invalid if no matching '(' or unexpected ')'
			}

			Parentheses.pop();
			expectOperator = true; // After ')', we expect an operator but not unary
			allowUnary = false;
			i++;
		}



		//handles trig functions. 
		else if (isalpha(ch)) 
		{
			while (i < input.length() && isalpha(input[i])) //First load all letters of the trig function into the token.
			{
				Token += input[i];
				i++;
			}

			if (isFunction(Token))//Check if the token is a valid trig function. If its valid BUT a ( doesn't follow it, return false.
			{
				if (i >= input.length() || input[i] != '(') 
				{
					cout << "Error: Invalid use of function " << Token << ". Please try again." << endl;
					return false;
				}

				Parentheses.push('(');//If completely valid, check for balanced parentheses and update expectOperator and allowUnary accordingly.
				i++;
				expectOperator = false;
				allowUnary = true;
			}
			
			
			else 
			{
				cout << "Error: Invalid character detected. Please try again." << endl;
				return false;
			}

			Token.clear();//This is necessary for checking for multiple uses of trig functions or nested trig functions.
		}

		else
		{
			cout << "Error: Invalid character. Please try again." << endl;
			return false;
		}
	}


	if (!Parentheses.empty())
	{
		cout << "Error: Unbalanced parentheses. Please try again." << endl;
		return false;
	}

	
	return true;// Input is valid if all parentheses are balanced and we end expecting an operator
}



/*
@purpose:
	-Tokenize user inputted equation.

@param:
	-string& Equation: User inputted equation that will be tokenized.

@return:
	-Return stack of tokenized equation.

@notes:
	-Tokenization is useful for breaking down strings of text into invidual components (tokens) as opposed to individual characters.
		-EX: "Hello, World!" -> ["Hello", ",", "World", "!"]
	-size_t used for i counter variable. Its apparently good practice to use size_t instead of int for counters.

@example:
	-(3+4) -> ["-", "(", "3", "+", "4", ")"]
	-.5+1 -> ["-0.5", "+", "1"]
*/
stack<string>Tokenize(const string& Equation)
{
	stack<string>tokenStack;
	string Token;
	size_t i = 0;
	bool hasDecimal = false;

	while (i < Equation.length())
	{
		//check for decimal point and operand. 
		if (isdigit(Equation[i]) || Equation[i] == '.')
		{
			Token.clear();

			//Check if decimal has a digit before it. If no, add a '0'. EX: .5 -> 0.5
			if (Equation[i] == '.' && (i == 0 || !isdigit(Equation[i - 1])))
			{
				Token += '0';
			}

			//If "." detected, append all numbers to the right of the decimal point to the left of the decimal point to form the whole decimal number.
			//EX: 12.345, parse 345 and add it to 12. to form the full 12.345
				//IF SOMETHING GOES WRONG IN TESTING P2, LOOK HERE FIRST.
			while (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
			{
				Token += Equation[i];
				i++;
			}

			tokenStack.push(Token);
		}

		//Handles determining the context of "-" and checking if its unary or subtraction.
		else if (Equation[i] == '-') {
			// Check to see if '-' is at the start or follows an open parenthesis or another operator
			if (i == 0 || Equation[i - 1] == '(' || Equation[i - 1] == '+' || Equation[i - 1] == '-' || Equation[i - 1] == '*' || Equation[i - 1] == '/' || Equation[i - 1] == '^' || Equation[i - 1] == '%')
			{
				Token = "-";
				i++;

				// If the next character is a digit or a decimal point, it is a negative number. Push '-' and the rest of the number to the stack
				if (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
				{
					hasDecimal = false;

					//Check if decimal has a digit before it. If no, add a '0'. EX: .5 -> 0.5
					if (Equation[i] == '.' && (i == 0 || !isdigit(Equation[i - 1])))
					{
						Token += '0';
					}

					while (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
					{
						if (Equation[i] == '.' && hasDecimal)
						{
							break;
						}

						if (Equation[i] == '.')
						{
							hasDecimal = true;
						}

						Token += Equation[i];
						i++;
					}

					tokenStack.push(Token);
				}

				// If the next character is '(', it's a unary operator for an expression
				else if (i < Equation.length() && Equation[i] == '(')
				{
					tokenStack.push("-");
					tokenStack.push("(");
					i++;
				}
			}

			else
			{
				// Otherwise, it is subtraction. Push only '-' to the stack
				tokenStack.push(std::string(1, Equation[i]));
				i++;
			}
		}

		//if current character is an operator or parenthesis, add them to the Token Stack.
		else if (Equation[i] == '+' || Equation[i] == '-' || Equation[i] == '*' || Equation[i] == '/' || Equation[i] == '%' || Equation[i] == '^' || Equation[i] == '(' || Equation[i] == ')')
		{
			tokenStack.push(string(1, Equation[i]));
			i++;
		}

		//skip whitespace.
		else i++;
	}

	//Final post fix equation is currently reversed, reverse it and return it.
	return ReverseStack(tokenStack);
}



/*
@purpose:
	-Check precedence of an operator.

@param:
	-string& Token: Operator of precedence to be checked.

@return:
	-Returns int value according to precedence of operator.

@notes:
	- +, -, *, /, and % all have left associativity, which means they are evaluated from left to right. Only ^ has right associativity.
*/
int Precedence(const string& Token)
{
	if (Token == "+" || Token == "-") return 1;

	else if (Token == "*" || Token == "/" || Token == "%") return 2;

	else if (Token == "^") return 3;

	else return 0;
}



/*
@purpose:
	-Convert user inputted equation from infix to postfix notation.
		-EX: 1+2*3 -> 1 2 3 * +
@param:
	-stack<string> tokenStack: User inputted equation in infix notation.

@return:
	-Returns the equation in postfix notation in a stack, ready to be fed directly into the postfix evaluation / calculator function.

@notes:
	- top = look at the top of the stack.
	- pop = remove the top of the stack.
	- push = add an element to the top of the stack.
*/
stack<string> shuntingYard(stack<string> tokenStack)
{
	stack<string> postFixStack;
	stack<string> operatorStack;
	string Token;//Stack index ref point

	while (!tokenStack.empty())
	{
		Token = tokenStack.top();
		tokenStack.pop();

		//If current token is a positive or negative operand, push to postfix stack.
		if (isdigit(Token[0]) || (Token.length() > 1 && Token[0] == '-' && isdigit(Token[1])))
		{
			postFixStack.push(Token);
		}

		//If current token is an "(", push to operator stack.
		else if (Token == "(")
		{
			operatorStack.push(Token);
		}

		//If current token is an ")", pop until matching "(" is found. Once found, pop "(" then continue.
		else if (Token == ")")
		{
			while (operatorStack.top() != "(")
			{
				postFixStack.push(operatorStack.top());
				operatorStack.pop();
			}

			operatorStack.pop();
		}

		//If reach here, token is an operator. Pop the operator stack and push to postfix stack until an operator with higher precedence is found.
		else
		{
			while (!operatorStack.empty() && Precedence(Token) <= Precedence(operatorStack.top()) && (Token != "^" || Precedence(operatorStack.top()) > Precedence(Token)))
			{
				postFixStack.push(operatorStack.top());
				operatorStack.pop();
			}

			operatorStack.push(Token);
		}
	}

	//IF there are operators left in the operator stack, push them to the postfix stack.
	while (!operatorStack.empty())
	{
		postFixStack.push(operatorStack.top());
		operatorStack.pop();
	}

	//Final post fix equation is currently reversed, reverse and return it.
	return ReverseStack(postFixStack);
}



/*
@purpose:
	-Perform an operation on two operands.

@param:
	-string& Token: Operator of precedence to be checked.
	-double Operand1: First operand.
	-double Operand2: Second operand.

@return:
	-Returns a double of the result of the operation.

@notes:
	-This was created to make the Calculator function more readable.
	-The return 0.0 will NEVER be reached due to guard clauses in the validate input function but it was still included as good practice.
*/
double performCalculation(const string& Token, double Operand1, double Operand2)
{

	if (Token == "+") return Operand1 + Operand2;

	else if (Token == "-") return Operand1 - Operand2;

	else if (Token == "*") return Operand1 * Operand2;

	else if (Token == "/") return Operand1 / Operand2;

	else if (Token == "%") return fmod(Operand1, Operand2);

	else if (Token == "^") return pow(Operand1, Operand2);

	return 0.0;
}



/*
@purpose:
	-Calculates the post fix equation.

@param:
	-stack<string> postFixStack: User inputted equation in postfix notation.

@return:
	-Returns a double of the result of the postfix equation to the main function to be printed.

@notes:
	-stod = String to double.
*/
double evaluateEquation(stack<string> postFixStack)
{
	stack<double> evalStack;
	string Token;
	double Operand1 = 0.0;
	double Operand2 = 0.0;
	double Result = 0.0;

	//Start eval iterating through the post fix stack by first poping off the top of the stack.
	while (!postFixStack.empty())
	{
		Token = postFixStack.top();
		postFixStack.pop();

		//Check if current token is a number, negative number, or number with a decimal. If so, convert it to a double data type and push it to the eval stack.
		if (isdigit(Token[0]) || Token[0] == '.' || (Token[0] == '-' && (isdigit(Token[1]) || Token[1] == '.')))
		{
			evalStack.push(stod(Token));
		}

		//Pop the top of the stack twice to load the operands. If the current token is a "-" and the eval stack is empty, it is unary minus and push as such. Otherwise, perform the operation and push the result to the eval stack.
		else
		{
			Operand2 = evalStack.top();
			evalStack.pop();

			if (Token == "-" && evalStack.empty())
			{
				evalStack.push(-Operand2); // Handle unary minus
			}

			else
			{
				Operand1 = evalStack.top(); evalStack.pop();
				Result = performCalculation(Token, Operand1, Operand2);
				evalStack.push(Result);
			}
		}
	}

	Result = round(evalStack.top() * 1000) / 1000;//round to 3 decimal places.

	return Result;
}