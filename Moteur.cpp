//
//  Moteur.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 08/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Moteur.h"

void remplitImage(std::vector<unsigned char> *image, const std::vector<std::complex<double>> &matrice, const unsigned int &y, const unsigned int &longueur, const bool &peindreEnBlanc){
    for (unsigned int x = 0; x < longueur; x++) {
        std::vector<double> couleur = coloration(matrice[y*longueur+x], peindreEnBlanc);
        for (int k = 0; k < 3; k++)
            (*image)[4 * (y * longueur + x) + k] = couleur[k];
        (*image)[4 * (y * longueur + x) + 3] = 255;
    }
}


std::vector<double> coloration(complex<double> couleur, bool peindreEnBlanc){
    std::vector<double> couleurObtenue(3,couleur.real());
    if (!peindreEnBlanc){
        switch (int(couleur.imag())%7) { // 7 couleurs prévues
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

vector<unsigned char> faireImage(unsigned int &hauteur, const unsigned int &longueur, complex<double> &origine, const double &echelle, const bool &peindreEnBlanc, const bool &symetrieVerticale, Dynamicien &dynamicien){
    vector<unsigned char> image;
    unsigned int hauteurBis = hauteur;
    
    if (symetrieVerticale){
        hauteur = (hauteur/2)*2; // pour s'assurer d'un nombre pair
        origine.imag(0.);
        origine = origine + complex<double>(0,hauteur) * (echelle/4.0);
        hauteurBis = hauteur/2;
    }
    
    image.resize(longueur * hauteur * 4);
    vector<complex<double>> matrice = dynamicien.creeLaMatrice(longueur, hauteurBis, echelle, origine);
    
    for (unsigned int y = 0; y < hauteurBis; y++)
        remplitImage(&image, matrice, y, longueur, peindreEnBlanc);
    
    if (symetrieVerticale){
        for (unsigned int y = 0; y < hauteurBis; y++)
            for (unsigned int x = 0; x < longueur; x++) {
                vector<double> couleur = coloration(matrice[y*longueur+x], peindreEnBlanc);
                for (unsigned int k = 0; k < 3; k++)
                    image[4 * ((hauteur-1 - y) * longueur + x) + k] = couleur[k];
                image[4 * ((hauteur-1 - y) * longueur + x) + 3] = 255;
            }
    }
    return image;
}
