#pragma once
#ifndef SIMPLECALCULATOR_H_
#define SIMPLECALCULATOR_H_

#include <vector>
#include "Calculator.h"
#include "Iterator.h"
#include "Symbol.h"
/*
SimpleCalculator constructs the Symbols that are the building blocks
of an expression by defining the character(s), function, and domain
for each symbol.
*/
class SimpleCalculator:public Calculator<double>
{
	public:
	//typedef Symbol<double> Symbol;
	typedef BinaryOperatorSymbol<double> BinaryOperatorSymbol;
	typedef OperandSymbol<double> OperandSymbol;
	typedef CompositeOperandSymbol<double> CompositeOperandSymbol;

	SimpleCalculator(void);
	~SimpleCalculator(void);
	virtual void CreateSymbols();
	void CreateOperands();
	void CreateOperations();
	friend class SymbolIterator;

	class SymbolIterator:public Iterator<Symbol*>
	{
	public:
		SymbolIterator(SimpleCalculator *calc):_calculator(calc){_iter = _calculator->_symbols.begin();}
		virtual void First(){_iter = _calculator->_symbols.begin();}
		virtual void Next(){_iter++;}
		virtual bool IsDone(){return _iter ==_calculator->_symbols.end();}
		virtual Symbol *Current(){return *_iter;}
		
	private:
		SymbolIterator(){}
		SimpleCalculator *_calculator;
		std::vector<Symbol* >::iterator _iter;
	};
	SymbolIterator *GetSymbols(){return new SymbolIterator(this);}

};
#endif

