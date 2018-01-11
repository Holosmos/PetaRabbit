//
//  Algebre.h
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 31/12/2017.
//  Copyright © 2017 Raphaël Alexandre. All rights reserved.
//

#ifndef Algebre_h
#define Algebre_h

#include <functional>
#include <stdio.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

struct Homogene {
	complex<double> x;
	complex<double> y;

	void print();

	Homogene(): x(0.), y(1.) {};
    Homogene(const complex<double> &a, const complex<double> &b) : x(a), y(b) {};
    Homogene(const complex<double> &a) : x(a), y(1.) {};
    Homogene(const double &a, const double &b) : x(a), y(b) {};
    Homogene(const double &a) : x(a), y(1.) {};

	complex<double> carteY();
	complex<double> carteX();

	double distanceAvec(Homogene b);
};

#endif /* Algebre_h */
