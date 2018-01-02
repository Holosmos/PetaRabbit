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

#include <thread>
#include <cmath>

#include "Algebre.h"
#include "Cycle.h"

#include "lodepng.h"

struct Dynamicien {
	const char* filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
	
	bool peindreEnBlanc = false;
	int borneDIteration;
	
	std::function<Complexe(Homogene)> dynamique;
	
	
	sf::VertexArray creeLaMatrice(int longueur, int hauteur, double echelle, Complexe origine = Complexe(0,0));
};


#endif /* Dynamicien_h */
