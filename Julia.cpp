#include "Julia.h"

using namespace std;

// Test de convergence des itérées

complex<double> Julia::convergenceDe(Homogene z, double parametreConvergence){

	// Etude de la convergence d'un point donné

	Homogene copie = z; // Utile pour la seconde partie de la fonction

	for (unsigned int j = 0; j <= borneDIteration; j++){
		for (unsigned int k = 0; k < cyclesAttractifs->size(); k++) {
			Homogene cycle = (*cyclesAttractifs)[k];
			if (cycle.distanceAvec(z) < parametreConvergence) {
				return complex<double>(j,k+1); // correspond au message : j itérées, proche du cycle k
			}
		}
		z = fonctionIteree(z);
	}

	// Recherche d'un cycle en cas de non convergence
	// À activer selon les cas, peut allonger la durer d'execution.
	//

	Cycle moteurDesCycles(fonctionIteree);
	Homogene cycle = moteurDesCycles.chercheUnCycleAuPoint(z, pointDefaut);

	if ((cycle.x != pointDefaut.x || cycle.y != pointDefaut.y)) {
		cyclesAttractifs->push_back(cycle);
		cout << "+1 spé";
		cycle.print();
		for (int j = 0; j<= borneDIteration ; j++) {
			if ( copie.distanceAvec(cycle) < parametreConvergence) {
				return complex<double>(j, cyclesAttractifs->size());
			}
			copie = fonctionIteree(copie);
		}
	}

	//*/

	return complex<double>(borneDIteration); // renvoie le message qu'il n'y a pas eu de convergence
}
