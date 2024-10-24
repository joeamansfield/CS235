#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include <string>
#include <stack>
#include <sstream>
#include "ExpressionManagerInterface.h"
using namespace std;

class ExpressionManager : public ExpressionManagerInterface
{
private:
	string originalEquation = "";
	string postfixExpression = "";
	int finalValue;
	stack<string> fatStack;
	bool isOperator(string check)
	{
		return (check == "*" ||
				check == "/" ||
				check == "%" ||
				check == "+" ||
				check == "-");
	}
	bool isOpen(string check)
	{
		return (check == "(" ||
				check == "[" ||
				check == "{");
	}
	bool isClose(string check)
	{
		return (check == ")" ||
				check == "]" ||
				check == "}");
	}
	bool isMatch(string open, string close)
	{
		return ((open == "(" && close == ")") ||
				(open == "[" && close == "]") ||
				(open == "{" && close == "}"));
	}
	bool isOperand(string check)
	{
		for (unsigned int i = 0; i < check.size(); i++)
		{
			if (!isdigit(check[i])) { return false; }
		}
		return true;
	}
	bool isValidEntry(string check)
	{
		return (isOperand(check) ||
				isOperator(check) ||
				isOpen(check) ||
				isClose(check));
	}
	int checkPreced(string op)
	{
		if (op == "+" || op == "-") { return 1; }
		else if (op == "*" || op == "/" || op == "%" ) { return 2; }
		else if (op == "(" || op == "[" || op == "{") { return 3; }
	}
public:
	ExpressionManager(string inStr = "") { originalEquation = inStr; }
	~ExpressionManager(void) {}

	// Returns final integer value
	virtual int value(void)
	{
		stringstream evauluateStream;
		evauluateStream << postfixExpression;
		int leftOp = 0;
		int rightOp = 0;
		string symbol;
		for (symbol; evauluateStream >> symbol;)
		{
			if (isOperand(symbol)) { fatStack.push(symbol); }
			if (isOperator(symbol))
			{
				rightOp = stoi(fatStack.top());
				fatStack.pop();
				leftOp = stoi(fatStack.top());
				fatStack.pop();
				if (symbol == "+") { leftOp = leftOp + rightOp; }
				else if (symbol == "-") { leftOp = leftOp - rightOp; }
				else if (symbol == "/") { leftOp = leftOp / rightOp; }
				else if (symbol == "*") { leftOp = leftOp * rightOp; }
				else if (symbol == "%") { leftOp = leftOp % rightOp; }
				fatStack.push(to_string(leftOp));
			}
		}
		return stoi(fatStack.top());
	}
 
	// Returns infix representation, checks for errors
	virtual string infix(void)
	{
		stringstream tempStream;
		tempStream << originalEquation;
		string symbol;
		for (symbol; tempStream >> symbol;)
		{
			if (isOpen(symbol)) { fatStack.push(symbol); }
			if (isClose(symbol))
			{
				if (fatStack.empty()) { throw "Unbalanced"; }
				if (isMatch(fatStack.top(), symbol)) { fatStack.pop(); }
				else { throw "Unbalanced"; }
			}
		}
		if (!fatStack.empty()) { throw "Unbalanced"; }
		while (!fatStack.empty()) { fatStack.pop(); }
		tempStream.clear();
		tempStream << originalEquation;
		tempStream >> symbol;
		fatStack.push(symbol);
		for (symbol; tempStream >> symbol;)
		{
			if (isOperator(fatStack.top()) && isOperator(symbol)) { throw "Missing Operand"; }
			if (isOperand(fatStack.top()) && isOperand(symbol)) { throw "Missing Operator"; }
			if (!isValidEntry(symbol)) { throw "Illegal Operator"; }
			fatStack.push(symbol);
		}
		if (isOperator(fatStack.top())) { throw "Missing Operand"; }
		while (!fatStack.empty()) { fatStack.pop(); }
		return originalEquation;
	}

	// Returns postfix representation
	virtual string postfix(void)
	{
		while (!fatStack.empty()) { fatStack.pop(); } //clear stack
		stringstream tempStream;
		tempStream << originalEquation;
		string symbol;
		for (symbol; tempStream >> symbol;)
		{
			if (isOperand(symbol))
			{
				postfixExpression.append(symbol);
				postfixExpression.append(" ");
			}
			else if (fatStack.empty())
			{
				fatStack.push(symbol);
			}
			else
			{
				if (isOperator(symbol))
				{
					if (isOperator(fatStack.top()))
					{
						if (checkPreced(symbol) > checkPreced(fatStack.top()))
						{
							fatStack.push(symbol);
						}
						else
						{
							bool donePreced = false;
							while (!fatStack.empty() && !donePreced)
							{
								postfixExpression.append(fatStack.top());
								postfixExpression.append(" ");
								fatStack.pop();
								if (!fatStack.empty())
								{
									if (checkPreced(symbol) < checkPreced(fatStack.top())) { donePreced = true; }
								}
							}
							fatStack.push(symbol);
						}
					}
					else { fatStack.push(symbol); }
				}
				else if (isOpen(symbol)) { fatStack.push(symbol); }
				else if (isClose(symbol))
				{
					while (!isMatch(fatStack.top(), symbol))
					{
						postfixExpression.append(fatStack.top());
						postfixExpression.append(" ");
						fatStack.pop();
					}
					fatStack.pop();
				}
			}
		}
		while (!fatStack.empty())
		{
			postfixExpression.append(fatStack.top());
			postfixExpression.append(" ");
			fatStack.pop(); 
		}
		return postfixExpression;
	}

	// (BONUS) Returns prefix representation
	virtual string prefix(void)
	{
		stringstream tempStream;
		tempStream << originalEquation;
		string symbol;
		for (symbol; tempStream >> symbol;)
		{

		}
		return "NOT IMPLEMENTED";
	}

	// Returns the infix vector'd expression items
	virtual string toString(void) const
	{
		return "NOT IMPLEMENTED, NOT NECESSARY";
	}
};
#endif	// EXPRESSION_MANAGER_H
