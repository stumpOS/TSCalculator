#include "Key.h"


Key::Key(wxPoint pos, unsigned edgelength,Symbol *symbol):_position(pos),_size(wxSize(edgelength,edgelength)),_textColor(wxColor(0,0,0)),_backColor(wxColor(255,255,255)),_symbol(symbol)
{
	_center =wxPoint(_position.x + (_size.GetWidth()*0.25),_position.y + (_size.GetHeight()*0.25));
}


Key::~Key(void)
{
}
void Key::Draw(wxPaintDC *dc)
{
	wxBrush brush(_backColor);
	wxFont font(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	dc->SetBrush(brush);
	dc->DrawRectangle(_position.x,_position.y,_size.GetWidth(),_size.GetHeight());
	
	dc->SetFont(font);
	dc->SetTextForeground(_textColor);
	dc->SetTextBackground(_backColor);

	dc->DrawText(wxString(_symbol->GetLabel()),_center.x, _center.y);

}
bool Key::HitTest(wxPoint test)
{
	bool hit = false;
	if((test.x < _position.x + _size.GetWidth()) && (test.x > _position.x))
	{
		if(test.y < _position.y + _size.GetHeight() && test.y > _position.y)
		{
			hit = true;
		}
	}
	return hit;
}
void Key::ReverseColors()
{
	wxColor temp = _textColor;
	_textColor = _backColor;
	_backColor = temp;
}