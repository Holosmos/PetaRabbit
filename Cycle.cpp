#include "Cycle.h"

using namespace std;

bool Cycle::donneUnCycle(Homogene z0){
	
	// Calcul d'une partie l'orbite positive
	
	vector<Homogene> orbite(0);
	Homogene zEps(z0.x + c_eps, z0.y + c_eps/2);
	orbite.push_back(z0);
	
	// On répertorie les images successives en les comparant aux précédentes
	
	for (int i = 1; i<= c_borne; i++) {
		z0 = fonctionIteree(z0);
		orbite.push_back(z0);
		for (int j=0; j<i; j++) {
			if (z0.distanceAvec(orbite[j]) <c_eps){
				
				// Si deux images sont eps-proches alors on vérifie que le cycle périodique potentiellement trouvé est suffisamment attractif
				
				c_point = z0;
				for (int k = 1; k<= i; k++) {
					zEps = fonctionIteree(zEps);
				}
				return z0.distanceAvec(zEps) < c_eps/10;
			}
		}
	}
	return false;
}

Homogene Cycle::chercheUnCycleAuPoint(Homogene z0, Homogene pointParDefaut){
	if (donneUnCycle(z0)) {
		return c_point;
	}
	return pointParDefaut;
}
