#ifndef MYROTATEDIALOG_H
#define MYROTATEDIALOG_H

#include <wx/radiobox.h>
#include <wx/button.h>
#include <wx/dialog.h>

class MyRotateDialog: public wxDialog
{
  public:
    MyRotateDialog(wxWindow* parent,
       wxWindowID id=wxID_ANY,
       const wxPoint& pos=wxDefaultPosition,
       const wxSize& size=wxDefaultSize);
    wxButton* Button1;
    wxButton* Button2;
    wxRadioBox* RadioBox1;
};

#endif