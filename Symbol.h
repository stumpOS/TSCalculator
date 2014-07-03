#pragma once
#ifndef SYMBOL_H_
#define SYMBOL_H_
#include <wx/wx.h>
#include <string>
#include <functional>
#include <cmath>
#include <utility>
#include <vector>
#include "Domain.h"

template<class T>
class Symbol
{
public:
	Symbol(int rank,std::string label):_rank(rank),_label(label){}
	virtual ~Symbol(){}
	std::string const& GetLabel(){return _label;}
	void SetLabel(std::string str){_label = wxString(str);}
	virtual T Fire(T a, T b) = 0;

	int GetRank(){return _rank;}
	friend bool operator<(Symbol const& rhs, Symbol const& lhs);
protected:
	std::string _label;
	int _rank;
};
template<class T>
class OperandSymbol:public Symbol<T>
{
public:
	OperandSymbol(std::string label, T data):Symbol<T>(-1,label),_data(data){}
	OperandSymbol(int rank,double data):Symbol<T>(rank,""),_data(data){}
	virtual ~OperandSymbol(){}
	virtual T Fire(T a, T b)
	{
		return _data;
	}
	void SetData(T const& data){_data = data;}
private:
	T _data;
};

template<class T>
class CompositeOperandSymbol:public Symbol<T>
{
public:
	CompositeOperandSymbol(std::string label):Symbol<T>(-1,label){}
	CompositeOperandSymbol(int rank):Symbol<T>(rank,""){}
	virtual ~CompositeOperandSymbol(){}
	virtual T Fire(T a, T b)
	{
		T result = 0;
		if(!_symbols.empty())
		{
			int exponent = -1;
			bool leftOfDecimal = true;
			std::vector<Symbol<T>* >::iterator it = _symbols.begin();
			for(;it!=_symbols.end();it++)
			{
				if((*it)->GetRank()==0)
				{
					if(leftOfDecimal==true)
					{
						leftOfDecimal = false;
					}
					else
						throw std::invalid_argument("invalid syntax");
					continue;
				}
				if(leftOfDecimal)
				{
					result = result*10.0 + (*it)->Fire(a,b);
				}
				else
				{
					result += pow(10.0,exponent)*((*it)->Fire(a,b));
					exponent--;
				}
			}
		}
		return result;
	}
	void AddSymbol(Symbol<T>* sym){_symbols.push_back(sym);}
	void RemoveSymbol()
	{
		if(!_symbols.empty())
			_symbols.pop_back();
	}
private:
	std::vector<Symbol<T>* > _symbols;
};

template<class T>
class BinaryOperatorSymbol:public Symbol<T>
{
public:
	
	BinaryOperatorSymbol(std::string label,int rank,std::function<T(T,T)> func):Symbol<T>(rank,label),_function(func){}
	BinaryOperatorSymbol(int rank,std::function<T(T,T)> func):Symbol<T>(rank,""),_function(func){}

	virtual ~BinaryOperatorSymbol(){}
	
	void SetLeftDomain(T up, T low){_leftDomain.Set(up,low);}
	void SetRightDomain(T up, T low){_rightDomain.Set(up,low);}
	void SetRightDiscontinuity(T undefined){_rightDomain.SetUndefined(undefined);}

	virtual T Fire(T a, T b)
	{
		if(IsValid(a,b))
			return _function(a,b);
		else
			throw std::logic_error("logic error!");
	}
	bool IsValid(T const& leftArg, T const& rightArg)
	{
		bool valid = true;
		if(_leftDomain.HasConstraint())
			valid = _leftDomain.IsWithin(leftArg);
		if(_rightDomain.HasConstraint())
			valid = _rightDomain.IsWithin(rightArg);
		return valid;
	}
	
private:

	std::function<T(T,T)> _function;
	Domain<T> _rightDomain;
	Domain<T> _leftDomain;

};


#endif