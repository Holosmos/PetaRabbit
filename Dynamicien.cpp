//
//  Dynamicien.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Dynamicien.h"
using namespace std;

Dynamicien::Dynamicien(const bool &peindreBlanc) : peindreEnBlanc(peindreBlanc), dynamique(0){}

void calculeLigne(const unsigned int &y,
                  const unsigned int &longueur, const unsigned int &hauteur,
                  const double &echelle, const complex<double> &origine,
                  const function<complex<double>(Homogene)> &convergenceDe,
                  std::vector<complex<double>> *ligne){


    for (unsigned int j = 0; j< longueur ; j++){

        // Calculs des coordonnées du pixel choisi

        complex<double> z0 = complex<double>(j,hauteur-y) * echelle;
        z0 = z0 + origine;

        // Calculs sur la convergence du point

        Homogene z(z0,complex<double>(1,0));
        complex<double> resultatConvergence = convergenceDe(z);
        unsigned int nombreIteree = resultatConvergence.real();

        // Coloration en fonction du nombre d'itérées

        unsigned int couleur = 255 - ((nombreIteree>=35) ?
                             (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
                             : nombreIteree * 4);  // formule maison pour une harmonie

        (*ligne)[j] = complex<double>(couleur,resultatConvergence.imag());
    }

}

std::vector<complex<double>> Dynamicien::creeLaMatrice(int longueur, int hauteur, const double &echelle, complex<double> origine){
    // Pré-calculs pour les coordonnées des points étudiés

    complex<double> origineFenetre = complex<double>(longueur,hauteur) * (echelle/2.0);
    origine = origine - origineFenetre;

    std::vector<complex<double>> image(hauteur*longueur,0.);

    #pragma omp parallel for
    for (int y = 0; y < hauteur; y++){ // on parcourt les lignes puis les colonnes

        std::vector<complex<double>> ligne(longueur, 0.);

        calculeLigne(y, longueur, hauteur, echelle, origine, dynamique, &ligne);

        for (unsigned int j = 0; j < longueur; j++) {
            image[y*longueur + j] = ligne[j];
        }
    }
    return image;
}
