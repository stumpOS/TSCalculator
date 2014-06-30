#include "ViewExpression.h"
BEGIN_EVENT_TABLE(ViewExpression,wxWindow)
	EVT_PAINT(ViewExpression::OnPaint)
END_EVENT_TABLE()

ViewExpression::ViewExpression(MainFrame *parent,wxSize s):wxWindow(parent,wxID_ANY,wxDefaultPosition,s,wxBORDER_SIMPLE),DocumentObserver(parent->GetDocument()),_parent(parent)
{
	_textColor = wxColor(0,0,0);
	_backColor = wxColor(255,255,255);
	CreateInterface();
}

ViewExpression::~ViewExpression(void)
{
	DestroyChildren();
}
void ViewExpression::CreateInterface()
{
	int width,height;
	GetClientSize(&width,&height);
	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

	_expression = new wxTextCtrl(this,wxID_ANY,"",wxDefaultPosition,wxSize(width,height),wxTE_RIGHT|wxTE_READONLY,wxDefaultValidator);
	hSizer->Add(_expression,1,wxEXPAND,0);
	SetSizer(hSizer);
	hSizer->Fit(this);

	wxFont font(28, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	_expression->SetDefaultStyle(wxTextAttr(_textColor,_backColor,font,wxTEXT_ALIGNMENT_RIGHT));
	Refresh();
}
void ViewExpression::OnPaint(wxPaintEvent &event)
{
	std::string expression = _parent->GetDocument()->GetExpressionAsString();
	_expression->SetValue(wxString(expression));
}
void ViewExpression::Observe()
{
	Refresh();
}