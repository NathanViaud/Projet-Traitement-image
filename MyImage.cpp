#include "MyImage.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

MyImage::MyImage(const wxString& fileName):wxImage(fileName){
}

MyImage::MyImage(wxImage image):wxImage(image){
	
}

MyImage::MyImage(int largeur, int hauteur):wxImage(largeur, hauteur){
	
}

MyImage::MyImage():wxImage(){
	
}

void MyImage::Negative(){
	for(int i=0;i<(this->GetHeight()*this->GetWidth()*3);i++){
		this->GetData()[i] = 255 - this->GetData()[i];
	}
}

// Transforme l'image en nuances de gris
void MyImage::Desaturate(){
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i+=3){
		float l = this->GetData()[i]*0.2126+this->GetData()[i+1]*0.7152+this->GetData()[i+2]*0.0722;
		this->GetData()[i] = l;
		this->GetData()[i+1] = l;
		this->GetData()[i+2] = l;
	}
}

// Seuillage en noir et blanc de l'image
void MyImage::Threshold(int seuil){
	this->Desaturate();
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i+=3){
		if(this->GetData()[i] <=seuil){
			this->GetData()[i] = 0;
			this->GetData()[i+1] = 0;
			this->GetData()[i+2] = 0;
		} else {
			this->GetData()[i] = 255;
			this->GetData()[i+1] = 255;
			this->GetData()[i+2] = 255;
		}
	}
}


void MyImage::Mirror(bool horizontaly){  //ça marche pas
	int m = this->GetWidth()/2;
	
	for(int y =1; y<this->GetHeight();y++){
		for(int x=0;x<m;x+=3){
			int indice_courant = x*y;
			int indice_dest = this->GetWidth()*y-x-2;
			int sauv = this->GetData()[indice_courant];
			this->GetData()[indice_courant] = this->GetData()[indice_dest];
			this->GetData()[indice_dest] = sauv;
			sauv = this->GetData()[indice_courant+1];
			this->GetData()[indice_courant+1] = this->GetData()[indice_dest+1];
			this->GetData()[indice_dest+1] = sauv;
			sauv = this->GetData()[indice_courant+2];
			this->GetData()[indice_courant+2] = this->GetData()[indice_dest+2];
			this->GetData()[indice_dest+2] = sauv;
		}
	}
	
}

MyImage MyImage::Rotate90(){
        
	unsigned char* data = this->GetData();
	
	MyImage nouvelle(this->GetHeight(),this->GetWidth());
	unsigned char* newdata = nouvelle.GetData();
	
	int height = this->GetHeight() ;    int width = this->GetWidth() ;  
	
	for(int ligne = 0; ligne<height ; ligne++){
		for(int colonne = 0; colonne<width; colonne++){
			newdata[ (colonne*height+height-ligne-1)*3      ]=data[(ligne*width+colonne)*3];
			newdata[ (colonne*height+height-ligne-1)*3+1 ]=data[(ligne*width+colonne)*3+1];
			newdata[ (colonne*height+height-ligne-1)*3+2 ]=data[(ligne*width+colonne)*3+2];
		}
	}
	
	return nouvelle;
}

// Posterisation en 8 couleurs
void MyImage::Posterize(){
	for(int i=0;i<(this->GetHeight()*this->GetWidth()*3);i++){
		if(this->GetData()[i]>127){
			this->GetData()[i] = 255;
		} else{
			this->GetData()[i] = 0;
		}
	}
}

int MyImage::ComptageCouleurs(){
	bool* couleurs = new bool[256*256*256];

	for(int i = 0; i< (256*256*256); i++){
		couleurs[i] = false;
	}

	int nb_couleurs = 0;
	unsigned long int size = GetHeight() * GetWidth() * 3;

	unsigned char* buffer = GetData();

	for(unsigned long int i=0;i<size;i+=3){
		int index = (buffer[i] << 16) + (buffer[i+1] << 8) + (buffer[i+2]);
		if(!couleurs[index]){
			couleurs[index] = true;
			nb_couleurs++;
		}
	}

	return nb_couleurs;

}

// Améliore le contraste d'une image ne nuance de gris
void MyImage::EnhenceContrast(int minValue, int maxValue){
	int d = (255*minValue) /(maxValue-minValue);
	int f = 255 /(maxValue-minValue);
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i++){
		this->GetData()[i] = f * this->GetData()[i] + d;
	}
	
}

// Augmente la luminosité de l'image
void MyImage::Luminosity(int dl){
	unsigned char* buffer = this->GetData();
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i++){
		if(buffer[i]+dl > 255){
			buffer[i] = 255;
		} else{
			buffer[i] = buffer[i] + dl;
		}
	}
}

