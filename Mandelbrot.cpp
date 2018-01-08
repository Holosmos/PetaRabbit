//
//  Mandelbrot.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Mandelbrot.h"

using namespace std;

complex<double> Mandelbrot::convergencePourParametre(complex<double> c){
	function<complex<double>(complex<double>)> fonction = [c](complex<double> z){
		return z*z + c;};
	
	complex<double> point = c;
    if (norm(c + 0.25) < 0.24) {
        return complex<double>(borneDIteration,0.0);
    }
    if (norm(c + 1.) < 0.05){
        return complex<double>(borneDIteration,0.0);
    }
	//itérations
	for (unsigned int j = 0; j < borneDIteration; j++) {
		if (norm(point) >= 4.1){
			return complex<double>(j, 0.0);
		}
		point = fonction(point);
	}
	return complex<double>(borneDIteration, 0.0);
}
