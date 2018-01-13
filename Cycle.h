#ifndef __Simulation__Cycle__
#define __Simulation__Cycle__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Algebre.h"
#include <complex>

#include "Parametres.h"


/// === paramètres
const bool affichageDesCycles = false;

const unsigned int nombreDeTirages = 500;
const unsigned int nombreIterationsTests = 300;

const bool rechercheProfondeDansJulia = false;

const double c_eps = 0.00005;
const unsigned int c_borne = 100;
const double parametreDistance = 0.005;

/// ===

class Cycle {
	std::function<Homogene(Homogene)> fonctionIteree;
    std::vector<Homogene>* cyclesAttractifs;

	bool donneUnCycle(Homogene z0);
	Homogene c_point = Homogene(0.0);

	bool nEstPasDejaUnCycle(const Homogene &point);

public:
	
	Cycle(const std::function<Homogene (Homogene)> &fonctionAIterer, std::vector<Homogene> *cycles):fonctionIteree(fonctionAIterer), cyclesAttractifs(cycles){};

	void calculeLesCyclesAttractifs();

	Homogene chercheUnCycleAuPoint(Homogene z0);
	void chercheANouveau(const complex<double> &origine, const double &echelle);
};

#endif /* defined(__Simulation__Cycle__) */
