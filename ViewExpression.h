#pragma once
#ifndef VIEWEXPRESSION_H_
#define VIEWEXPRESSION_H_
#include <wx/wx.h>
#include <string>
#include "MainFrame.h"
#include "DocumentObserver.h"

class ViewExpression:public wxWindow, public DocumentObserver
{
public:
	ViewExpression(MainFrame *parent,wxSize size);
	virtual ~ViewExpression(void);
	void OnPaint(wxPaintEvent &event);

	virtual void Observe();
	void CreateInterface();
	wxDECLARE_EVENT_TABLE();

private:
	MainFrame *_parent;
	wxTextCtrl *_expression;
	wxColor _textColor;
	wxColor _backColor;
};
#endif

