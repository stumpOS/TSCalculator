#pragma once
#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include <list>
#include <vector>
#include <stack>
#include <string>
#include "Symbol.h"
#include "functiontree.h"
/*
The Expression enforces the lexical grammar of arithmetic expressions
*/
class Expression
{
public:
	typedef std::list<Symbol<double>* >::iterator expression_ptr;

	Expression();
	~Expression(void);
	void NewOperand(Symbol<double>* symbol);
	enum State{StartState, RightOfOperator, BuildingOperand, BuildingOperandAfterDecimal, ErrorState};

	void Update(Symbol<double>* const& symbol);
	std::string const& GetExpressionAsString(){return _expressionString;}
	
	void ClearExpression();
	void BackExpression();
	void Evaluate();

private:
	std::string _expressionString;
	std::list<Symbol<double>* > _expression;
	CompositeOperandSymbol<double>* _currentOperand;
	State _state;
	std::stack<State> _pastStates;
};
#endif