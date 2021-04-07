#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
//#include "MyImage.hpp"
#include <iostream>
#include <string>
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.hpp"
#include "MyHistogram.hpp"
#include <vector>



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
	//void OnThresholdImage(wxCommandEvent& event);
	void LuminosityImage();
	void SaveFile(wxString fileName);
	void OnMouseLeftDown(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void PenImage();
private:
	wxBitmap m_bitmap;
	MyImage *m_image;
	MyHistogram *histo;
	int m_width;
	int m_height;
	wxPoint m_onePoint;
	wxPoint m_mousePoint;
	std::vector<wxPoint> m_points;
	bool mode_pen = false;
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
	void OnProcessImage(wxCommandEvent& event);
	void OnSaveFile(wxCommandEvent& WXUNUSED(event));
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
	ID_EContrast,
	ID_Luminosity,
	ID_SaveFile,
	ID_Pen
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
	menuFile->Append(ID_SaveFile, wxT("Save"));

	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;
	Bind(wxEVT_MENU, &MyFrame::OnPlusLarge, this, ID_PlusLarge);
	Bind(wxEVT_MENU, &MyFrame::OnMoinsLarge, this, ID_MoinsLarge);
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_OpenImage);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnSaveFile, this,ID_SaveFile );

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
	menuProcess->Append(ID_Luminosity, wxT("Add Luminosity"));
	menuProcess->Append(ID_Pen, wxT("Mode stylo"));

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
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Luminosity);
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Pen);
	
	
	
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

void MyFrame::OnSaveFile(wxCommandEvent& WXUNUSED(event)){
	wxString filename = wxSaveFileSelector(wxT("Save file as"), wxT("*.png"), wxT("data"));
	if(!filename.empty()){
		m_panel->SaveFile(filename);
	}
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
		case ID_Luminosity:
			m_panel->LuminosityImage();
			break;
		case ID_Pen:
			m_panel->PenImage();
			break;
	}
}

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
	Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
	m_image = nullptr;
	m_onePoint = wxPoint(0,0);
	m_mousePoint = m_onePoint;
	Bind(wxEVT_MOTION, &MyPanel::OnMouseMove, this);
	Bind(wxEVT_LEFT_DOWN, &MyPanel::OnMouseLeftDown, this);
	//Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
}

MyPanel::~MyPanel() {}

void MyPanel::OpenImage(wxString fileName){
	m_image = new MyImage(fileName);
	histo = new MyHistogram(m_image);
	m_width = m_image->GetWidth();
	m_height = m_image->GetHeight();
	this->GetParent()->SetSize(m_width+100,m_height+100);
	this->Refresh();
}

void MyPanel::OnPaint(wxPaintEvent & WXUNUSED(event)){
	wxPaintDC dc(this);
	
	if(m_image!=nullptr){
		m_bitmap = wxBitmap(*m_image);
		dc.DrawBitmap(m_bitmap,0,0);
		wxPen pen(*wxBLACK,5,wxPENSTYLE_SOLID);
		pen.SetWidth(5);
		dc.SetPen( pen );
		if(mode_pen){
			//dc.DrawCircle(wxPoint(m_onePoint),50);
			dc.DrawLine(m_mousePoint,m_onePoint);
		}
		if(m_points.size() > 0){
			for(int i=0;i<m_points.size();i+=2){
				dc.DrawLine(m_points[i],m_points[i+1]);
				std::cout << "p1 x: "<< m_points[i].x <<"p1 y: " <<m_points[i].y <<"p2 x: " <<m_points[i+1].x <<"p2 y: " <<m_points[i+1].y << std::endl;
			}
		}
		
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
				std::cout << "erreur" << std::endl;
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

//void MyPanel::ThresholdImage(){ //V1
//	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
//	dlg->ShowModal() ;
//	if(m_image!=nullptr){
//		m_image->Threshold(dlg->m_threshold->GetValue());
//	}
//	this->Refresh();
//}

void MyPanel::ThresholdImage(){			//V2
	int size = m_image->GetHeight()*m_image->GetWidth()*3;
	int save[size];

	memcpy(save, m_image->GetData(), size);
	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
	if(m_image!=nullptr){
		int res = dlg->ShowModal();
		if(res == wxID_OK){
			m_image->Threshold(dlg->m_threshold->GetValue());
		} else if(res == wxID_CANCEL){
			memcpy(m_image->GetData(), save, size);
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

// void MyPanel::OnThresholdImage(wxCommandEvent& event){     	//TP7 marche pas complétement mais pas obligatoire pour l'app finale
// 	//std::cout << "OnThresholdImage" << std::endl;
// 	std::cout << event.GetInt() << std::endl;
// 	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250, 140));
// 	if(m_image!=nullptr){
// 		if(wxID_OK){
// 			m_image->Luminosity(event.GetInt());
// 		}
// 	}
	
// }


//Augmente la luminosité de l'image
void MyPanel::LuminosityImage(){
	int size = m_image->GetHeight()*m_image->GetWidth()*3;
	int save[size];

	memcpy(save, m_image->GetData(), size);
	MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Luminosity"), wxDefaultPosition, wxSize(250, 140));
	if(m_image!=nullptr){
		int res = dlg->ShowModal();
		if(res == wxID_OK){
			m_image->Luminosity(dlg->m_threshold->GetValue());
		} else if(res == wxID_CANCEL){
			memcpy(m_image->GetData(), save, size);
		}
	}
	this->Refresh();
}

void MyPanel::SaveFile(wxString fileName)
//------------------------------------------------------------------------
{
	// just to create a tiny file
	FILE* f = fopen(fileName, "w") ;
	if (!f)
		wxMessageBox(wxT("Cannot save file"));
	else
	{
		this->SaveFile(fileName);
	}
}

void MyPanel::OnMouseLeftDown(wxMouseEvent &event){
	if(m_onePoint== wxPoint(0,0)){
		m_points.push_back(m_mousePoint);
	} else{
		m_points.push_back(m_onePoint);
	}
	m_onePoint.x = event.m_x;
	m_onePoint.y = event.m_y;
	m_points.push_back(m_onePoint);
	Refresh();
}

void MyPanel::OnMouseMove(wxMouseEvent &event){
	m_mousePoint.x = event.m_x;
	m_mousePoint.y = event.m_y;
	Refresh();
}

void MyPanel::PenImage(){
	mode_pen = !mode_pen;
}