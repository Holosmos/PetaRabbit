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
	Polynome(const std::vector<complex<double>> &coefficientsDuPolynome);
	Polynome(const complex<double> &constante);

	void print();
	complex<double> coefficientDIndice(unsigned int i);


	Polynome additionAvec(Polynome polynome);
	Polynome multiplicationAvec(const complex<double> &scalaire);
	Polynome multiplicationAvec(Polynome polynome);

	complex<double> evaluationAuPoint(const complex<double> &point);

	Polynome polynomeDerive();
	Polynome polynomeDeriveNeme(const unsigned int &n);

};

Polynome operator+(Polynome A, const Polynome &B);
Polynome operator+(const Polynome &A, const complex<double> &B);
Polynome operator+(const Polynome &A, const double &B);

Polynome operator*(Polynome A, const Polynome &B);
Polynome operator*(Polynome A, const complex<double> &B);
Polynome operator*(Polynome A, const double &B);

Polynome operator/(const Polynome &A, const complex<double> &B);
Polynome operator/(const Polynome &A, const double &B);

Polynome operator-(const Polynome &A);
Polynome operator-(const Polynome &A, const Polynome &B);
Polynome operator-(const Polynome &A, const complex<double> &B);
Polynome operator-(const Polynome &A, const double &B);


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
	Homogene(const complex<double> &a, const complex<double> &b);
	Homogene(const complex<double> &a);
	Homogene(const double &a, const double &b);
	Homogene(const double &a);

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
	FractionRationnelle(const Polynome &numerateur);
	FractionRationnelle(const Polynome &numerateur, const Polynome &denominateur);
};

Homogene evaluationAuPoint(Polynome numerateur, Polynome denominateur, Homogene point);

#endif /* Algebre_h */
