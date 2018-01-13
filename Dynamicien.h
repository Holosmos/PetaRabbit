//
//  Dynamicien.hpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#ifndef Dynamicien_h
#define Dynamicien_h

#include <cstdlib>
#include <iostream>
#include <vector>

#include <cmath>
#include <complex>

#include "Algebre.h"
#include "Cycle.h"

#include "lodepng.h"

struct Dynamicien {
    
    Dynamicien(const bool &peindreEnBlanc);

    bool peindreEnBlanc;
	std::function<complex<double>(Homogene)> dynamique;
    std::vector<complex<double>> creeLaMatrice(int longueur, int hauteur, const double &echelle, complex<double> origine);
};

#endif /* Dynamicien_h */
