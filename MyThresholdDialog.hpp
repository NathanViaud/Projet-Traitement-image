#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dialog.h>
#endif

class MyThresholdDialog : public wxDialog 
{
private:	
	wxButton* m_okButton;
public:
	wxSlider* m_threshold;
	MyThresholdDialog( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
};