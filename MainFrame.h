#pragma once
#ifndef MAINFRAME_H_
#define MAINFRAME_H_
#include <wx/wx.h>
#include "Document.h"
class ViewEdit;
class ViewExpression;
class MainFrame:public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame(void);
	enum ID{ID_Submit,ID_Clear,ID_Back};

	void OnExit(wxCommandEvent& event);
	void OnSubmit(wxCommandEvent& event);
	void OnClear(wxCommandEvent& event);
	void OnBack(wxCommandEvent& event);

	void CreateMenuBar();
	void CreateInterface();
	void CreateEditButtons(wxBoxSizer &sizer);

	Document *GetDocument(){return _document;}

	wxDECLARE_EVENT_TABLE();
private:
	wxButton *_submit;
	wxButton *_clear;
	wxButton *_back;

	ViewEdit *_viewEdit;
	ViewExpression *_viewExpression;

	Document *_document;
};
#endif

