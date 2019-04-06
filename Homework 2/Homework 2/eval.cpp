//
//  eval.cpp
//  Homework 2
//
//  Created by Xin Huang on 2/1/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

bool isValidInfix(string infix);
string noSpace(string infix);
bool allValidOperand(string infix, const Map& values);
string translate(string infix);
bool precedenceCheck(char a, char b);
int calculate(string postfix, int& result, const Map& values);

int evaluate(string infix, const Map& values, string& postfix, int& result)
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose only operands are [single lower case] letters (whether or not they appear in the values map), then postfix is set to the postfix form of the expression; otherwise postfix may or may not be changed, result is unchanged, and the function returns 1.

//   If infix is syntactically valid but contains at least one lower case letter operand that [does not appear in the values map], then result is unchanged and the function returns 2.

//   If infix is syntactically valid and all its lower case operand letters appear in the values map, then if evaluating the expression (using for each letter in the expression the value in the map that corresponds to it) attempts to divide by zero, then result is unchanged and the function returns 3.

//   otherwise, result is set to the value of the expression and the function returns 0.

{
    if (!isValidInfix(infix))
        return 1;
    postfix = translate(infix);
    if (!allValidOperand(infix, values))
        return 2;
    if (calculate(postfix, result, values) == 3)
        return 3;
    return 0;
}

bool isValidInfix(string infix)   // if false, return 1, result unchanged
{
    infix = noSpace(infix);
    if (infix.size() == 0)
        return false;
    if (infix.size() == 1 && islower(infix[0]))   // if only 1 valid operand
        return true;
    
    int openPN = 0;     // number of open parentheses
    int closePN = 0;    // number of close parentheses
    int operatorN = 0;  // number of operators
    int operandN = 0;   // number of operands
    string noP = "";    // a string of infix without parenthesis
    
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        if (!islower(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')')
            return false;
        if (c == '(')
            openPN ++;
        if (c == ')')
            closePN ++;
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            operatorN ++;
            noP += c;
        }
        if (islower(c))
        {
            operandN ++;
            noP += c;
        }
        if (openPN < closePN)        // before any ')', there must be a '('
            return false;
    }
    if (openPN != closePN)           // each open parenthesis must associate with a close paratheses
        return false;
    if (operandN - operatorN != 1)   // number of operand must be 1 more than number of operator
        return false;
    if (noP.size() == 0)             // cannot have empty parenthesis
        return false;
    
    char curr, next;
    for (int i = 0; i < noP.size()-1; i++)
    {
        curr = noP[i];
        next = noP[i+1];
        if ((islower(curr) && islower(next)) || (!islower(curr) && !islower(next)))
            return false;   // neighboring operation expression cannot both be operands or operators
    }
    if (!islower(noP[0]) || !islower(noP[noP.size()-1]))
        return false;       // first and last expression cannot be operator
    
    for (int i = 0; i < infix.size()-1; i++)
    {
        curr = infix[i];
        next = infix[i+1];
        if (curr == '(' && next == ')')
            return false;   // cannot have empty parenthesis
    }
    
    return true;
}

string noSpace(string infix)
{
    string noSpace = "";
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        if (!isspace(c))   //get rid of spaces
            noSpace += c;
    }
    return noSpace;
}

bool allValidOperand(string infix, const Map& values)   // if false, return 2, result unchanged
{
    char c;
    for (int i = 0; i < infix.size(); i++)
    {
        c = infix[i];
        if (islower(c) && !values.contains(c))
            return false;
    }
    
    return true;
}

string translate(string infix)
{
    infix = noSpace(infix);
    string postfix = "";
    stack<char> operation;
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        if (islower(c))
        {
            postfix += c;
            continue;
        }
        switch(c)
        {
            case '(':
                operation.push('(');
                break;
            case ')':
                while (operation.top() != '(')
                {
                    postfix += operation.top();
                    operation.pop();
                }
                operation.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!operation.empty() && operation.top() != '(' && precedenceCheck(c, operation.top()))
                {
                    postfix += operation.top();
                    operation.pop();
                }
                operation.push(c);
                break;
        }
    }
    while (!operation.empty())
    {
        postfix += operation.top();
        operation.pop();
    }

    return postfix;
}

bool precedenceCheck(char a, char b)   // check if precedence of a <= precedence of b
{
    if ((a == '*' || a == '/') && (b == '+' || b == '-'))
        return false;
    return true;
}

int calculate(string postfix, int& result, const Map& values)
{
    stack<char> operand;
    
    for (int i = 0; i < postfix.size(); i++)
    {
        char c = postfix[i];
        if (islower(c))
        {
            int value = 0;
            values.get(c, value);
            operand.push(value);
        }
        else
        {
            int answer = 0;
            char operand2 = operand.top();
            operand.pop();
            char operand1 = operand.top();
            operand.pop();
            
            switch(c)
            {
                case '+':
                    answer = operand1 + operand2;
                    break;
                case '-':
                    answer = operand1 - operand2;
                    break;
                case '*':
                    answer = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                        return 3;
                    answer = operand1 / operand2;
                    break;
            }
            operand.push(answer);
        }
    }
    
    result = operand.top();
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0);
    assert(pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);   // FAIL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}

