#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "MainFrame.h"
class CalculatorApp: public wxApp
{
public:
	virtual bool OnInit();
};
wxIMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
	MainFrame *frame = new MainFrame( "Calculator", wxPoint(100, 100), wxSize(475, 310) );
	frame->Show( true );
	return true;
}