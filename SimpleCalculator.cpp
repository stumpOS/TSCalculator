#include "SimpleCalculator.h"


SimpleCalculator::SimpleCalculator(void)
{
	CreateSymbols();
}


SimpleCalculator::~SimpleCalculator(void)
{
}
void SimpleCalculator::CreateSymbols()
{
	CreateOperands();
	CreateOperations();
}
void SimpleCalculator::CreateOperands()
{
	for(unsigned short i=0;i<10;i++)
	{
		OperandSymbol *symbol = new OperandSymbol(-1,(double)i);
		std::string str = Calculator::GetStringFromShort(i);
		symbol->SetLabel(str);
		_symbols.push_back(symbol);
	}

	OperandSymbol *decimal_symbol = new OperandSymbol(0,0);
	decimal_symbol->SetLabel(".");
	_symbols.push_back(decimal_symbol);
}
void SimpleCalculator::CreateOperations()
{
	auto add = [](double a, double b){return a+b;};
	auto mult = [](double a, double b){return a*b;};
	auto div = [](double a, double b){return a/b;};
	auto power = [](double a, double b){return pow(a,b);};
	auto negate = [](double a,double b){return a-b;};

	int rank=1;
	
	BinaryOperatorSymbol *power_symbol = new BinaryOperatorSymbol("^",rank++,power);
	BinaryOperatorSymbol *mult_symbol = new BinaryOperatorSymbol("*",rank++,mult);
	BinaryOperatorSymbol *div_symbol = new BinaryOperatorSymbol("/",rank++,div);
	div_symbol->SetRightDiscontinuity(0);
	BinaryOperatorSymbol *negate_symbol = new BinaryOperatorSymbol("-",rank++,negate);
	BinaryOperatorSymbol *add_symbol = new BinaryOperatorSymbol("+",rank++,add);
	
	_symbols.push_back(negate_symbol);
	_symbols.push_back(power_symbol);
	_symbols.push_back(mult_symbol);
	_symbols.push_back(add_symbol);
	_symbols.push_back(div_symbol);
}