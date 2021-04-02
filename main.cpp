#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
//#include "MyImage.hpp"
#include <iostream>
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.hpp"
#include "MyHistogram.hpp"

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

class MyPanel: public wxPanel{
public:
	MyPanel(wxWindow *parent);
	~MyPanel();
	void OpenImage(wxString fileName);
	void OnPaint(wxPaintEvent &WXUNUSED(event));
	void MirrorImageH();
	void MirrorImageV();
	void BlurImage();
	void RotationImage();
	void NegativeImage();
	void DesaturateImage();
	void ThresholdImage();
	void PosterizeImage();
	void ComptageCouleursImage();
	void EnhenceContrastImage();
private:
	wxBitmap m_bitmap;
	MyImage *m_image;
	MyHistogram *histo;
	int m_width;
	int m_height;

};

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	MyPanel *m_panel;
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnEC(wxCommandEvent& event);
	void OnPlusLarge(wxCommandEvent& event);
	void OnMoinsLarge(wxCommandEvent& event);
	void MouseHandler(wxMouseEvent& event);
	void OnOpenImage(wxCommandEvent& event);
	void OnMirrorV(wxCommandEvent& event);
	void OnMirrorH(wxCommandEvent& event);
	void OnBlur(wxCommandEvent& event);
	void OnRotation(wxCommandEvent& event);
	void OnProcessImage(wxCommandEvent& event);
};

enum	// énumération. Elle gère la numérotation automatiquement 
{
	ID_Hello = 1,
	ID_About,	// ID_Truc a pour valeur 2 
	ID_EC,	// ID_Machin a pour valeur 3 
	ID_PlusLarge,
	ID_MoinsLarge,
	ID_OpenImage,
	ID_MirrorV,
	ID_MirrorH,
	ID_Blur,
	ID_Rotation,
	ID_Negative,
	ID_Desaturate,
	ID_Threshold,
	ID_Posterize,
	ID_Comptage,
	ID_EContrast
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( wxT("Hello World"), wxPoint(50, 50), wxSize(450, 340) );
	frame->Centre();
	frame->Show(true);
	wxInitAllImageHandlers();
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	
	m_panel = new MyPanel(this);
	
	 Bind(wxEVT_MOTION, &MyFrame::MouseHandler, this);
	
	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), wxT("Cliquez ici")) ;
	menuFile->Append(ID_PlusLarge, wxT("Plus large\tCtrl--"));
	menuFile->Append(ID_MoinsLarge, wxT("Moins large\tCtrl-+"));
	menuFile->Append(ID_OpenImage, wxT("Ouvrir"));
	menuFile->AppendSeparator();
	menuFile->Append(ID_About, wxT("About\tCtrl-A")) ;
	menuFile->Append(wxID_EXIT) ;

	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;
	Bind(wxEVT_MENU, &MyFrame::OnPlusLarge, this, ID_PlusLarge);
	Bind(wxEVT_MENU, &MyFrame::OnMoinsLarge, this, ID_MoinsLarge);
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_OpenImage);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

	wxMenu  *menuHelp = new wxMenu;
	menuHelp->Append(ID_EC, wxT("En cours\tCtrl-E"));
	Bind(wxEVT_MENU, &MyFrame::OnEC, this, ID_EC);

	wxMenu *menuProcess = new wxMenu;
	menuProcess->Append(ID_MirrorV, wxT("MirrorV"));
	menuProcess->Append(ID_MirrorH, wxT("MirrorH"));
	menuProcess->Append(ID_Blur, wxT("Blur"));
	menuProcess->Append(ID_Rotation, wxT("Rotation"));
	menuProcess->Append(ID_Negative, wxT("Negative"));
	menuProcess->Append(ID_Desaturate, wxT("Desaturate"));
	menuProcess->Append(ID_Threshold, wxT("Threshold"));
	menuProcess->Append(ID_Posterize, wxT("Posterize"));
	menuProcess->Append(ID_Comptage, wxT("Comptage couleurs"));
	menuProcess->Append(ID_EContrast, wxT("Enhence contrast"));

	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorV);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorH);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotation);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Posterize);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Comptage);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_EContrast);
	
	
	
	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
	menuBar->Append( menuHelp, wxT("Help"));
	menuBar->Append( menuProcess, wxT("Process"));
	SetMenuBar(menuBar) ;

	CreateStatusBar(1);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event) {
	wxLogMessage(wxT("Auteur : nathan"));
}

void MyFrame::OnEC(wxCommandEvent& event) {
	wxLogMessage(wxT("En cours de construction"));
}

void MyFrame::OnMoinsLarge(wxCommandEvent& event) {
	int w;
	int h;
	this->GetSize(&w,&h);
	this->SetSize(w-100,h);
}

void MyFrame::OnPlusLarge(wxCommandEvent& event) {
	int w;
	int h;
	this->GetSize(&w,&h);
	this->SetSize(w+100,h);
}

void MyFrame::OnOpenImage(wxCommandEvent& event){
	wxString fileName = wxFileSelector("Choose a file to open");
	if(!fileName.empty()){
		wxLogMessage(wxT("Fichier correct"));
		m_panel->OpenImage(fileName);
	} else {
		wxLogMessage(wxT("Une erreur est survenue"));
	}
}

