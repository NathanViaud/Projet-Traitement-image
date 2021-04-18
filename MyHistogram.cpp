#include "MyHistogram.hpp"
#include <iostream>

MyHistogram::MyHistogram(MyImage *img):image(img){
	int size = image->GetHeight()*image->GetWidth()*3;
	int save[size];
	memcpy(save, image->GetData(), size); // Sauvegarde de l'image
	image->Desaturate(); // Desaturation de l'image pour créer l'histogram
	tableau = (int*) calloc(256, 8);
	for(int i=0;i<size;i+=3){
		for(int j=0;j<255 && j<= image->GetData()[i];j++){
			if(j == image->GetData()[i]){
				tableau[j] +=1;
		}
		}
	}
	memcpy(image->GetData(), save, size); // Récupération de l'image de base
}

// Retourne la valeur min et max des pixels(nuances de gris)
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
	*minValue = min;
	*maxValue = max;
}