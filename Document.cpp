#include "Document.h"


Document::Document(wxSize size):_size(size)
{
	_lastHitKey = NULL;
	_calculator = new SimpleCalculator();
	CreateKeys();
}

Document::~Document(void)
{
	ClearKeys();
	delete _calculator;
}
void Document::ClearExpression()
{
	_expression.ClearExpression();
	UpdateObservers();
}
void Document::BackExpression()
{
	_expression.BackExpression();
	UpdateObservers();
}
std::string const& Document::GetExpressionAsString()
{
	return _expression.GetExpressionAsString();
}
void Document::Evaluate()
{
	_expression.Evaluate();
	UpdateObservers();
}
void Document::AddObserver(DocumentObserver *observer)
{
	_listeners.push_back(observer);
}
void Document::RemoveObserver(DocumentObserver *observer)
{
	_listeners.remove(observer);
}
void Document::UpdateObservers()
{
	observer_iter it = _listeners.begin();
	for(;it!=_listeners.end();it++)
	{
		(*it)->Observe();
	}
}
void Document::Draw(wxPaintDC *dc)
{
	key_iter it= _keys.begin();
	for(;it!=_keys.end();it++)
	{
		(*it)->Draw(dc);
	}
}
void Document::HitKey(Key *key)
{
	key->ReverseColors();
	_lastHitKey = key;
	_expression.Update(key->GetSymbol());
}
void Document::CreateKeys()
{
	IteratorPtr<Symbol<double>*> iter = _calculator->GetSymbols();

	float min = MIN(_size.GetWidth(),_size.GetHeight());
	float edgeLength = (int)((float)min/((float)COL));

	float xStart = 0,yStart = 0;
	wxPoint pos(xStart,yStart);
	
	int colCount = 1;

	for(iter->First();!iter->IsDone();iter->Next())
	{
		Key *key = new Key(pos,edgeLength,iter->Current());
		
		_keys.push_back(key);

		if(colCount>=COL)
		{
			pos.x = xStart;
			pos.y += edgeLength;
			colCount = 1;
		}
		else
		{
			colCount++;
			pos.x += edgeLength;
		}
	}
}
void Document::ReleaseKey()
{
	if(_lastHitKey!=NULL)
	{
		_lastHitKey->ReverseColors();
	}
}
void Document::ClearKeys()
{
	if(!_keys.empty())
	{
		key_iter it = _keys.begin();
		for(;it!=_keys.end();)
		{
			Key* temp = *it;
			it++;
			delete temp;
			temp = NULL;
		}
		_keys.clear();
	}
}