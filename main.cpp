/*
@author: Kendric Agdaca
@since: 06/06/24 -> 

@purpose: 
	-This is the main source file of the program that ONLY houses the main function and a restart function. All other functions are stored within calculate.cpp.

@notes:
	-Only initialize important variables where necessary. If the variable is small / unimportant, initialize at the top of the function.

	-Since this is a simple and relatively straight forward program that doesn't require the need of multiple struct nodes, I decided to code this procedureally.

	-Codeium copilot was used to generate a majority of this code. I first did research and make pseudocode flow charts (see README), then I had ChatGPT generate sample segments of code, then I started writing code.
		Interestingly enough, the Codeium generated code was almost identical to the ChatGPT generated code. What was also nice was that after Codeium had sampled enough of my coding style, it even auto generated
		comments and comment headers they way I like to write them. My only gripe is that if I use the Codeium chat to generate sample codes and then ask it to refactor or reformat, it starts to generate code that isn't very straight
		foward and starts to use fancy function calls that are unique to C++ instead of writing code that uses core fundamentals.

		-While I do feel like I cheated a little bit using AI's to help me write this code, I think it's worth it. I still did my due diligence and did the research
		behind each function and algorithm. See README for all of my notes for each function.

	-I decided to stray away from Hungarian notation since it just seems silly to me now and a lot of people online feel the same way. I did however use JavaDoc style comments.

	-This is a console/terminal application. This will be upgraded in the future to a GUI using Qt as a way to start learning GUI creation.

	-The reason why this project took so long was because I had to basically rewrite the entire program. I copy pasted toooo much code from codeium and ChatGPT to the point where the code broke and became messy
		and unreadable. I also added the feature of being able to use trigonometric functions.

	-Shunting Yard algorithm HAS to be used for calculator programs in order to make evaluating larger more complex equations easier. This calculator can handle:
		-Operator precedence and associativity (PEMDAS)
		-Parentheses.
		-Exponents.
		-Decimal points.
		-Negative (unary) numbers.
		-Trigonometric functions (only sin, cos, tan)
		-Logarithmic functions (only log and ln)
		-Radical functions (only sqrt)
		-Piecewise functions (only abs)
		-Eulers number 'e'
		                   *****NOTE: for the sake of simplicity, trig, log, radical, piecewise, and eulers number will all fall under the term "functions"*****

	-Coding conventions:
		Naming conventions:
			-All single word variables and function names are capitalized.
			-All multi word variables and function names have the first word lowercase and the rest of the words are capitalized.
		Comment conventions:
			-Use JavaDoc style comments. Each function should have a purpose, parameters, return, and notes section.
			-In line comments should be kept brief and shouldn't need the use of comment blocks. If the comment isn't in line with the code its describing, put it right above the line of code with one
				less indentation than the code.
			-One comment can be used to describe multiple lines of code IF the multiple lines of code all work towards achieving one goal.

	-Upon mid completion reflection/evaluation, I could have used a combination of queues and stacks to solve the problem.
		-A queue could've been used in validate and tokenize and a stack would be used in shunting yard and evaluating the equation. If I were to follow this approach, when passing the queue tokenize output
			to stack shunting yard, I would just push the front of the queue into the stack and then pop the queue.
		-EX:
			    queue<string> tokenQueue;
				tokenQueue.push("3");
				tokenQueue.push("+");
				tokenQueue.push("4");
				tokenQueue.push("*");
				tokenQueue.push("2");

				// Create a stack and transfer elements from the queue to the stack
				stack<string> tokenStack;
				while (!tokenQueue.empty()) 
				{
					tokenStack.push(tokenQueue.front());
					tokenQueue.pop();
				}

		-Stacks are basically a standard linked list while a queue is a circular linked list. Both have a time complexity of O(1) for push/enqueue, pop/dequeue, front/peek, and IsEmpty.
		-Stacks are LIFO and queues are FIFO. For stacks, the equation would be read from bottom to top while for queues, the equation would be read from left to right. 
		-At the beginning of the project I chose to just use stacks for everything for the sake of consistency and reduce the need for converting between stacks and queues, HOWEVER,
			it would have been a good learning opportunity to learn and use queues. 

		-For trig functions in shunting yard and evaluating the equation, they dont have operator precedence because they aren't operators. Thus, they are treated as operands.
		-Binary minus is referred to in Tokenize. Binary minus means normal subtraction while unary minus means negative number.
		-OneNote flow charts dont include how to handle switching bewteen calculating in degrees or radians, converting to scientific notation, or eulers number. This are 
			functionalities that I added on top of the project. The flow charts only cover the basic functionality of the calculator.



		-new VS shortcut learned: ctrl + k then while still holding ctrl, ctrl + c to comment out highlighted lines. ctrl + k then ctrl + u to uncomment.
			Any previous comments before ctrl + k + c will be retained, meaning that ctrl + k + u wont uncomment them.
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Calculate.h"
using namespace std;

/*
@purpose:
	-Asks the userif they'd like to perform another calculation.

@param:
	-None.

@return:
	-Returns true if user wants to continue, false if they don't.

@notes:
	-This was separated from main function to thin out the main function.
*/
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




/*
@notes:
	-getline is used over cin because cin doesn't accept spaces.
		example: 1 + 1 in cin would just be 1
				 1+1 in cin would be 1+1
	-bool degrees = 1
		  radians = 0
*/
int main()
{
	string Equation;
	bool DegOrRad = 0; //By default calculate in radian mode.
	stack<string>tokenizedStack;
	stack<string>postFixStack;
	double Result = 0.0;
	double RoundedResult = 0.0;
	bool DebugMode = 1;//1 = test prints only, 0 = no prints
	

	cout << "Welcome to the Scientific Calculator. Please note:" << endl << "*Dont use spaces between numbers or operators." << endl << "*To switch between calculating in Radian or Degrees, type 'deg' or 'rad'. By default the calculator is set to radian mode." << endl << "*Log is in base 10" << endl << "*Dont use juxtaposition in the equation EX: 2(3) use 2*(3) instead"<< endl << "*Encapsulate exponents in parentheses. EX: 2^(1+2)" << endl << "*To exit, type 'exit' or 'quit'." << endl;
	cout << "Allowed operators and functions: + - * / ^ % e sin cos tan log ln sqrt abs" << endl;
	while (true)
	{
		cout << endl <<"Enter an equation: ";
		getline(cin, Equation);

		if (Equation == "exit" || Equation == "quit" || Equation == "Exit" || Equation == "Quit") break;

		if (Equation == "rad" || Equation == "Rad")
		{
			DegOrRad = 0;
			cout << "Switched to Radian mode." << endl;
			continue;
		}

		if (Equation == "deg" || Equation == "Deg")
		{
			DegOrRad = 1;
			cout << "Switched to Degrees mode." << endl;
			continue;
		}

		if (!validateEquation(Equation)) continue;

		else
		{
			tokenizedStack = Tokenize(Equation);
			if (DebugMode) testPrint(tokenizedStack);
			postFixStack = shuntingYard(tokenizedStack);
			if (DebugMode) testPrint(postFixStack);
			//evaluateEquation(postFixStack, DegOrRad, Result);//Result is passed by reference (&). Meaning any changes made to Result in evaluateEquation will be reflected in the main function as well.
			//cout << "Result: "  << Result << endl;
		}


		if (!Restart()) break;
		else continue;
	}
}