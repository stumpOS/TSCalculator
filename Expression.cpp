#include "Expression.h"


Expression::Expression():_state(StartState),_currentOperand(NULL)
{
	_pastStates.push(_state);
}


Expression::~Expression(void)
{
}
void Expression::BackExpression()
{
	if(!_expression.empty())
	{
		switch(_state)
		{
		case BuildingOperandAfterDecimal:
		case BuildingOperand:
			if(_currentOperand!=NULL)
				_currentOperand->RemoveSymbol();
			break;

		case StartState:
		case RightOfOperator:
			_expression.pop_back();
			break;

		default:
			break;
			
		}
		if(!_expressionString.empty())
		{
		_expressionString.pop_back();
		}
		if(!_pastStates.empty())
			_pastStates.pop();
		_state = _pastStates.top();
	}
}
void Expression::ClearExpression()
{
	_expressionString = "";
	if(!_expression.empty())
	{	
		for(expression_ptr it=_expression.begin();it!=_expression.end();)
		{
			if((*it)->GetRank()==-2)
			{
				Symbol<double> *temp = *it;
				it++;
				_expression.remove(temp);
				delete temp;
			}
			else
				it++;
		}
		_expression.clear();
	}
	_state = StartState;
}
void Expression::Evaluate()
{
	
	FunctionTree<double> functiontree;

	for(expression_ptr it = _expression.begin();it!=_expression.end();it++)
	{
		functiontree.Insert(*it);
	}

	try{
		double answer = functiontree.Evaluate();
		char buffer[50];
		int numberOfChars = sprintf(buffer,"%f",answer);
		const char *answer_str = buffer;
		_expressionString = std::string(answer_str,numberOfChars);
	}
	catch(std::logic_error const& ex)
	{
		_expressionString = ex.what();
	}
	catch(std::overflow_error const& ex)
	{
		_expressionString = "overflow";
	}
	functiontree.Clear();
}
void Expression::Update(Symbol<double>* const& symbol)
{
	bool addToExpression = true, isValid = true;

	switch(_state)
	{
	case StartState:
		
		if(symbol->GetRank()<0)
		{
			NewOperand(symbol);
			addToExpression = false;
		}
		else if(symbol->GetRank()>0)
		{
			_state = RightOfOperator;
		}
		else if(symbol->GetRank()==0)
		{
			addToExpression = false;
			isValid = false;
		}
		break;
	case BuildingOperandAfterDecimal:
		if(symbol->GetRank()==0)
		{
			isValid = false;
		}
	case BuildingOperand:
		if(symbol->GetRank()>0)
		{
			_state = RightOfOperator;
		}
		else if(isValid)
		{
			if(symbol->GetRank()==0)
			{
				_state = BuildingOperandAfterDecimal;
			}
			addToExpression = false;
			if(_currentOperand!=NULL)
			{
				_currentOperand->AddSymbol(symbol);
			}
		}
		break;

	case RightOfOperator:

		if(symbol->GetRank()<=0)
		{
			NewOperand(symbol);
		}
		else
		{
			_expression.pop_back();
			_expressionString.pop_back();
		}
		break;

	default:
		break;
	}
	if(addToExpression)
	{
		_expression.push_back(symbol);	
	}
	if(isValid)
	{
		_expressionString += symbol->GetLabel();
	}
	_pastStates.push(_state);
}
void Expression::NewOperand(Symbol<double>* symbol)
{
	_state = BuildingOperand;
	_currentOperand = new CompositeOperandSymbol<double>(-2);
	_currentOperand->AddSymbol(symbol);

	_expression.push_back(_currentOperand);
}
