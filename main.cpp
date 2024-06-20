#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include "Calculate.h"
using namespace std;

//do not to input manipulation in this function, this is only for validation. Any input manipulation should be done in the tokenize function
/*
bool validateInput(string &Equation)
{
	unordered_set<char> Operators = { '+', '-', '*', '/', '^', '%', '(', ')', '.', '~'};
	unordered_set<char> Numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	size_t i;
	char Token;
	bool decimalCheck = false;


//Empty input check.
	if (Equation.empty())
	{
		cout << "Error: Empty input. Please try again." << endl;
		return false;
	}


	for (i = 0; i < Equation.length(); i++)
	{
		Token = Equation[i];


		if (isspace(Token))//Whitespace check.
		{
			cout << "Error: Whitespace detected. Please try again." << endl;
			return false;
		}

		if (Numbers.find(Token) == Numbers.end() && Operators.find(Token) == Operators.end())//Invalid character check.
		{
			cout << "Error: Invalid character detected. Please try again." << endl;
			return false;
		}

		if (Token == '/' && (i + 1 < Equation.length() && Equation[i + 1] == '0'))//Division by zero check.
		{
			cout << "Error: Division by zero detected. Please try again." << endl;
			return false;
		}


		if (Equation.size() == 1 && Operators.count(Token))//Single operator check.
		{
			cout << "Error: Single operator detected. Please try again." << endl;
			return false;
		}


		if ((Operators.count(Equation.front()) > 0 && Equation.front() != '(') || (Operators.count(Equation.back()) > 0 && Equation.back() != ')'))//Leading operator check. Exclude '(' and ')'.
		{
			cout << "Error: Leading or trailing operator detected. Please try again." << endl;
				return false;
		}



		if (Operators.count(Token) && Token != '~' && Operators.count(Equation[i + 1]) && Equation[i+1] != '~')//Consecutive operator check.
		{
			cout << "Error: Consecutive operators detected. Please try again." << endl;
			return false;
		}



		if (Token == '.')//Multiple decimal points check.
		{
			if (decimalCheck == true)
			{
				cout << "Error: Multiple decimal points detected. Please try again." << endl;
				return false;
			}

			else
			{
				decimalCheck = true;
			}
		}
		else if (!isdigit(Token))//If non-digit is detected, reset decimalCheck.
		{
			decimalCheck = false;
		}

	}


	/*
	advanced checks
		check for proper use of unary minus (EX: 1~2 instead of 1-2)
		check for unmatched parentheses
		check against proper use of parentheses. Prevent things such as (), (1), (+)
		if ~~ detected, convert following number to positive.

	need to think of
		prevent 1~~2
		.5 triggering consecutive operators




}*/








// Function to check if a character is a valid operator






bool Restart()
{
	string Continue;

	while (true)
	{
		cout << "Would you like to continue? (y/n) ";
		getline(cin, Continue);
		if (Continue == "y")
		{
			return true;
		}
		else if (Continue == "n")
		{
			return false;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			continue;
		}
	}
}




//create test cases function here


int main()
{
	string Equation;
	stack<string>tokenizedStack;
	stack<string>postFixStack;
	double Result = 0.0;
	//bool Continue = true;

	cout << "Welcome to the Scientific Calculator. Please note:" << endl << "If you want to use negative numbers, use the '~' character." << endl << "Dont use spaces between numbers or operators." << endl << endl;
	while (true)
	{
		cout << "Enter an equation: ";
		getline(cin, Equation);

		if (!validateInput(Equation)) continue;

		else
		{
			cout << Equation << endl;
		}




		if (!Restart()) break;
		else continue;
	}
}