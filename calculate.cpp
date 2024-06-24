
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
	static const unordered_set<string> functions = { "sin()", "cos()", "tan()", "log()", "ln()", "sqrt()", "abs()" };

	if (functions.find(str) != functions.end()) {
		return true;
	}
	else {
		return false;
	}
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

	// Input is valid if all parentheses are balanced and we end expecting an operator
	return true;
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


