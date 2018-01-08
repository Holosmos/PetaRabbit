//
//  Dynamicien.hpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#ifndef Dynamicien_h
#define Dynamicien_h

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <cmath>
#include <complex>

#include "Algebre.h"
#include "Cycle.h"

#include "lodepng.h"

struct Dynamicien {
	int borneDIteration;

	std::function<complex<double>(Homogene)> dynamique;
    std::vector<complex<double>> creeLaMatrice(int longueur, int hauteur, double echelle, complex<double> origine);


    // À vocation à disparaitre
	sf::VertexArray creeLaMatriceWin(int longueur, int hauteur, double echelle, complex<double> origine);
    const char* filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
    bool peindreEnBlanc = true;
};

std::vector<double> coloration(complex<double> couleur, bool peindreEnBlanc);

#endif /* Dynamicien_h */
