
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyImage : public wxImage{
public:
	MyImage(const wxString& fileName);
	MyImage(wxImage image);
	MyImage(int largeur, int hauteur);
	MyImage();
	void Negative();
	void Desaturate();
	void Threshold(int seuil);
	void Mirror(bool horizontally);
	MyImage Rotate90();
	void Posterize();
	int ComptageCouleurs();
	void EnhenceContrast(int minValue, int maxValue);
};