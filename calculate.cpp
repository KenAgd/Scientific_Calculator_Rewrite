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
	-I chose to use unordered_set instead of unordered_map because unordered_set automatically assigns a key to each value whereas unordered_map does not.
		Both use hashing functions and both have the same time complexity (O(1)), unordered_set just saves me time and lines.
*/
bool isFunction(const string& str) {
	static const unordered_set<string> functions = { "sin", "cos", "tan", "log", "ln", "sqrt", "abs" };

	if (functions.find(str) != functions.end()) 
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
bool validateInput(const string& input) {
	stack<char> Parentheses;  // Stack to track parentheses for balancing
	bool expectOperator = false;
	bool allowUnary = true;
	bool hasDecimal = false;
	string FunctionToken;
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

		//Handle whitespace.
		if (isspace(ch))
		{
			cout << "Error: Whitespace detected. Please try again." << endl;
			return false;
		}

		//Handle decimal points.
		else if (isdigit(ch) || ch == '.') 
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


		//Handle operators
		else if (isOperator(ch))
		{
			if (ch == '-' && allowUnary)
			{
				i++;
				continue;
			}

			if (expectOperator == false)
			{
				cout << "Error: Invalid operator usage. Please try again." << endl;
				return false;
			}

			if (ch == '/' && i + 1 < input.length() && input[i + 1] == '0')
			{
				cout << "Error: Division by zero detected. Please try again." << endl;
				return false;
			}

			if (isOperator(input.back()) || input.back() == '.')
			{
				cout << "Error: Invalid operator usage. Please try again." << endl;
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


		//Handle open parentheses
		else if (ch == '(')
		{
			Parentheses.push(ch);
			expectOperator = false; // After '(', we do not expect an operator but allow unary.
			allowUnary = true;
			i++;
		}


		//Handle close parentheses
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


		//Check for Euler's number 'e'.
		else if (ch == 'e') 
		{
			// Check if 'e' is preceded by a digit or decimal point.
			if (i > 0 && (isdigit(input[i - 1]) || input[i - 1] == '.')) 
			{
				cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
				return false;
			}

			// Check if 'e' is followed by a digit or decimal point.
			if (i + 1 < input.length() && (isdigit(input[i + 1]) || input[i + 1] == '.')) 
			{
				cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
				return false;
			}

			// Check if 'e' is followed by any letter.
			if (i + 1 < input.length() && isalpha(input[i + 1])) 
			{
				cout << "Error: Invalid use of Euler's number 'e'. Please try again." << endl;
				return false;
			}

			i++;
			expectOperator = true;
			allowUnary = false;
		}


		//Handles trig functions. 
		else if (isalpha(ch))
		{
			
			//First load all letters of the trig function into the token.
			while (i < input.length() && isalpha(input[i]))
			{
				FunctionToken += input[i];
				i++;
			}

			//Check if the token is a valid trig function. If its valid BUT a ( doesn't follow it, error print and return false.
			if (isFunction(FunctionToken))
			{
				if (i >= input.length() || input[i] != '(') 
				{
					cout << "Error: Invalid use of function. Please try again." << endl;
					return false;
				}

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

			FunctionToken.clear();//This is necessary for checking for multiple uses of trig functions or nested trig functions.
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

			//Handles parsing the full function name and adding it to the stack.
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
		else if (Equation[i] == '-')
		{
			//Check if it's a binary minus by checking if '-' follows a number, a closing parenthesis, or an 'e'.
			if (i > 0 && (isdigit(Equation[i - 1]) || Equation[i - 1] == ')' || Equation[i - 1] == 'e'))
			{
				tokenStack.push("-");
				i++;
			}
			else//Unary minus
			{
				Token = "-";
				i++;

				//Handles negative numbers. Check if unary minus is followed by a number.
				if (i < Equation.length() && isdigit(Equation[i]))
				{
					while (i < Equation.length() && (isdigit(Equation[i]) || Equation[i] == '.'))
					{
						Token += Equation[i];
						i++;
					}
					tokenStack.push(Token);
				}

				//Handles negative functions. Check if unary minus is followed by a function.
				else if (i < Equation.length() && isalpha(Equation[i]))
				{
					while (i < Equation.length() && isalpha(Equation[i]))
					{
						Token += Equation[i];
						i++;
					}
					tokenStack.push(Token);
				}
				
				
				else//Standalone unary minus, such as in front of a parenthesis.
				{
					tokenStack.push("-");
				}
			}
		}

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
	else if (Token == "^") return pow(Operand1, Operand2);
	else if (Token == "sin") return (DegOrRad == 1) ? (sin(Operand1 * (3.14159 / 180))) : sin(Operand1);
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
	Result = 0.0;


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


		else if (Token[0] == 'e' ||  Token == "-e") Token[0] == 'e' ? evalStack.push(2.71828) : evalStack.push(-2.71828);


		else if (isFunction(Token)) 
		{
			functionOperand = evalStack.top();
			evalStack.pop();
			Result = performCalculation(Token, functionOperand, NULL, DegOrRad);
			evalStack.push(Result);
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
				Operand1 = evalStack.top(); 
				evalStack.pop();
				Result = performCalculation(Token, Operand1, Operand2, DegOrRad);
				evalStack.push(Result);
			}
		}
	}


	
	if (abs(Result) > 1e10 || (abs(Result) < 1e-4 && Result != 0.0))//Convert to scientific notation if final result is larger than 10^10 or smaller than 10^-4.
	{
		stringstream ss;
		ss << scientific << setprecision(3) << evalStack.top();
		ss >> Result;
	}
	else Result = round(evalStack.top() * 1000) / 1000;//round to 3 decimal places.
}
