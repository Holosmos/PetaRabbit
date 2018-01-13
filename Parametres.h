//
//  Parametres.h
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 09/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#ifndef Parametres_h
#define Parametres_h

#include <stdio.h>
#include <complex>
#include "Algebre.h"

using namespace std;

// Paramètres globaux

const string cheminFichierPhoto = "./PhotoJulia.png";

// Paramètres fenêtre

const double facteur = 1; // rupture à 1 047 809 880 pixels ~= 22^2 * 1920 * 1080
const double echelleInitiale = 0.01 / facteur;

const complex<double> origineInitale(0,0);

const bool peindreEnBlanc = true;

// Paramètres analytiques

const double finesseConvergence = 0.001;
const unsigned int borneDIteration = 200;

// Paramètres dynamiques

const bool symetrieVerticale = false;

const bool estJulia = true;
const bool estMandelbrot = !estJulia;

function<Homogene(Homogene)> exempleJulia(unsigned int j);
const function<Homogene(Homogene)> fonctionJulia = exempleJulia(0);
const unsigned int nombreDeCyclesVoulus = 2;


// Constantes - À ignorer

const Homogene pointDefaut = Homogene(complex<double>(-1,-2),complex<double>(-3,-4));
const Homogene pointInfini = Homogene(complex<double>(1.0),complex<double>(0.0));



#endif /* Parametres_h */
