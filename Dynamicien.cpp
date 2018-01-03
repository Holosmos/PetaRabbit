//
//  Dynamicien.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Dynamicien.h"
using namespace sf;
using namespace std;

void calculeLigneW(int y,
				  int longueur, int hauteur,
				  double echelle, Complexe origine,
				  int borneDIteration, bool peindreEnBlanc,
				  function<Complexe(Homogene)> convergenceDe,
				  VertexArray *ligne){
	
	
	for (int j = 0; j<= longueur ; j++){
		
		// Calculs des coordonnées du pixel choisi
		
		Complexe z0 = Complexe(j,hauteur-y) * echelle;
		z0 = z0 + origine;
		
		// Calculs sur la convergence du point
		
		Homogene z(z0,Complexe(1,0));
		Complexe resultatConvergence = convergenceDe(z);
		int nombreIteree = resultatConvergence.partieReelle();
		
		// Coloration en fonction du nombre d'itérées
		
		int couleur = 255 - ((nombreIteree>=35) ?
							 (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
							 : nombreIteree * 4);  // formule maison pour une harmonie
		
		if (peindreEnBlanc) {
			(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,couleur,couleur));
		}
		else{
			switch (int(resultatConvergence.partieImaginaire())%7) { // 7 couleurs prévues
				case 0:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,couleur,couleur));
					break;
				case 1:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,0,0));
					break;
				case 2:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(0,couleur,0));
					break;
				case 3:
					(*ligne)[j] = Vertex(Vector2f(j,y),Color(0,0,couleur));
					break;
				case 4:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,couleur,0));
					break;
				case 5:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(0,couleur,couleur));
					break;
				case 6:
					(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,0,couleur));
					break;
			}
			
		}
	}
	
}

VertexArray Dynamicien::creeLaMatriceWin(int longueur, int hauteur, double echelle, Complexe origine){
	
	// Pré-calculs pour les coordonnées des points étudiés
	
	Complexe origineFenetre = Complexe(longueur,hauteur) * (echelle/2.0);
	origine = origine - origineFenetre;
	
	VertexArray matrice(Points,(longueur+1)*(hauteur+1));
	
	//generate some image
	unsigned lon = longueur+1;
	unsigned hau = hauteur+1;
	
	std::vector<unsigned char> image;
	image.resize(lon * hau * 4);
	
	
	int y;
	for (y = 0; y <= hauteur -1 ; y += 2){ // on parcourt les lignes puis les colonnes
		
		VertexArray ligne1(Points,longueur+1);
		VertexArray ligne2(Points,longueur+1);
		
		// Deux threads pour profiter pleinement d'un processeur dual-core
		thread a(calculeLigneW, y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, dynamique, &ligne1);
		thread b(calculeLigneW, y + 1, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, dynamique, &ligne2);
		a.join();
		b.join();
		
		unsigned int k = y * (longueur+1);
		for (unsigned int j = 0; j <= longueur; j++) {
			matrice[k+j] = ligne1[j];
			matrice[k+(longueur+1)+j] = ligne2[j];
			image[4 * y * lon + 4 * j + 0] = ligne1[j].color.r;
			image[4 * y * lon + 4 * j + 1] = ligne1[j].color.g;
			image[4 * y * lon + 4 * j + 2] = ligne1[j].color.b;
			image[4 * y * lon + 4 * j + 3] = ligne1[j].color.a;
			image[4 * (y+1) * lon + 4 * j + 0] = ligne2[j].color.r;
			image[4 * (y+1) * lon + 4 * j + 1] = ligne2[j].color.g;
			image[4 * (y+1) * lon + 4 * j + 2] = ligne2[j].color.b;
			image[4 * (y+1) * lon + 4 * j + 3] = ligne2[j].color.a;
		}
	}
	while (y <= hauteur) { // on fait les dernières lignes
		
		VertexArray ligne(Points,longueur+1);
		thread a(calculeLigneW, y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, dynamique, &ligne);
		a.join();
		
		unsigned int k = y*(longueur+1);
		for (unsigned int j = 0; j <= longueur; j++) {
            matrice[k+j] = ligne[j];
            image[4 * y * lon + 4 * j + 0] = ligne[j].color.r;
            image[4 * y * lon + 4 * j + 1] = ligne[j].color.g;
            image[4 * y * lon + 4 * j + 2] = ligne[j].color.b;
            image[4 * y * lon + 4 * j + 3] = ligne[j].color.a;
		}
		y++;
	}
	
	lodepng::encode(filename, image, (longueur +1), (hauteur +1));
	
	return matrice;
}


