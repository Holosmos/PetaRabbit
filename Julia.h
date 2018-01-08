// Pour utiliser Julia : utiliser ce code dans main.cpp
/*/ Lancement de Julia et Dynamicien
Cycle moteurDesCycles(methode);
Dynamicien dynamicien;

std::vector<Homogene>* cycles = moteurDesCycles.getCyclesAttractifs();

dynamicien.peindreEnBlanc = makeW;
dynamicien.borneDIteration = borne;

function<Complexe(Homogene)> dyn = [methode, borne, cycles](Homogene point){
	Julia julia(methode, borne, cycles);
	return julia.convergenceDe(point);
};
//*/


#ifndef __Simulation__Julia__
#define __Simulation__Julia__

#include <cstdlib>
#include <iostream>
#include <vector>

#include <thread>
#include <cmath>
#include <complex>

#include "Algebre.h"
#include "Cycle.h"

struct Julia {
	
	std::function<Homogene (Homogene)> fonctionIteree;
	std::vector<Homogene> *cyclesAttractifs;
	
	Homogene pointDefaut = Homogene(complex<double>(-1,-2),complex<double>(-3,-4));
	
	Julia(std::function<Homogene (Homogene)> fonction, unsigned int borne, std::vector<Homogene> *cyclesAttractifs);
	
	unsigned int borneDIteration;
	
	complex<double> convergenceDe(Homogene z, double parametreConvergence = 0.0005);
};



#endif /* defined(__Simulation__Julia__) */
