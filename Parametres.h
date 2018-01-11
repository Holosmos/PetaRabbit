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

// Choix type simulation

const bool fabricationImage = true;
const bool fenetreSimulation = false;

// Paramètres globaux

const string cheminFichierPhoto = "/Users/Raphael/Desktop/PhotoJulia.png";

const double finesseConvergence = 0.001;
const unsigned int borneInitiale = 200;

const double facteurResolutionInitiale = 1;
const double echelleInitiale = 0.0025;

const complex<double> origineInitale(0,0);

const bool peindreEnBlanc = true;
const bool symetrieVerticale = false;

const bool estJulia = true;
const bool estMandelbrot = !estJulia;

function<Homogene(Homogene)> exempleJulia(unsigned int j);
const function<Homogene(Homogene)> fonctionJulia = exempleJulia(0);

const Homogene pointDefaut = Homogene(complex<double>(-1,-2),complex<double>(-3,-4));
const Homogene pointInfini = Homogene(complex<double>(1.0),complex<double>(0.0));

// Propre à Cycles
const bool affichageDesCycles = false;

const unsigned int nombreDeCyclesVoulus = 2;
const unsigned int nombreDeTirages = 500;
const unsigned int nombreIterationsTests = 300;

const bool rechercheProfondeDansJulia = false;

const double c_eps = 0.00005;
const unsigned int c_borne = 100;
const double parametreDistance = 0.005;



#endif /* Parametres_h */
