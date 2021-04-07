#include "MyHistogram.hpp"
#include <iostream>

MyHistogram::MyHistogram(MyImage *img):image(img){
	int size = image->GetHeight()*image->GetWidth()*3;
	int save[size];
	memcpy(save, image->GetData(), size);
	image->Desaturate();
	tableau = (int*) calloc(256, 8);
	for(int i=0;i<size;i+=3){
		for(int j=0;j<255 && j<= image->GetData()[i];j++){
			if(j == image->GetData()[i]){
				tableau[j] +=1;
		}
		}
	}
	memcpy(image->GetData(), save, size);
}

void MyHistogram::GetDynamic(int *minValue, int *maxValue){
	int min, max;
	bool init = false;
	for(int i=0; i <= 255;i++){
		if(tableau[i] > 0){
			if(!init){
				init = true;
				max = i;
				min = i;
			}
			else if( i < min ){
				min = i;
			} else if( i > max){
				max = i;
			}
		}
	}
	std::cout << "Hmin: " << min << std::endl;
	std::cout << "Hmax: " << max << std::endl;
	*minValue = min;
	*maxValue = max;
}