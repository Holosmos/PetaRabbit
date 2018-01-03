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
	function<Complexe(Complexe)> fonction = [c](Complexe z){
		return z*z + c;};
	
	Complexe point = c;
    /*/if (c.moduleAuCarre() < 0.0625) {
        return Complexe(0, 0.0);
    }//*/
    if ((c + 0.25).moduleAuCarre() < 0.24) {
        return Complexe(borneDIteration,0.0);
    }
    if ((c + 1.).moduleAuCarre() < 0.05){
        return Complexe(borneDIteration,0.0);
    }
	//itérations
	for (unsigned int j = 0; j < borneDIteration; j++) {
		if (point.moduleAuCarre() >= 4.1){
			return Complexe(j, 0.0);
		}
		point = fonction(point);
	}
	return Complexe(borneDIteration, 0.0);
}



