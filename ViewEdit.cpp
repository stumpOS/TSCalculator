#include "ViewEdit.h"
BEGIN_EVENT_TABLE(ViewEdit, wxWindow)
	EVT_PAINT(ViewEdit::OnPaint)
	EVT_LEFT_DOWN(ViewEdit::OnLeftButtonDown)
	EVT_LEFT_UP(ViewEdit::OnLeftButtonUp)
END_EVENT_TABLE()

ViewEdit::ViewEdit(MainFrame *parent,wxSize s):wxWindow(parent,wxID_ANY,wxDefaultPosition,s,wxBORDER_SIMPLE),DocumentObserver(parent->GetDocument()),_parent(parent)
{
}


ViewEdit::~ViewEdit(void)
{
}
void ViewEdit::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	_parent->GetDocument()->Draw(&dc);

}

void ViewEdit::OnLeftButtonDown(wxMouseEvent &event)
{
	int x,y;
	x = event.m_x;
	y = event.m_y;
	Document *document = _parent->GetDocument();
	IteratorPtr<Key*> iter = document->GetKeys();
	for(iter->First();!iter->IsDone(); iter->Next())
	{
		if(iter->Current()->HitTest(wxPoint(x,y)))
		{
			document->HitKey(iter->Current());
			document->UpdateObservers();
		}
	}
}
void ViewEdit::OnLeftButtonUp(wxMouseEvent &event)
{	
	_parent->GetDocument()->ReleaseKey();
	Refresh();
}
void ViewEdit::Observe()
{
	Refresh();
}