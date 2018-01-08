//
//  Moteur.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 08/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Moteur.h"

FractionRationnelle exemple(unsigned int j){
    vector<complex<double>> p1;
    vector<complex<double>> p2;
    complex<double> i(0.0,1.0);
    switch (j) {
        case 0:
            p1 = vector<complex<double>>(3,0.*i);    // LAPIN
            p1[2] = 1. + 0.*i;
            p1[0] = -0.123 + 0.745*i;
            p2 = vector<complex<double>>(1,1. + 0.*i);
            break;
        case 1:
            p1 = vector<complex<double>>(3,0.*i);  // COLLIER
            p1[2] = 1. + 0.*i;
            p1[0] = -1. + 0.*i;
            p2 = vector<complex<double>>(3,0.*i);
            p2[2] = 1. + 0.*i;
            break;
        case 2:
            p1 =  vector<complex<double>>(3,0.*i); // GALAXIE
            p1[2] = -0.138 + 0.*i;
            p1[1] = -0.303 + 0.*i;
            p1[0] = -0.138 + 0.*i;
            p2 = vector<complex<double>>(2,0.*i);
            p2[1] = 1. +0.*i;
            break;
        case 3:
            p1 = vector<complex<double>>(3,0.*i); // STRANGE
            p1[2] = 1. + 0.*i;
            p1[0] = -0.8 + 0.*i;
            p2 = vector<complex<double>>(1,1. +0.*i);
            break;
        case 4:
            p1 = vector<complex<double>>(4,0.*i);  // NEWTON
            p1[3] = 2. + 0.*i;
            p1[0] = -2. + 0.*i;
            p2 = vector<complex<double>>(3,0.*i);
            p2[2] = 3. + 0.*i;
            p2[0] = -2. + 0.*i;
            break;
        case 5:
            p1 = vector<complex<double>>(26,0.*i);   // PENTAGONE
            p1[25] = 87. + 0.*i;
            p1[20] = -3335. + 0.*i;
            p1[10] = -6670. + 0.*i;
            p1[5] = -435. + 0.*i;
            p1[0] = 1. + 0.*i;
            p2 = vector<complex<double>>(30,0.*i);
            p2[29] = -1. + 0.*i;
            p2[24] = -435. + 0.*i;
            p2[19] = 6670. + 0.*i;
            p2[9] = 3335. + 0.*i;
            p2[4]  = 87. + 0.*i;
            break;
        default:
            break;
    }
    
    Polynome nume(p1), deno(p2);
    return FractionRationnelle(nume,deno);
}


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