void MyFrame::MouseHandler(wxMouseEvent& event){
	std::string mousePos = std::to_string(event.m_x) + " | " + std::to_string(event.m_y);
	SetStatusText(mousePos, 0);
}

void MyFrame::OnMirrorV(wxCommandEvent& event){
	m_panel->MirrorImageV();
}

void MyFrame::OnMirrorH(wxCommandEvent& event){
	m_panel->MirrorImageH();
}

void MyFrame::OnBlur(wxCommandEvent& event){
	m_panel->BlurImage();
}

void MyFrame::OnRotation(wxCommandEvent& event){
	m_panel->RotationImage();
}

void MyFrame::OnProcessImage(wxCommandEvent& event){
	switch(event.GetId()){
		case ID_Blur:
			m_panel->BlurImage();
			break;
		case ID_MirrorH:
			m_panel->MirrorImageH();
			break;
		case ID_MirrorV:
			m_panel->MirrorImageV();
			break;
		case ID_Rotation:
			m_panel->RotationImage();
			break;
		case ID_Negative:
			m_panel->NegativeImage();
			break;
		case ID_Desaturate:
			m_panel->DesaturateImage();
			break;
			
		case ID_Threshold:
			m_panel->ThresholdImage();
			break;
		case ID_Posterize:
			m_panel->PosterizeImage();
			break;
		case ID_Comptage:
			m_panel->ComptageCouleursImage();
			break;
		case ID_EContrast:
			m_panel->EnhenceContrastImage();
			break;
	}
}

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	m_image = nullptr;
}

MyPanel::~MyPanel() {}

void MyPanel::OpenImage(wxString fileName){
	m_image = new MyImage(fileName);
	histo = new MyHistogram(m_image);
//	m_width = m_image->GetWidth();
//	m_height = m_image->GetHeight();
//	this->GetParent()->SetSize(m_width,m_height);
	this->Refresh();
}

void MyPanel::OnPaint(wxPaintEvent & WXUNUSED(event)){
	wxPaintDC dc(this);
	if(m_image!=nullptr){
		m_bitmap = wxBitmap(*m_image);
		dc.DrawBitmap(m_bitmap,0,0);
	}
}

void MyPanel::MirrorImageH(){
	if(m_image!=nullptr){
		m_image->Mirror(true);
	}
	this->Refresh();
}

void MyPanel::MirrorImageV(){
	if(m_image!=nullptr){
		m_image->Mirror(false);
	}
	this->Refresh();
	
}

void MyPanel::BlurImage(){
	if(m_image!=nullptr){
		*m_image = m_image->Blur(10);
	}
	this->Refresh();
}

void MyPanel::RotationImage(){
	MyRotateDialog *dlg = new MyRotateDialog(this, -1);
	if(m_image!=nullptr){
		if(dlg->ShowModal() == wxID_OK){
			if(dlg->RadioBox1->GetSelection() == 0){
				*m_image = m_image->Rotate90();
			} else if (dlg->RadioBox1->GetSelection() == 1){
				*m_image = m_image->Rotate180();
			} else{
				std::cout << "ça marche pas" << std::endl;
			}
		}
	}
	this->Refresh();
}

void MyPanel::NegativeImage(){
	if(m_image!=nullptr){
		m_image->Negative();
	}
	this->Refresh();
}

void MyPanel::DesaturateImage(){
	if(m_image!=nullptr){
		m_image->Desaturate();
		int max, min;
		histo->GetDynamic(&min, &max);
	}
	this->Refresh();
}

//void MyPanel::ThresholdImage(){
//	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
//	dlg->ShowModal() ;
//	if(m_image!=nullptr){
//		m_image->Threshold(dlg->m_threshold->GetValue());
//	}
//	this->Refresh();
//}

void MyPanel::ThresholdImage(){			//V2
	MyImage *save = new MyImage();
	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
	if(m_image!=nullptr){
		if(dlg->ShowModal() == wxID_OK){
			m_image->Threshold(dlg->m_threshold->GetValue());
		} else if(dlg->ShowModal() == wxID_CANCEL){
			//m_image = *save->Copy();
		}
	}
	this->Refresh();
}

void MyPanel::PosterizeImage(){
	if(m_image!=nullptr){
		m_image->Posterize();
	}
	this->Refresh();
}

void MyPanel::ComptageCouleursImage(){
	if(m_image!=nullptr){
		wxString couleurs = std::to_string(m_image->ComptageCouleurs());
		wxLogMessage(couleurs);
		
	}
}

void MyPanel::EnhenceContrastImage(){
	if(m_image!=nullptr){
		int min, max;
		histo->GetDynamic(&min, &max);
		std::cout << "Emin: " << min << std::endl;
		std::cout << "Emax: " << max << std::endl;
		m_image->EnhenceContrast(min, max);
		this->Refresh();
		MyHistogram *hist = new MyHistogram(m_image);
		hist->GetDynamic(&min, &max);
	}
	
}

