#pragma once
#ifndef VIEWEDIT_H_
#define VIEWEDIT_H_
#include "wx/wx.h"
#include "MainFrame.h"
#include "DocumentObserver.h"
class ViewEdit:public wxWindow,public DocumentObserver
{
public:
	ViewEdit(MainFrame* parent,wxSize s);
	virtual ~ViewEdit(void);
	void OnPaint(wxPaintEvent &event);
	void OnLeftButtonDown(wxMouseEvent &event);
	void OnLeftButtonUp(wxMouseEvent &event);
	virtual void Observe();
	wxDECLARE_EVENT_TABLE();
private:
	MainFrame *_parent;
};
#endif

