#include <wx/wxprec.h>
#include "MyImage.hpp"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyHistogram {
public:
	MyHistogram(MyImage *image);
	void GetDynamic (int *minValue, int *maxValue);
	
private:
	int *tableau;
	MyImage *image;
};







