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
#include<wx/filedlg.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>


//constante utiles
#define APPLICATION_WIDTH	600
#define APPLICATION_HEIGHT	500 
#define WIDGET_PANEL_WIDTH	150
#define WIDGET_Y0			30
#define WIDGET_Y_STEP		50


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
	ID_CHECKPEN,
	ID_BUTTONRETURN,
	ID_BUTTONIMGRETURN
};

class MyControlPanel;


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
	void RemoveLastline();
	void Save();
	void Last();
private:
	wxBitmap m_bitmap;
	MyImage *m_image;
	MyHistogram *histo;
	int m_width;
	int m_height;
	wxPoint m_onePoint;
	wxPoint m_mousePoint;
	std::vector<wxPoint> m_points;
	bool ligneEnCours;
	bool mode_stylo;
	std::vector<MyImage*> m_save;
};


class MyControlPanel: public wxPanel{
public:
	MyControlPanel(wxWindow *parent);
	bool GetPenValue(){return m_checkPen->GetValue();};
private:
	wxCheckBox* m_checkPen;
	wxButton* m_returnButton;
	wxButton* m_imgReturn;
	void OnCheckPen(wxCommandEvent &event);
	void OnBackButton(wxCommandEvent &event);
	void OnReturnButton(wxCommandEvent &event);
	void OnImgReturnButton(wxCommandEvent &event);
};



class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	MyControlPanel* GetControlPanel(){return m_controlPanel;};
	MyPanel* GetPanel(){return m_panel;};
	void RefreshDrawing(){m_panel->Refresh();};
private:
	MyPanel *m_panel;
	MyControlPanel *m_controlPanel;
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






//************************************************************************************************//
//						MyApp													   				  //
//************************************************************************************************//


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( wxT("Hello World"), wxPoint(50, 50), wxSize(450, 340) );
	frame->Centre();
	frame->Show(true);
	wxInitAllImageHandlers();
	return true;
}


//************************************************************************************************//
//											MyControlPanel										  //
//************************************************************************************************//

MyControlPanel::MyControlPanel(wxWindow *parent): wxPanel(parent){
	 int w, h, y;
	 GetParent()->GetSize(&w, &h);
	 SetSize(wxRect(wxPoint(0,0), wxPoint(WIDGET_PANEL_WIDTH, h))) ;
	 SetBackgroundColour(*wxLIGHT_GREY) ;

	y = WIDGET_Y0;
	m_checkPen = new wxCheckBox(this, ID_CHECKPEN, "Mode Stylo", wxPoint(10, y), wxSize(100,20)) ;
	Bind(wxEVT_CHECKBOX, &MyControlPanel::OnCheckPen, this, ID_CHECKPEN) ;

	y+= WIDGET_Y_STEP;
	m_returnButton = new wxButton(this, ID_BUTTONRETURN, wxT("Return"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnReturnButton, this, ID_BUTTONRETURN) ;

	y+= WIDGET_Y_STEP;
	m_imgReturn = new wxButton(this, ID_BUTTONIMGRETURN, wxT("Return Image"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnImgReturnButton, this, ID_BUTTONIMGRETURN) ;
}

void MyControlPanel::OnCheckPen(wxCommandEvent &event){
	std::cout << "OnCheckPen" << std::endl;
}

void MyControlPanel::OnReturnButton(wxCommandEvent &event){
	MyFrame* frame = (MyFrame*)GetParent();
	frame->GetPanel()->RemoveLastline();
	frame->RefreshDrawing();
}

void MyControlPanel::OnImgReturnButton(wxCommandEvent &event){
	MyFrame* frame = (MyFrame*)GetParent();
	frame->GetPanel()->Last();
}

//************************************************************************************************//
//											MyFrame   											  //
//************************************************************************************************//


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{

	m_controlPanel = new MyControlPanel(this);
	m_panel = new MyPanel(this);
	
	
	Bind(wxEVT_MOTION, &MyFrame::MouseHandler, this);
	
	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), wxT("Cliquez ici")) ;
	menuFile->Append(ID_PlusLarge, wxT("Plus large\tCtrl--"));
	menuFile->Append(ID_MoinsLarge, wxT("Moins large\tCtrl-+"));
	menuFile->Append(ID_OpenImage, wxT("Ouvrir"));
	menuFile->AppendSeparator();
	menuFile->Append(ID_About, wxT("About\tCtrl-A")) ;
	menuFile->Append(wxID_EXIT);
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
	}
}


MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
	int w,h;
	GetParent()->GetClientSize(&w, &h);
	SetSize(wxRect(wxPoint(WIDGET_PANEL_WIDTH,0), wxPoint(w+200, h+200))) ;
	SetBackgroundColour(wxColour(0xFF,0xFF,0xFF)) ;
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
	Save();
}

void MyPanel::OnPaint(wxPaintEvent & WXUNUSED(event)){
	wxPaintDC dc(this);

	MyFrame* frame = (MyFrame*)GetParent();
	mode_stylo = frame->GetControlPanel()->GetPenValue();
	if(!mode_stylo){
		ligneEnCours = false;
		if(m_points.size()%2==1){
			m_points.pop_back();
		}
	}
	
	
	if(m_image!=nullptr){
		m_bitmap = wxBitmap(*m_image);
		dc.DrawBitmap(m_bitmap,0,0);
		if(mode_stylo && ligneEnCours){
			dc.DrawLine(m_mousePoint,m_onePoint);
		}
		wxPen pen(*wxBLACK,5,wxPENSTYLE_SOLID);
		pen.SetWidth(5);
		dc.SetPen(pen);
		if(m_points.size() > 0){
			for(int i=0;i<m_points.size()-1;i+=2){
				if(m_points[i+1] != wxPoint(0,0)){
					dc.DrawLine(m_points[i],m_points[i+1]);
				}
				
			}
		}
		
	}
}

void MyPanel::MirrorImageH(){
	if(m_image!=nullptr){
		m_image->Mirror(true);
		Save();
	}
	this->Refresh();
}

void MyPanel::MirrorImageV(){
	if(m_image!=nullptr){
		m_image->Mirror(false);
		Save();
	}
	this->Refresh();
}

void MyPanel::BlurImage(){
	if(m_image!=nullptr){
		*m_image = m_image->Blur(10);
		Save();
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
		Save();		
	}
	this->Refresh();
}

void MyPanel::NegativeImage(){
	if(m_image!=nullptr){
		m_image->Negative();
		Save();
	}
	this->Refresh();
}

void MyPanel::DesaturateImage(){
	if(m_image!=nullptr){
		m_image->Desaturate();
		int max, min;
		histo->GetDynamic(&min, &max);
		Save();
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
		Save();
	}
	this->Refresh();
}

void MyPanel::PosterizeImage(){
	if(m_image!=nullptr){
		m_image->Posterize();
		Save();
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
		Save();
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
		Save();
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
	if(m_points.size()%2 ==0){
		ligneEnCours = true;
	} else {
		ligneEnCours = false;
	}
	if(mode_stylo){
		std::cout << ligneEnCours << std::endl;
		m_onePoint.x = event.m_x;
		m_onePoint.y = event.m_y;
		m_points.push_back(m_onePoint);
		std::cout << m_points[0].x << "|"  << m_points[0].y << std::endl;
		Refresh();
	}
	
}

void MyPanel::OnMouseMove(wxMouseEvent &event){
	if(ligneEnCours == true){
		m_mousePoint.x = event.m_x;
		m_mousePoint.y = event.m_y;
	}
	Refresh();
}

void MyPanel::RemoveLastline(){
	if(m_points.size()>1 && !ligneEnCours){
		m_points.pop_back();
		m_points.pop_back();
	}
}

void MyPanel::Save(){
	int size = m_image->GetHeight()*m_image->GetWidth()*3;
	MyImage* save = new MyImage(m_image->GetWidth(), m_image->GetHeight());
	memcpy(save->GetData(), m_image->GetData(), size);
	m_save.push_back(save);
}

void MyPanel::Last(){
	if(m_save.size()>1){
		m_save.pop_back();
	}
	std::cout<< "Last" << std::endl;
	int size = m_image->GetHeight()*m_image->GetWidth()*3;
	memcpy(m_image->GetData(), m_save[m_save.size()-1]->GetData(), size);
	this->Refresh();
}