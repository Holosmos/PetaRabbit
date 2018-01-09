//
//  Parametres.hpp
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

const bool peindreEnBlanc = false;
const bool symetrieVerticale = false;

const bool estJulia = true;
const bool estMandelbrot = !estJulia;

FractionRationnelle exempleJulia(unsigned int j);
const FractionRationnelle fracJulia = exempleJulia(0);

const double finesseConvergence = 0.0005;

const Homogene pointDefaut = Homogene(complex<double>(-1,-2),complex<double>(-3,-4));
const Homogene pointInfini = Homogene(complex<double>(1.0),complex<double>(0.0));

// Propre à Cycles.h/cpp

const double c_eps = 0.00005;
const unsigned int c_borne = 100;
const double parametreDistance = 0.005;



#endif /* Parametres_h */
