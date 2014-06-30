#pragma once
#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include <list>
#include <vector>
#include <string>
#include <wx/wx.h>
#include "Iterator.h"
#include "DocumentObserver.h"
#include "Symbol.h"
#include "SimpleCalculator.h"
#include "Key.h"
#include "Expression.h"
#define MIN(a,b) (a < b ? a:b)
#define COL 4
class Document
{
	typedef std::list<DocumentObserver*>::iterator observer_iter;
	typedef std::vector<Key*>::iterator key_iter;
public:
	Document(wxSize size);
	~Document(void);
	void AddObserver(DocumentObserver *listener);
	void RemoveObserver(DocumentObserver *listener);
	void Draw(wxPaintDC *dc);
	void UpdateObservers();
	wxSize &GetSize(){return _size;}
	std::string const& GetExpressionAsString();
	void Evaluate();
	friend class KeyIterator;
	class KeyIterator:public Iterator<Key*>
	{
	public:
		KeyIterator(Document *doc){_document = doc;_iter = _document->_keys.begin();}
		virtual void First(){_iter = _document->_keys.begin();}
		virtual void Next(){_iter++;}
		virtual bool IsDone(){return _iter ==_document->_keys.end();}
		virtual Key *Current(){return *_iter;}
	private:
		KeyIterator(){}
		Document *_document;
		key_iter _iter;
	};
	KeyIterator *GetKeys(){return new KeyIterator(this);}
	
	void HitKey(Key *key);
	void ReleaseKey();
	void ClearExpression();
	void BackExpression();
private:
	void CreateKeys();
	void ClearKeys();

	wxSize _size;
	std::list<DocumentObserver*> _listeners;
	std::vector<Key*> _keys;
	Key* _lastHitKey;
	SimpleCalculator *_calculator;
	Expression _expression;
};
#endif

