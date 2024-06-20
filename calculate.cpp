/*
Tokenize
	-if input such as .5 detected, add a 0 to the left
	-if ~~ detected, convert to positive number.

*/
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
	static const unordered_set<string> functions = { "sin", "cos", "tan", "log", "ln", "sqrt", "abs" };

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
bool validateInput(const string& input)
{
	stack<char> Parentheses;  // Stack to track parentheses for balancing
	bool expectOperator = false;   // Flag to track if we expect an operator next
	bool allowUnary = true;        // Flag to allow unary minus
	bool hasDecimal = false;       // Flag to track if a decimal point has been seen
	string Token;
	size_t i = 0;                  // Index for iterating through the input string




	if (input.empty())//Empty input check.
	{
		cout << "Error: Empty input. Please try again." << endl;
		return false;
	}



	if (input.length() == 1 && isOperator(input[0]))//Single operator check.
	{
		cout << "Error: Single operator detected. Please try again." << endl;
		return false;
	}



	while (i < input.length())
	{
		char ch = input[i];

		if (isspace(ch))//Whitespace check.
		{
			cout << "Error: Whitespace detected. Please try again." << endl;
			return false;
		}



		// Handle numbers, operators, and parentheses
		if (isdigit(ch) || ch == '.')
		{
			hasDecimal = false;
			if (ch == '.')//Used for detecting multiple decimal points. Same as hasDecimal = (ch == '.');
			{
				hasDecimal = true;
			}
			i++;
			
			if (ch == '.' && (i >= input.length() || !isdigit(input[i]))) 
			{
				cout << "Error: Invalid decimal usage." << endl;
				return false; 
			}

			while (i < input.length() && (isdigit(input[i]) || input[i] == '.')) 
			{
				if (input[i] == '.') 
				{
					if (hasDecimal) 
					{
						std::cout << "Error: Multiple decimal points detected. Please try again." << std::endl;
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
			if (ch == '-' && allowUnary)// Unary minus is allowed, proceed to the next character
			{
				i++;
				continue;
			}

			if (!expectOperator)//error print if non operator (minus unary minus) is detected.
			{
				cout << "Error: Operator detected at the beginning of the expression (except unary minus). Please try again." << endl;
				return false;
			}

			if (ch == '/' && i + 1 < input.length() && input[i + 1] == '0')//Division by zero check.
			{
				cout << "Error: Division by zero detected. Please try again." << endl;
				return false;
			}

			if (isOperator(input.back()))
			{
				cout << "Error: Operator detected at the end of the expression. Please try again." << endl;
				return false;
			}

			if (ch == '%') {
				// Ensure '%' is followed by a digit and is not preceded by a decimal point
				if (i > 0 && input[i - 1] == '.') return false; // Prevent '5.%2'
				if (i + 1 < input.length() && !isdigit(input[i + 1])) return false; // Ensure valid usage of %
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


		//Handle trig functions.
		else if (isalpha(ch))
		{
			//Read trig function name.
			while (i < input.length() && isalpha(input[i]))
			{
				Token += input[i];
				i++;
			}

			if (isFunction(Token))
			{
				// If it's a recognized function, it must be followed by '('
				if (i >= input.length() || input[i] != '(')
				{
					cout << "Error: Invalid use of trig function. Please try again." << endl;
					return false;
				}

				Parentheses.push('(');
				i++;
				expectOperator = false; // After a function, we do not expect an operator but allow unary
				allowUnary = true;
			}

			else
			{
				cout << "Error: Invalid trig function. Please try again." << endl;
				return false; // Invalid token
			}
		}

		else
		{
			cout << "Error: Invalid character. Please try again." << endl;
			return false;
		}
	}


	if (!Parentheses.empty()) //Check for unmatched left parentheses
	{
		cout << "Error: Unbalanced parentheses. Please try again." << endl;
		return false;
	}
	// Input is valid if all parentheses are balanced and we end expecting an operator
	return true;
}