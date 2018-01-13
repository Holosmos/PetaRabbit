#ifndef __Simulation__Julia__
#define __Simulation__Julia__

#include <cstdlib>
#include <iostream>
#include <vector>

#include <thread>
#include <cmath>
#include <complex>

#include "Parametres.h"

#include "Algebre.h"
#include "Cycle.h"

struct Julia {
    Julia(const std::function<Homogene (Homogene)> &fonction,  std::vector<Homogene> *cycles): fonctionIteree(fonction), cyclesAttractifs(cycles) {};

	std::function<Homogene (Homogene)> fonctionIteree;
    std::vector<Homogene> *cyclesAttractifs;

	complex<double> convergenceDe(Homogene z);
};



#endif /* defined(__Simulation__Julia__) */
