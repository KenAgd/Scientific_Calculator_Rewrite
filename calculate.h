
#pragma once
#ifndef CALCULATE_H
#define CALCULATE_H

#include <stack>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

bool isOperator(char Token);
bool isFunction(const string& str);
bool validateInput(const string& input);
stack<string> ReverseStack(stack<string> tokenStack);
void testPrint(stack<string> Stack);
stack<string> Tokenize(const string& input);
stack<string> shuntingYard(stack<string> TokenStack);
double Calculator(stack<string> PostFixStack);




#endif