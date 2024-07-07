
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
int Precedence(const string& Token);
double performCalculation(const string& Token, double Operand1, double Operand2, bool DegOrRad);



//Main Functions
bool validateInput(const string& input);
stack<string> Tokenize(const string& input);
stack<string> shuntingYard(stack<string> TokenStack);
void evaluateEquation(stack<string> postFixStack, bool DegOrRad, double& Result);
#endif