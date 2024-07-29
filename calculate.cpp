/*
@author: Kendric Agdaca
@since: 06/06/24 ->

@purpose:
	-This is the main driver of the Scientific Calculator. It contains all the functions that are used to evaluate the equation.

@purpose:

@param:

@return:

@notes:
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <sstream> 
#include <iomanip> 
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
	-Checks if a character is an operator.

@param:
	-char Token: Character to be checked.

@return:
	-Returns true if the character is a valid operator.
	-Returns false if the character is an invalid operator.

@notes:
	-
*/
bool isOperator(char Token)
{
	return (Token == '+' || Token == '-' || Token == '*' || Token == '/' || Token == '^' || Token == '%');
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
	-I chose to use unordered_set instead of unordered_map because unordered_set automatically assigns a key to each value whereas unordered_map does not.
		Both use hashing functions and both have the same time complexity (O(1)), unordered_set just saves me time and lines.
*/
bool isFunction(const string& str) {
	static const unordered_set<string> functions = { "sin", "cos", "tan", "log", "ln", "sqrt", "abs", "-sin", "-cos", "-tan", "-log", "-ln", "-sqrt", "-abs" };
	return functions.find(str) != functions.end();
}



/*
@purpose:
	-Ensures proper usage of decimal points.

@param:
	-const string& Equation: User equation input.
	-size_t& i: Current index of the character in the input.
	-const char& Token: Current character in the input.
	-bool& expectOperator: Determine if we expect an operator next.
	-bool& allowUnary: Determine if we allow unary operators.

@return:
	-Returns true if the decimal point is valid. If invalid, error print and return false.
	-i, expectOperator, and allowUnary are updated and returned via pass-by-reference.

@notes:
	-Aux function to validateEquation.
	-Checks for multiple decimal points and if a decimal point is followed by a number.
*/
bool validateDecimalPoint(const string& Equation, size_t& i, const char& Token, bool& expectOperator, bool& allowUnary)
{
	bool hasDecimal = false;

	//Keeps track of number of decimals. Prevents multiple decimals.
	if (Token == '.')hasDecimal = true;
	i++;


	//Ensures that a decimal is followed by a number.
	if (Token == '.' && (i >= Equation.length() || !isdigit(Equation[i])))
	{
		cout << "Error: Invalid decimal usage." << endl;
		return false;
	}


	//Check for multiple decimal points.
	while (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
	{
		if (Equation[i] == '.')
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
	return true;
}



/*
@purpose:
	-Ensures proper usage of operators (+, -, *, /, ^, %).

@param:
	-const string& Equation: User equation input.
	-size_t& i: Current index of the character in the input.
	-const char& Token: Current character in the input.
	-bool& expectOperator: Determine if we expect an operator next.
	-bool& allowUnary: Determine if we allow unary operators.

@return:
	-Returns true if the operator is valid. If invalid, error print and return false.
	-i, expectOperator, and allowUnary are updated and returned via pass-by-reference.

@notes:
	-Aux function to validateEquation.
	-Checks for multiple operators in a row, if an operator is preceded/followed by a number, if theres an operator at the beginning or end of the equation,
		proper usage of modulo, undefined behavior/NaN, and division by zero.
*/
bool validateOperator(const string& Equation, size_t& i, const char& Token, bool& expectOperator, bool& allowUnary)
{
		if (expectOperator == false)
		{
			cout << "Error: Invalid operator usage. Please try again." << endl;
			return false;
		}


		//Prevent division by zero.
		if (Token == '/' && i + 1 < Equation.length() && Equation[i + 1] == '0')
		{
			cout << "Error: Division by zero detected. Please try again." << endl;
			return false;
		}


		//Check for if there is an operator at the beginning or end of the equation.
		if (isOperator(Equation.back()) || Equation.back() == '.')
		{
			cout << "Error: Invalid operator usage. Please try again." << endl;
			return false;
		}


		//Ensure proper usage of modulo by checking that % has an integer in both operands.
		if (Token == '%')
		{
			if (i == 0 || (!isdigit(Equation[i - 1]) && Equation[i - 1] != ')')
				|| (i + 1 >= Equation.length()
					|| (!isdigit(Equation[i + 1]) && Equation[i + 1] != '(')))
			{
				cout << "Error: Invalid use of modulus operator." << endl;
				return false;
			}
		}


		//Ensure proper usage of exponent by preventing 0^0 or 0^-1.
		if (Token == '^')
		{
			//First check if incrementor is within the equation length memory bounds and then check for undefined behavior.
			if (i + 1 < Equation.length() && i - 1 >= 0)
			{
				if (Equation[i - 1] == '0' && Equation[i + 1] == '0')
				{
					cout << "Error: Undefined behavior (0^0). Please try again." << endl;
					return false;
				}
				
				if (Equation[i - 1] == '0' && (Equation[i + 1] == '-' && Equation[i + 2] == '1'))
				{
					cout << "Error: Undefined behavior (0^-1). Please try again." << endl;
					return false;
				}
			}
		}



		expectOperator = false;
		allowUnary = true; // After an operator, unary is allowed
		i++;
	
	return true;
}



/*
@purpose:
	-Ensures proper usage and balancing of parentheses.

@param:
	-const string& Equation: User equation input.
	-size_t& i: Current index of the character in the input.
	-const char& Token: Current character in the input.
	-bool& expectOperator: Determine if we expect an operator next.
	-bool& allowUnary: Determine if we allow unary operators.
	-stack<char>& Parentheses: Parentheses stack.

@return:
	-Returns true if the parenthesis are valid. If invalid, error print and return false.
	-i, expectOperator, Parentheses, and allowUnary are updated and returned via pass-by-reference.

@notes:
	-Prevents juxtaposition multiplication.
*/
bool validateParentheses(const string& Equation, size_t& i, const char& Token, bool& expectOperator, bool& allowUnary, stack<char>& Parentheses)
{
	if (Token == '(')
	{
		//Prevent digits before '('.
		if (i > 0 && isdigit(Equation[i - 1]))
		{
			cout << "Error: Juxtaposition multiplication detected. Please try again." << endl;
			return false;
		}

		else
		{
			Parentheses.push(Token);
			expectOperator = false; // After '(', we do not expect an operator but allow unary.
			allowUnary = true;
			i++;
		}
	}


	else if (Token == ')')
	{	
		//Handle parenthesis balancing.
		if (Parentheses.empty() || !expectOperator)
		{
			cout << "Error: Unbalanced parentheses. Please try again." << endl;
			return false; // Invalid if no matching '(' or unexpected ')'
		}


		//Prevent a number, decimal point, or '(' from following a ')'.
		else if (i + 1 < Equation.length() && (isdigit(Equation[i + 1]) || Equation[i + 1] == '.' || Equation[i + 1] == '('))
		{
			cout << "Error: Juxtaposition multiplication detected. Please try again." << endl;
			return false;
		}

		else
		{
			Parentheses.pop();
			expectOperator = true; // After ')', we expect an operator but not unary
			allowUnary = false;
			i++;
		}
	}
}



/*
@purpose:
	-Ensures proper usage of Euler's number 'e'.

@param:
	-const string& Equation: User equation input.
	-size_t& i: Current index of the character in the input.
	-bool& expectOperator: Determine if we expect an operator next.
	-bool& allowUnary: Determine if we allow unary operators.

@return:
	-Returns true if Eulers number is valid. If invalid, error print and return false.
	-i, expectOperator, and allowUnary are updated and returned via pass-by-reference.

@notes:
	-Aux function to validateEquation.
	-Checks if 'e' is preceded by a digit or decimal point, if 'e' is followed by a digit or decimal point, if 'e' is followed by any letter.
*/
bool validateEuler(const string& Equation, size_t& i, bool& expectOperator, bool& allowUnary)
{
	// Check if 'e' is preceded by a digit or decimal point.
	if (i > 0 && (isdigit(Equation[i - 1]) || Equation[i - 1] == '.'))
	{
		cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
		return false;
	}

	// Check if 'e' is followed by a digit or decimal point.
	if (i + 1 < Equation.length() && (isdigit(Equation[i + 1]) || Equation[i + 1] == '.'))
	{
		cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
		return false;
	}

	// Check if 'e' is followed by any letter.
	if (i + 1 < Equation.length() && isalpha(Equation[i + 1]))
	{
		cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
		return false;
	}

	i++;
	expectOperator = true;//After 'e', we can expect an operator.
	allowUnary = false;
	return true;
}



/*
@purpose:
	-Checks for proper use of "functions" (trig, log, radical, and algebraic).

@param:
	-const string& Equation: User equation input.
	-size_t& i: Current index of the character in the input.
	-bool& expectOperator: Determine if we expect an operator next.
	-bool& allowUnary: Determine if we allow unary operators.
	-stack<char>& Parentheses: Stack of parentheses, used to check for balanced parentheses.

@return:
	-Returns true if function is valid. If invalid, error print and return false.

@notes:
	-Aux function to validateEquation.
	-Checks if the token is a valid trig function, for balanced parentheses, for juxtiposition multiplication, and for undefined/NaN behavior.
	.sin(30) and sin(30). (or similar type inputs) are handled either by validateDecimalPoint or validateParentheses.
	-After loading all letters of the trig function into the token, Equation[i] now sits at the '(' of the function.
*/
bool validateFunctions(const string& Equation, size_t& i, bool& expectOperator, bool& allowUnary, stack<char>& Parentheses)
{
	string functionToken;
	size_t initialPosition = i;

	//First load all letters of the trig function into the token.
	while (i < Equation.length() && isalpha(Equation[i]))
	{
		functionToken += Equation[i];
		i++;
	}

	//Check if the token is a valid trig function.
	if (isFunction(functionToken))
	{
		//Prevent juxtiposition multiplication. Ex: (3+4)sin(30) or 30sin(30).
		if (initialPosition > 0 && (isdigit(Equation[initialPosition - 1]) || Equation[initialPosition - 1] == ')'))
		{
			cout << "Error: Juxtaposition multiplication detected. Please try again." << endl;
			return false;
		}


		//Ensure that a '(' follows the function.
		if (i >= Equation.length() || Equation[i] != '(')
		{
			cout << "Error: Invalid use of function. Please try again." << endl;
			return false;
		}


		//Prevent Logarithm undefined/NaN behavior such as log/ln(0) and log/ln(negative number).
		if (functionToken == "log" || functionToken == "ln")
		{
			if (i + 1 < Equation.length() && Equation[i + 1] == '0')
			{
				cout << "Error: Undefined Behavior (Logarithm of 0). Please try again." << endl;
				return false;
			}


			if (i + 2 < Equation.length() && (Equation[i + 1] == '-' && (isdigit(Equation[i + 2] || Equation[i + 2] == 'e'))))
			{
				cout << "Error: Undefined Behavior (Logarithm of Negative Numbers). Please try again." << endl;
				return false;
			}
		}


		//Prevent Square Root undefined/NaN behavior such as sqrt(negative number).
		if (functionToken == "sqrt" && (i + 1 < Equation.length() && Equation[i + 1] == '-'))
		{
			cout << "Error: Undefined Behavior (Square Root of Negative Number). Please try again." << endl;
			return false;
		}


		//if (functionToken == "tan")




		Parentheses.push('(');//If completely valid, check for balanced parentheses and update expectOperator and allowUnary accordingly.
		i++;
		expectOperator = false;
		allowUnary = true;
	}


	else
	{
		cout << "Error: Invalid alphabet char detected. Please try again." << endl;
		return false;
	}

	functionToken.clear();//This is necessary for checking for multiple uses of trig functions or nested trig functions.
}



/*
@purpose:
	-Validates user input to make sure all operators are used correctly and parentheses are balanced.

@param:
	-string &Equation: User equation input.

@return:
	-Returns true if equation is valid, prints error message and returns false if equation is invalid.

@notes:
	-This function checks for:
		-Empty input.
		-Use of whitespace.
		-Proper usage of decimal point, operators, Eulers number, and functions.
		-Balanced parentheses.
		-Division by 0.
		-Detects minus vs unary minus.
	-In this context, ch is the current character and input[i] is the next character.
	-This function could be refactored and compacted to be a lot smaller if I just used throw error function instead of error printing
		each error and of what type BUT I want the user to know what exactly is invalid about their input.
*/

bool validateEquation(const string& Equation) {
	stack<char> Parentheses;  // Stack to track parentheses for balancing
	char Token;
	bool expectOperator = false;
	bool allowUnary = true;
	size_t i = 0;


	if (Equation.empty())
	{
		cout << "Error: Empty Equation. Please try again." << endl;
		return false;
	}


	//Prevents single operator Equations.
	if (Equation.length() == 1 && isOperator(Equation[0]))
	{
		cout << "Error: Single operator detected. Please try again." << endl;
		return false;
	}


	while (i < Equation.length())
	{
		Token = Equation[i];

		//Handle whitespace.
		if (isspace(Token))
		{
			cout << "Error: Whitespace detected. Please try again." << endl;
			return false;
		}
		

		//Handle decimal points.
		else if (isdigit(Token) || Token == '.')
		{
			if (!validateDecimalPoint(Equation, i, Token, expectOperator, allowUnary)) return false;
		}


		//Handle operators
		else if (isOperator(Token))
		{
			//If current token is '-' and we can expect an unary minus, increment to next token to ensure its a number.
			if (Token == '-' && allowUnary)
			{
				i++;
				continue;
			}

			if (!validateOperator(Equation, i, Token, expectOperator, allowUnary)) return false;
		}



		else if (Token == '(' || Token == ')')
		{
			if (!validateParentheses(Equation, i, Token, expectOperator, allowUnary, Parentheses)) return false;
		}


		//Check for Euler's number 'e'.
		else if (Token == 'e')
		{
			if (!validateEuler(Equation, i, expectOperator, allowUnary)) return false;
		}


		//Handles trig functions. 
		else if (isalpha(Token))
		{
			if (!validateFunctions(Equation, i, expectOperator, allowUnary, Parentheses)) return false;
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


	return true;// Equation is valid if all parentheses are balanced and we end expecting an operator
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
		EX: "Hello, World!" -> ["Hello", ",", "World", "!"]
	-size_t used for i counter variable. Its apparently good practice to use size_t instead of int for counters.
	-string() used to convert int to string. Its not like type casting in C, its a "constructor" where the first parameter determines how many times to repeat the second parameter.

@example:
	-(3+4) -> ["-", "(", "3", "+", "4", ")"]
	-.5+1 -> ["-0.5", "+", "1"]
	12.345, parse 345 and add it to 12. to form the full 12.345
*/
stack<string> Tokenize(const string& Equation)
{
	stack<string> tokenStack;
	string Token;
	size_t i = 0;
	bool hasDecimal = false;

	while (i < Equation.length())
	{
		//Handle numbers, decimal numbers, and functions.
		if (isdigit(Equation[i]) || Equation[i] == '.' || isalpha(Equation[i]))
		{
			Token.clear();
			
			//If a decimal that is preceded by a number is detected, add a 0 to the front. EX: .5 -> 0.5
			if (Equation[i] == '.' && (i == 0 || !isdigit(Equation[i - 1])))
			{
				Token += '0';
			}

			//Handles parsing the full function name (such as sin or log) and adding it to the stack.
			if (isalpha(Equation[i]))
			{
				while (i < Equation.length() && isalpha(Equation[i]))
				{
					Token += Equation[i];
					i++;
				}
			}

			//Handles parsing numbers and adding it to the stack. 
			//If a decimal is detected, append all numbers to the right of the decimal to the left of the decimal to form the whole decimal number. See @example.
			else
			{
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
			}

			tokenStack.push(Token);
			hasDecimal = false;
		}

		//Determine context of '-'. Is it unary or bianry minus.
		//else if (Equation[i] == '-')
		//{
		//	//Check if it's a binary minus by checking if '-' follows a number, a closing parenthesis, or an 'e'.
		//	if (i > 0 && (isdigit(Equation[i - 1]) || Equation[i - 1] == ')' || Equation[i - 1] == 'e'))
		//	{
		//		tokenStack.push("-");
		//		i++;
		//	}
		//	else//Unary minus
		//	{
		//		Token = "-";
		//		i++;

		//		//Handles negative numbers. Check if unary minus is followed by a number.
		//		if (i < Equation.length() && isdigit(Equation[i]))
		//		{
		//			while (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
		//			{
		//				Token += Equation[i];
		//				i++;
		//			}
		//			tokenStack.push(Token);
		//		}

		//		//Handles negative functions. Check if unary minus is followed by a function.
		//		else if (i < Equation.length() && isalpha(Equation[i]))
		//		{
		//			while (i < Equation.length() && isalpha(Equation[i]))
		//			{
		//				Token += Equation[i];
		//				i++;
		//			}
		//			tokenStack.push(Token);
		//		}
		//		
		//		
		//		else//Standalone unary minus, such as in front of a parenthesis.
		//		{
		//			tokenStack.push("-");
		//		}
		//	}
		//}

		else//Other operators and parentheses
		{
			tokenStack.push(string(1, Equation[i]));
			i++;
		}
	}

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
	-Convert user inputted equation from infix to postfix notation. This is achieved by rearranging operators to follow their operands
		while preserving precedence and associativity of the original equation. Converting to postfix is crucial for
		these types of calculators because it simplifies the eval/calculation process, especially when dealing
		with longer and/or complex equations involving different operators with different precedences.

@param:
	-stack<string> tokenStack: User inputted equation in infix notation.

@return:
	-Returns the equation in postfix notation in a stack, ready to be fed directly into the postfix evaluation / calculator function.

@notes:
	-top = look at the top of the stack.
	-pop = remove the top of the stack.
	-push = add an element to the top of the stack.

@example:
	-1+2*3 = 1 2 3 * +
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
		

		//If current token is a positive or negative operand (including Eulers number), push to postfix stack.
		if (isdigit(Token[0]) || (Token.length() > 1 && Token[0] == '-' && isdigit(Token[1])) || Token[0] == 'e' || (Token.length() > 1 && Token[0] == '-' && Token[1] == 'e'))
		{
			postFixStack.push(Token);
		}
		

		else if (isFunction(Token)) 
		{
			operatorStack.push(Token);
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
			operatorStack.pop(); // Pop the "("


		// If there is a function on top of the operator stack, pop it to postfix stack. This helps to eval use of multiple trig/log functions in one equation.
			if (!operatorStack.empty() && isFunction(operatorStack.top())) 
			{
				postFixStack.push(operatorStack.top());
				operatorStack.pop();
			}
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
	-Performs calculations:
		-Arithmetic (addition, subtraction, multiplication, division, modulo, and exponentiation)
		-Trigonometric (sin, cos, tan)
		-Logarithmic (log and ln)
		-Radical (sqrt)
		-Piecewise (abs)
	-Able to calculate trigonometric functions in degrees or radians based on user input (DegOrRad).

@param:
	-string& Token: Operator of precedence to be checked.
	-double Operand1: First operand.
	-double Operand2: Second operand.

@return:
	-Returns a double of the result of the operation.

@notes:
	-This was created to make the Calculator function more readable.
	-The return 0.0 will NEVER be reached due to guard clauses in the validate input function but it was still included as good practice.
	-By default sin, cos, tan, log, ln, sqrt, and abs are in radians but user input is in degrees.
	-Bool DegOrRad -> degrees = 1
					  radians = 0
*/
double performCalculation(const string& Token, double Operand1, double Operand2, bool DegOrRad)
{
	if (Token == "+") return Operand1 + Operand2;
	else if (Token == "-") return Operand1 - Operand2;
	else if (Token == "*") return Operand1 * Operand2;
	else if (Token == "/") return Operand1 / Operand2;
	else if (Token == "%") return fmod(Operand1, Operand2);
	//else if (Token == "^") return pow(Operand1, Operand2);
	else if (Token == "^")
	{
		if (Operand2 < 0)
		{
			return 1 / pow(Operand1, -Operand2);
		}
		return pow(Operand1, Operand2);
	}
	
	
	//potential fix to negative functions is to perform the positive calculation and then return the negative version. BUT
		//this doesn't fix normal numbers. It would be more efficient to fix everything in one fell swoop then to fix each one individually.
	else if (Token == "sin") return (DegOrRad == 1) ? (sin(Operand1 * (3.14159 / 180))) : sin(Operand1);
	else if (Token == "-sin") return -((DegOrRad == 1) ? (sin(Operand1 * (3.14159 / 180))) : sin(Operand1));
	else if (Token == "cos") return (DegOrRad == 1) ? (cos(Operand1 * (3.14159 / 180))) : cos(Operand1);
	else if (Token == "tan") return (DegOrRad == 1) ? (tan(Operand1 * (3.14159 / 180))) : tan(Operand1);
	else if (Token == "log") return log10(Operand1);
	else if (Token == "ln") return log(Operand1);
	else if (Token == "sqrt") return sqrt(Operand1);
	else if (Token == "abs") return fabs(Operand1);
	return 0.0;
}



/*
@purpose:
	-Calculates the post fix equation.

@param:
	-stack<string> postFixStack: User inputted equation in postfix notation.

@return:
	-Returns a double of the result of the postfix equation to the main function via pass by reference to be printed.

@notes:
	-stod = String to double.
	-Originally, conversion to scientific notation was done in main function but in order to make main function more pretty, it was moved to this function.
		Nothing is lost in this function in terms of functionality or readability by moving the converion to this function since its only 6 lines.
*/
void evaluateEquation(stack<string> postFixStack, bool DegOrRad, double &Result)
{
	stack<double> evalStack;
	string Token;
	double functionOperand = 0.0;
	double Operand1 = 0.0;
	double Operand2 = 0.0;
	Result = 0.0;//Zero out Result before perform next calculation just as a precaution.


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


		//If Euler's number is detected, push its number equivalent to the eval stack and clear Token.
		else if (Token[0] == 'e' || Token == "-e")
		{
			Token[0] == 'e' ? evalStack.push(2.71828) : evalStack.push(-2.71828);//Only 'e' and '-e' will trigger this. If 'e' not detected, assume its '-e' and push -2.71828.
	
		}

		else if (isFunction(Token)) 
		{





			functionOperand = evalStack.top();
			evalStack.pop();
			Result = performCalculation(Token, functionOperand, NULL, DegOrRad);
			evalStack.push(Result);
		}

		
		//Pop the top of the stack twice to load the operands. If the current token is a "-" and the eval stack is empty, it is unary minus and push as such. Otherwise, perform the operation and push the result to the eval stack.
		else//old
		{
			Operand2 = evalStack.top();
			evalStack.pop();

			if (Token == "-" && evalStack.empty())
			{
				evalStack.push(-Operand2); // Handle unary minus
			}


			else
			{
				Operand1 = evalStack.top(); 
				evalStack.pop();
				Result = performCalculation(Token, Operand1, Operand2, DegOrRad);
				evalStack.push(Result);
			}
		}




		
		////new
		//else
		//{
		//	if (evalStack.empty())
		//	{
		//		// Handle unary minus for the first operand
		//		Operand2 = 0;
		//		Operand1 = 0;
		//	}
		//	else
		//	{
		//		Operand2 = evalStack.top();
		//		evalStack.pop();

		//		if (evalStack.empty() && Token == "-")
		//		{
		//			evalStack.push(-Operand2); // Handle unary minus
		//			continue;
		//		}

		//		if (!evalStack.empty())
		//		{
		//			Operand1 = evalStack.top();
		//			evalStack.pop();
		//		}
		//		else
		//		{
		//			Operand1 = 0; // For cases like "-2^3"
		//		}
		//	}

		//	Result = performCalculation(Token, Operand1, Operand2, DegOrRad);
		//	evalStack.push(Result);
		//}


	}


	
	if (abs(Result) > 1e10 || (abs(Result) < 1e-4 && Result != 0.0))//Convert to scientific notation if final result is larger than 10^10 or smaller than 10^-4.
	{
		stringstream ss;
		ss << scientific << setprecision(3) << evalStack.top();
		ss >> Result;
	}
	else Result = round(evalStack.top() * 1000) / 1000;//round to 3 decimal places.

}
