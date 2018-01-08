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

Dynamicien::Dynamicien(const unsigned int &borne, const bool &peindreBlanc) : borneDIteration(borne), peindreEnBlanc(peindreBlanc), dynamique(0){}

void calculeLigneW(int y,
				  int longueur, int hauteur,
				  double echelle, complex<double> origine,
				  int borneDIteration, bool peindreEnBlanc,
				  function<complex<double>(Homogene)>* convergenceDe,
				  VertexArray *ligne){


	for (int j = 0; j<= longueur ; j++){

		// Calculs des coordonnées du pixel choisi

		complex<double> z0 = complex<double>(j,hauteur-y) * echelle;
		z0 = z0 + origine;

		// Calculs sur la convergence du point

		Homogene z(z0,complex<double>(1,0));
		complex<double> resultatConvergence = (*convergenceDe)(z);
		int nombreIteree = resultatConvergence.real();

		// Coloration en fonction du nombre d'itérées

		int couleur = 255 - ((nombreIteree>=35) ?
							 (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
							 : nombreIteree * 4);  // formule maison pour une harmonie

		if (peindreEnBlanc) {
			(*ligne)[j] = Vertex(Vector2f(j,y), Color(couleur,couleur,couleur));
		}
		else{
			switch (int(resultatConvergence.imag())%7) { // 7 couleurs prévues
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

VertexArray Dynamicien::creeLaMatriceWin(int longueur, int hauteur, double echelle, complex<double> origine){

	// Pré-calculs pour les coordonnées des points étudiés

	complex<double> origineFenetre = complex<double>(longueur,hauteur) * (echelle/2.0);
	origine = origine - origineFenetre;

	VertexArray matrice(Points,(longueur+1)*(hauteur+1));

    #pragma omp parallel for
	for (int y = 0; y <= hauteur; y++){ // on parcourt les lignes puis les colonnes

		VertexArray ligne(Points,longueur+1);

		calculeLigneW(y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, dynamique, &ligne);

		unsigned int k = y * (longueur+1);
		for (unsigned int j = 0; j <= longueur; j++) {
            matrice[k+j] = ligne[j];
		}
	}
	return matrice;
}


void calculeLigne(int y,
                  int longueur, int hauteur,
                  double echelle, complex<double> origine,
                  int borneDIteration,
                  function<complex<double>(Homogene)>* convergenceDe,
                  std::vector<complex<double>> *ligne){


    for (int j = 0; j< longueur ; j++){

        // Calculs des coordonnées du pixel choisi

        complex<double> z0 = complex<double>(j,hauteur-y) * echelle;
        z0 = z0 + origine;

        // Calculs sur la convergence du point

        Homogene z(z0,complex<double>(1,0));
        complex<double> resultatConvergence = (*convergenceDe)(z);
        int nombreIteree = resultatConvergence.real();

        // Coloration en fonction du nombre d'itérées

        int couleur = 255 - ((nombreIteree>=35) ?
                             (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
                             : nombreIteree * 4);  // formule maison pour une harmonie

        (*ligne)[j] = complex<double>(couleur,resultatConvergence.imag());
    }

}

std::vector<complex<double>> Dynamicien::creeLaMatrice(int longueur, int hauteur, double echelle, complex<double> origine){
    // Pré-calculs pour les coordonnées des points étudiés

    complex<double> origineFenetre = complex<double>(longueur,hauteur) * (echelle/2.0);
    origine = origine - origineFenetre;

    std::vector<complex<double>> image(hauteur*longueur,0.);

    #pragma omp parallel for
    for (int y = 0; y < hauteur; y++){ // on parcourt les lignes puis les colonnes

        std::vector<complex<double>> ligne(longueur, 0.);

        calculeLigne(y, longueur, hauteur, echelle, origine, borneDIteration, dynamique, &ligne);

        for (unsigned int j = 0; j < longueur; j++) {
            image[y*longueur + j] = ligne[j];
        }
    }
    return image;
}
