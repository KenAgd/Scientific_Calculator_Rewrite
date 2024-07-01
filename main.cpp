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

	-Shunting Yard algorithm HAS to be used for calculator programs in order to make evaluating larger more complex equations easier. It can handle:
		-Operator precedence and associativity (PEMDAS)
		-Parentheses.
		-Exponents.
		-Decimal points.
		-Negative (unary) numbers.
		-Trigonometric functions.

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

*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <algorithm>
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
*/
int main()
{
	string Equation;
	stack<string>tokenizedStack;
	stack<string>postFixStack;
	double Result = 0.0;
	

	cout << "Welcome to the Scientific Calculator. Please note:" << endl << "If you want to use negative numbers, use the '~' character." << endl << "Dont use spaces between numbers or operators." << endl << "If you want to exit, type 'exit' or 'quit'." << endl;
	while (true)
	{
		cout << endl <<"Enter an equation: ";
		getline(cin, Equation);

		if (Equation == "exit" || Equation == "quit" || Equation == "Exit" || Equation == "Quit") break;

		if (!validateInput(Equation)) continue;

		else
		{
			tokenizedStack = Tokenize(Equation);
			//testPrint(tokenizedStack);
			postFixStack = shuntingYard(tokenizedStack);
			testPrint(postFixStack);
			//evaluateEquation(postFixStack);
//			Result = evaluateEquation(postFixStack);
		//	cout << "Result: " << Result << endl;
		}


		if (!Restart()) break;
		else continue;
	}
}