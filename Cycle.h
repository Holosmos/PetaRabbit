#ifndef __Simulation__Cycle__
#define __Simulation__Cycle__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Algebre.h"

class Cycle {
	double c_eps = 0.00005;
	
	bool donneUnCycle(Homogene z0);

	Homogene c_point = Homogene(0.0);

public:
	
	int c_borne = 100;
	
	std::function<Homogene(Homogene)> fonctionIteree;
	
	Cycle(std::function<Homogene (Homogene)> fonctionAIterer):fonctionIteree(fonctionAIterer){};
	
	void eps(double eps){c_eps = eps;}
	double eps(){return c_eps;}
	
	void borne(int borne){c_borne = borne;}
	int borne(){return c_borne;}
	
	Homogene chercheUnCycleAuPoint(Homogene z0, Homogene pointParDefaut);
	
};

#endif /* defined(__Simulation__Cycle__) */