void calculeLigne(int y,
                  int longueur, int hauteur,
                  double echelle, Complexe origine,
                  int borneDIteration,
                  function<Complexe(Homogene)> convergenceDe,
                  std::vector<Complexe> *ligne){
    
    
    for (int j = 0; j< longueur ; j++){
        
        // Calculs des coordonnées du pixel choisi
        
        Complexe z0 = Complexe(j,hauteur-y) * echelle;
        z0 = z0 + origine;
        
        // Calculs sur la convergence du point
        
        Homogene z(z0,Complexe(1,0));
        Complexe resultatConvergence = convergenceDe(z);
        int nombreIteree = resultatConvergence.partieReelle();
        
        // Coloration en fonction du nombre d'itérées
        
        int couleur = 255 - ((nombreIteree>=35) ?
                             (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
                             : nombreIteree * 4);  // formule maison pour une harmonie
        
        (*ligne)[j] = Complexe(couleur,resultatConvergence.partieImaginaire());
    }
    
}

std::vector<Complexe> Dynamicien::creeLaMatrice(int longueur, int hauteur, double echelle, Complexe origine){
    // Pré-calculs pour les coordonnées des points étudiés
    
    Complexe origineFenetre = Complexe(longueur,hauteur) * (echelle/2.0);
    origine = origine - origineFenetre;
    
    
    std::vector<Complexe> image(hauteur*longueur,0.);
    
    int y;
    for (y = 0; y < hauteur -1 ; y +=2){ // on parcourt les lignes puis les colonnes
        
        std::vector<Complexe> ligne1(longueur, 0.);
        std::vector<Complexe> ligne2(longueur, 0.);
        
        // Deux threads pour profiter pleinement d'un processeur dual-core
        thread a(calculeLigne, y, longueur, hauteur, echelle, origine, borneDIteration, dynamique, &ligne1);
        thread b(calculeLigne, y + 1, longueur, hauteur, echelle, origine, borneDIteration, dynamique, &ligne2);
        a.join();
        b.join();
        
        for (unsigned int j = 0; j < longueur; j++) {
            image[y*longueur + j] = ligne1[j];
            image[(y+1)*longueur + j] = ligne2[j];
        }
    }
    while (y < hauteur) { // on fait les dernières lignes
        
        std::vector<Complexe> ligne(longueur, 0.);
        thread a(calculeLigne, y, longueur, hauteur, echelle, origine, borneDIteration, dynamique, &ligne);
        a.join();
        
        for (unsigned int j = 0; j <= longueur; j++) {
            image[y*longueur + j] = ligne[j];
        }
        y++;
    }
    
    return image;
}


std::vector<double> coloration(Complexe couleur, bool peindreEnBlanc){
    std::vector<double> couleurObtenue(3,couleur.partieReelle());
    if (!peindreEnBlanc){
        switch (int(couleur.partieImaginaire())%7) { // 7 couleurs prévues
            case 1:
                couleurObtenue[1] = 0.;
                couleurObtenue[2] = 0.;
                break;
            case 2:
                couleurObtenue[0] = 0.;
                couleurObtenue[2] = 0.;
                break;
            case 3:
                couleurObtenue[0] = 0.;
                couleurObtenue[1] = 0.;
                break;
            case 4:
                couleurObtenue[2] = 0.;
                break;
            case 5:
                couleurObtenue[0] = 0.;
                break;
            case 6:
                couleurObtenue[1] = 0.;
                break;
        }
        
    }
    return couleurObtenue;
}
