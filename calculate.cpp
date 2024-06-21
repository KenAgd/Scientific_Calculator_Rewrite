
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include "calculate.h"
using namespace std;

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


// Function to check if a string is a valid function
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


*/
// Function to validate user input
//do not to input manipulation in this function, this is only for validation. Any input manipulation should be done in the tokenize function
//% requires an integer in both operands

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
Tokenize
	-if input such as .5 detected, add a 0 to the left
	-if -- or -(-num)) detected, convert to positive number.


stack<string> Tokenize(const string& input)
{

}*/