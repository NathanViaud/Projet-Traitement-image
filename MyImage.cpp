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

void MyImage::Desaturate(){
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i+=3){
		float l = this->GetData()[i]*0.2126+this->GetData()[i+1]*0.7152+this->GetData()[i+2]*0.0722;
		this->GetData()[i] = l;
		this->GetData()[i+1] = l;
		this->GetData()[i+2] = l;
	}
}

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

void MyImage::Mirror(bool horizontaly){
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
	
//	for(int i =0; i< (this->GetHeight()) ;i++){
//		for(int j=0;j<m;j+=3){
//			int rouge = this->GetData()[i*j];
//			int vert = this->GetData()[i*j+1];
//			int bleu = this->GetData()[i*j+2];
//			this->GetData()[i*j] = this->GetData()[i*this->GetWidth() - j];
//			this->GetData()[i*j+1] = this->GetData()[i*this->GetWidth() - (j+1)];
//			this->GetData()[i*j+2] = this->GetData()[i*this->GetWidth() - (j+2)];
//			this->GetData()[i*this->GetWidth() - j] = rouge;
//			this->GetData()[i*this->GetWidth() - (j+1)] = vert;
//			this->GetData()[i*this->GetWidth() - (j+2)] = bleu;
//		}
//	}
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

void MyImage::Posterize(){
	for(int i=0;i<(this->GetHeight()*this->GetWidth()*3);i++){
		if(this->GetData()[i]>127){
			std::cout << "255 : " << std::to_string(this->GetData()[i]) << " = ";
			this->GetData()[i] = 255;
			std::cout << std::to_string(this->GetData()[i]) << std::endl;
		} else{
			std::cout << "0 : " << std::to_string(this->GetData()[i])<<" = ";
			this->GetData()[i] = 0;
			std::cout << std::to_string(this->GetData()[i]) << std::endl;
		}
	}
}

int MyImage::ComptageCouleurs(){
	std::vector<std::vector<int>> couleurs;
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i+=3){
		std::vector<int> couleur;
		couleur.push_back(this->GetData()[i]);
		couleur.push_back(this->GetData()[i+1]);
		couleur.push_back(this->GetData()[i+2]);
		if (std::find(couleurs.begin(), couleurs.end(), couleur) != couleurs.end()){
			
		} else {
			couleurs.push_back(couleur);
			std::cout<< "+1" << std::endl;
		}
		
	}
	std::cout << "fini"<< std::endl;
	return couleurs.size();
}


void MyImage::EnhenceContrast(int minValue, int maxValue){
	std::cout << "Imin: " << minValue << std::endl;
	std::cout << "Imax: " << maxValue << std::endl;
	int d = (255*minValue) /(maxValue-minValue);
	int f = 255 /(maxValue-minValue);
	for(int i=0; i< (this->GetHeight()*this->GetWidth()*3);i++){
		this->GetData()[i] = f * this->GetData()[i] + d;
	}
	
}

