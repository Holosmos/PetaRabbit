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

#include "Algebre.h"
#include "Cycle.h"

struct Julia {
	
	std::function<Homogene (Homogene)> fonctionIteree;
	std::vector<Homogene> *cyclesAttractifs;
	
	Homogene pointDefaut = Homogene(Complexe(-1,-2),Complexe(-3,-4));
	
public:
	Julia(std::function<Homogene (Homogene)> fonction, unsigned int borne, std::vector<Homogene> *cyclesAttractifs);
	
	unsigned int borneDIteration;
	
	Complexe convergenceDe(Homogene z, double parametreConvergence = 0.01);
	
	//void chercheANouveau(Complexe origine, double echelle, int longueur, int hauteur);
};



#endif /* defined(__Simulation__Julia__) */
