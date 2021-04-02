#include "MyThresholdDialog.hpp"

MyThresholdDialog::MyThresholdDialog( 
	wxWindow* parent, wxWindowID id, const wxString& title, 
	const wxPoint& pos, const wxSize& size, long style ) 
: wxDialog( parent, id, title, pos, size, style )
{
	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(20,10), wxSize(100,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,60), wxSize(100,30), 0 );
}
