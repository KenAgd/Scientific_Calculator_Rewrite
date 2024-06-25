
#pragma once
#ifndef CALCULATE_H
#define CALCULATE_H

#include <stack>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cmath>
using namespace std;

//Auxiliary Functions
void testPrint(stack<string> Stack);
bool isOperator(char Token);
bool isFunction(const string& str);
stack<string> ReverseStack(stack<string> tokenStack);

//Main Functions
bool validateInput(const string& input);
stack<string> Tokenize(const string& input);
stack<string> shuntingYard(stack<string> TokenStack);
double evaluateEquation(stack<string> postFixStack);
#endif