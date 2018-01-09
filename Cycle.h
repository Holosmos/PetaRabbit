#ifndef __Simulation__Cycle__
#define __Simulation__Cycle__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Algebre.h"
#include <complex>

class Cycle {
	std::function<Homogene(Homogene)> fonctionIteree;
    std::vector<Homogene>* cyclesAttractifs;

	const double c_eps = 0.00005;
    const unsigned int c_borne = 100;
    const double parametreDistance = 0.005;
    const Homogene pointDefaut = Homogene(complex<double>(-1,-2),complex<double>(-3,-4));
    const Homogene pointInfini = Homogene(complex<double>(1.0),complex<double>(0.0));

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
