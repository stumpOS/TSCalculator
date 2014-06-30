#pragma once
#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include <vector>
#include "Symbol.h"

template<class T>
class Calculator
{
public:
	typedef Symbol<T> Symbol;
	
	Calculator(void){}
	virtual ~Calculator(void)
	{
		std::vector<Symbol*>::iterator it = _symbols.begin();
		for(;it!=_symbols.end();)
		{
			Symbol *temp = *it;
			it++;
			delete temp;
			temp = NULL;
		}
		_symbols.clear();	
	}
	virtual void CreateSymbols() = 0;
	static std::string GetStringFromShort(unsigned short number);
	unsigned GetNumberOfSymbols(){return _symbols.size();}

protected:
	std::vector<Symbol* > _symbols;
};

#endif
