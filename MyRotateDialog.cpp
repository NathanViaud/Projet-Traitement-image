#include "MyRotateDialog.hpp"

#include <wx/intl.h>
#include <wx/string.h>

MyRotateDialog::MyRotateDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
:wxDialog(parent, id, wxT("Rotation"), pos, size)
{
  SetClientSize(wxSize(200,150));
 // Move(wxDefaultPosition);
  wxString __wxRadioBoxChoices_1[3] =
  {
    wxT("90    "),
    wxT("180   "),
    wxT("-90   ")
  };
  RadioBox1 = new wxRadioBox(this, wxID_ANY, _("Rotation angle"), wxPoint(16,8), wxSize(175,90), 3, __wxRadioBoxChoices_1, 3, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
  Button1 = new wxButton(this, wxID_OK, _("OK"), wxPoint(16,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
  Button2 = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}