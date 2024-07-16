
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
stack<string> ReverseStack(stack<string> tokenStack);
bool isOperator(char Token);
bool isFunction(const string& str);
bool validateDecimalPoint(const string& Equation, size_t& i, const char& ch, bool& expectOperator, bool& allowUnary);
bool validateOperator(const string& Equation, size_t& i, const char& Token, bool& expectOperator, bool& allowUnary);
bool validateEuler(const string& Equation, size_t& i, bool& expectOperator, bool& allowUnary);
bool validateFunctions(const string& Equation, size_t& i, bool& expectOperator, bool& allowUnary, stack<char>& Parentheses);
int Precedence(const string& Token);
double performCalculation(const string& Token, double Operand1, double Operand2, bool DegOrRad);



//Main Functions
bool validateEquation(const string& input);
stack<string> Tokenize(const string& input);
stack<string> shuntingYard(stack<string> TokenStack);
void evaluateEquation(stack<string> postFixStack, bool DegOrRad, double& Result);
#endif