#include "MainFrame.h"
#include "ViewEdit.h"
#include "ViewExpression.h"
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_BUTTON(ID_Submit,MainFrame::OnSubmit)
	EVT_BUTTON(ID_Back,MainFrame::OnBack)
	EVT_BUTTON(ID_Clear,MainFrame::OnClear)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size)
{
	int width,height;
	GetClientSize(&width,&height);
	_document = new Document(wxSize(width,height*0.8));
	
	CreateMenuBar();
	CreateInterface();
}



MainFrame::~MainFrame(void)
{
	DestroyChildren();
	delete _document;
}
void MainFrame::CreateMenuBar()
{
	wxMenu *menuMore = new wxMenu;
	menuMore->Append(wxID_EXIT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuMore, "&More" );
	SetMenuBar( menuBar );
}
void MainFrame::CreateInterface()
{
	int width,height;
	GetClientSize(&width,&height);

	_viewEdit = new ViewEdit(this,_document->GetSize());
	_viewExpression = new ViewExpression(this,wxSize(width,height*0.1));

	wxBoxSizer *vSizer = new wxBoxSizer(wxVERTICAL);
	vSizer->Add(_viewExpression,0,wxEXPAND,0);
	vSizer->Add(_viewEdit,1,wxEXPAND,0);

	wxBoxSizer *sizerToHoldButtons = new wxBoxSizer(wxHORIZONTAL);
	CreateEditButtons(*sizerToHoldButtons);

	vSizer->Add(sizerToHoldButtons,0,wxEXPAND,0);
	
	SetSizer(vSizer);
	vSizer->Fit(this);
	
}
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close();
}
void MainFrame::OnSubmit(wxCommandEvent& event)
{
	_document->Evaluate();
}
void MainFrame::OnBack(wxCommandEvent& event)
{
	_document->BackExpression();
}
void MainFrame::OnClear(wxCommandEvent& event)
{
	_document->ClearExpression();
}
void MainFrame::CreateEditButtons(wxBoxSizer &sizer)
{
	_submit = new wxButton(this,ID_Submit,wxString("="));
	_clear = new wxButton(this,ID_Clear,wxString("clear"));
	_back = new wxButton(this,ID_Back,wxString("back"));

	sizer.Add(_submit,1,wxEXPAND,0);
	sizer.Add(_clear,1,wxEXPAND,0);
	sizer.Add(_back,1,wxEXPAND,0);
}