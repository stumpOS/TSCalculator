#pragma once
#ifndef KEY_H_
#define KEY_H_
#include <wx/wx.h>
#include "Symbol.h"
class Key
{
public:
	typedef Symbol<double> Symbol;
	Key(wxPoint pos, unsigned edgelength, Symbol *symbol);
	~Key(void);

	bool HitTest(wxPoint test);
	friend bool operator<(Key const& lhs, Key const& rhs);

	void Draw(wxPaintDC *dc);
	void Hit();
	void ReverseColors();
	Symbol *GetSymbol(){return _symbol;}
private:
	Key();
	wxPoint _position;
	wxSize _size;
	wxPoint _center;
	wxColor _textColor;
	wxColor _backColor;
	Symbol *_symbol;
};
#endif

