/*
@author: Kendric Agdaca
@date: 



*/


#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include "Calculate.h"
using namespace std;


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





int main()
{
	string Equation;
	stack<string>tokenizedStack;
	stack<string>postFixStack;
	double Result = 0.0;
	

	cout << "Welcome to the Scientific Calculator. Please note:" << endl << "If you want to use negative numbers, use the '~' character." << endl << "Dont use spaces between numbers or operators." << endl << endl;
	while (true)
	{
		cout << endl <<"Enter an equation: ";
		getline(cin, Equation);

		if (!validateInput(Equation)) continue;

		else
		{
			tokenizedStack = Tokenize(Equation);
			postFixStack = shuntingYard(tokenizedStack);

			Result = evaluateEquation(postFixStack);
			cout << "Result: " << Result << endl;
			//testPrint(postFixStack);
		}




		if (!Restart()) break;
		else continue;
	}
}