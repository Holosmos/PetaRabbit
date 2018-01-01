#ifndef __Simulation__Julia__
#define __Simulation__Julia__

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <functional>

#include <thread>
#include <cmath>

#include "Algebre.h"
#include "Cycle.h"

class Julia {

	Cycle moteurDesCycles;
	std::vector<Homogene> cyclesAttractifs;

	std::function<Homogene (Homogene)> fonctionIteree;

	Homogene pointDefaut = Homogene(Complexe(-1,-2),Complexe(-3,-4));
	Homogene pointInfini = Homogene(Complexe(1.0),Complexe(0.0));

	Complexe uniteImaginaire = Complexe(0,1);

	bool nEstPasDejaUnCycle(Homogene point, double parametreDistance = 0.005);

	Complexe convergenceDe(Homogene z, double parametreConvergence = 0.01);

public:

	int borneDIteration;

	Julia(std::function<Homogene (Homogene)> fonction);

	bool peindreEnBlanc = false;

        void creeLaMatrice(sf::VertexArray &tab, int longueur, int hauteur, double echelle, Complexe origine = Complexe(0,0));

	void chercheANouveau(Complexe origine, double echelle, int longueur, int hauteur);

};

#endif /* defined(__Simulation__Julia__) */
