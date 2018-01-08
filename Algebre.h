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

// --------------------------------
// --------------------------------
// ---------------- POLYNOME
// --------------------------------
// --------------------------------

struct Polynome {
	std::vector<complex<double>> coefficientsDuPolynome;
	unsigned int degreDuPolynome;


	Polynome();
	Polynome(std::vector<complex<double>> coefficientsDuPolynome);
	Polynome(complex<double> constante);

	void print();
	complex<double> coefficientDIndice(unsigned int i);


	Polynome additionAvec(Polynome polynome);
	Polynome multiplicationAvec(complex<double> scalaire);
	Polynome multiplicationAvec(Polynome polynome);

	complex<double> evaluationAuPoint(complex<double> point);

	Polynome polynomeDerive();
	Polynome polynomeDeriveNeme(unsigned int n);

};

Polynome operator+(Polynome A, Polynome B);
Polynome operator+(Polynome A, complex<double> B);
Polynome operator+(Polynome A, double B);

Polynome operator*(Polynome A, Polynome B);
Polynome operator*(Polynome A, complex<double> B);
Polynome operator*(Polynome A, double B);

Polynome operator/(Polynome A, complex<double> B);
Polynome operator/(Polynome A, double B);

Polynome operator-(Polynome A);
Polynome operator-(Polynome A, Polynome B);
Polynome operator-(Polynome A, complex<double> B);
Polynome operator-(Polynome A, double B);


// --------------------------------
// --------------------------------
// ---------------- HOMOGENE
// --------------------------------
// --------------------------------

struct Homogene {
	complex<double> x;
	complex<double> y;

	void print();


	Homogene();
	Homogene(complex<double> a, complex<double> b);
	Homogene(complex<double> a);
	Homogene(double a, double b);
	Homogene(double a);

	complex<double> carteY();
	complex<double> carteX();

	double distanceAvec(Homogene b);
};


// --------------------------------
// --------------------------------
// ---------------- FRACTION RATIONNELLE
// --------------------------------
// --------------------------------

struct FractionRationnelle {
	Polynome numerateur;
	Polynome denominateur;

	std::function<Homogene(Homogene)> fonctionRationnelle;

	FractionRationnelle();
	FractionRationnelle(Polynome numerateur);
	FractionRationnelle(Polynome numerateur, Polynome denominateur);
};

Homogene evaluationAuPoint(Polynome numerateur, Polynome denominateur, Homogene point);

#endif /* Algebre_h */
