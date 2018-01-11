//
//  Algebre.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 31/12/2017.
//  Copyright © 2017 Raphaël Alexandre. All rights reserved.
//

#include "Algebre.h"

void Homogene::print(){

	if (y != 0.0) {
		x = x/y;
		y = complex<double>(1.0);
	}
	else{
		x = complex<double>(1.0);
	}
	double a1 = x.real();
	double a2 = x.imag();

	double b1 = y.real();
	double b2 = y.imag();

	std::cout << "["<<a1<< " + "<<a2<<" * i  :  "<<b1<<" + "<<b2<<" * i]"<<std::endl;
}

complex<double> Homogene::carteY(){return x/y;}
complex<double> Homogene::carteX(){return y/x;}

double Homogene::distanceAvec(Homogene b){
	if (y != complex<double>(0) && b.y != complex<double>(0)) {
		return sqrt(norm((x * b.y - y * b.x)))/sqrt(norm((y * b.y)));
	}
	else{
		if (y == 0.0 && b.y == 0.0){
			return 0.0;
		}
		else if (b.y == 0.0){
			return sqrt(norm(y))/sqrt(norm(x)) ;
		}
		else{
			return sqrt(norm(b.y))/sqrt(norm(b.x)) ;
		}
	}
}

