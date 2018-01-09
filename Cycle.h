#ifndef __Simulation__Cycle__
#define __Simulation__Cycle__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Algebre.h"
#include <complex>

#include "Parametres.h"

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
