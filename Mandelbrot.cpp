//
//  Mandelbrot.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Mandelbrot.h"

using namespace std;

Complexe Mandelbrot::convergencePourParametre(Complexe c){

	vector<Complexe> coefficients(3,Complexe(0.0));
	coefficients[2] = Complexe(1.0);
	coefficients[0] = c;
	Polynome polynome = Polynome(coefficients);
	
	Complexe origineIteree(0.0);
	for (unsigned int j = 0; j < borneDIteration; j++) {
		origineIteree = polynome.evaluationAuPoint(origineIteree);
		if (origineIteree.moduleAuCarre() >= 4.1){
			return Complexe(j, 0.0);
		}
	}
	return Complexe(borneDIteration, 0.0);
}
