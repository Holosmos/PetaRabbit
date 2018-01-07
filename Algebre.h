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

// --------------------------------
// --------------------------------
// ---------------- COMPLEXE
// --------------------------------
// --------------------------------

struct Complexe{

public:

	Complexe();
	Complexe(double partieReelle);
	Complexe(double partieReelle,double partieImaginaire);

	void print();

	double partieReelle();
	double partieImaginaire();
	void partieReelle(double partieReelle);
	void partieImaginaire(double partieImaginaire);

	double moduleAuCarre();
	double module();
	Complexe conjugue();

	Complexe additionAvec(Complexe nombreComplexe);
	Complexe oppose();
	Complexe multiplicationAvec(Complexe nombreComplexe);
	Complexe multiplicationAvec(double scalaire);
	Complexe inverse();

	Complexe racineCarree();

private:

	double partieRe;
	double partieIm;

};

Complexe operator+(Complexe a,Complexe b);
Complexe operator+(Complexe a, double b);
Complexe operator+(double a, Complexe b);

Complexe operator-(Complexe a);
Complexe operator-(Complexe a,Complexe b);
Complexe operator-(Complexe a, double b);
Complexe operator-(double a, Complexe b);

Complexe operator*(Complexe a,Complexe b);
Complexe operator*(Complexe a, double b);
Complexe operator*(double a, Complexe b);

Complexe operator/(Complexe a,Complexe b);
Complexe operator/(Complexe a, double b);
Complexe operator/(double a, Complexe b);

bool operator==(Complexe a, Complexe b);
bool operator==(Complexe a, double b);
bool operator!=(Complexe a, Complexe b);
bool operator!=(Complexe a, double b);


// --------------------------------
// --------------------------------
// ---------------- POLYNOME
// --------------------------------
// --------------------------------

struct Polynome {

	std::vector<Complexe> coefficientsDuPolynome;

	unsigned int degreDuPolynome;
	Complexe uniteImaginaire;


public:

	Polynome();
	Polynome(std::vector<Complexe> coefficientsDuPolynome);
	Polynome(Complexe constante);

	void print();

	unsigned int degre();
	Complexe coefficientDIndice(unsigned int i);


	Polynome additionAvec(Polynome polynome);
	Polynome multiplicationAvec(Complexe scalaire);
	Polynome multiplicationAvec(Polynome polynome);

	Complexe evaluationAuPoint(Complexe point);

	Polynome polynomeDerive();
	Polynome polynomeDeriveNeme(unsigned int n);

};

Polynome operator+(Polynome A, Polynome B);
Polynome operator+(Polynome A, Complexe B);
Polynome operator+(Polynome A, double B);

Polynome operator*(Polynome A, Polynome B);
Polynome operator*(Polynome A, Complexe B);
Polynome operator*(Polynome A, double B);

Polynome operator/(Polynome A, Complexe B);
Polynome operator/(Polynome A, double B);

Polynome operator-(Polynome A);
Polynome operator-(Polynome A, Polynome B);
Polynome operator-(Polynome A, Complexe B);
Polynome operator-(Polynome A, double B);


// --------------------------------
// --------------------------------
// ---------------- HOMOGENE
// --------------------------------
// --------------------------------

struct Homogene {

public:

	Complexe x;
	Complexe y;

	void print();


	Homogene();
	Homogene(Complexe a, Complexe b);
	Homogene(Complexe a);
	Homogene(double a, double b);
	Homogene(double a);

	Complexe carteY();
	Complexe carteX();

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

public:
	std::function<Homogene(Homogene)> fonctionRationnelle;

	FractionRationnelle();
	FractionRationnelle(Polynome numerateur);
	FractionRationnelle(Polynome numerateur, Polynome denominateur);



};

Homogene evaluationAuPoint(Polynome numerateur, Polynome denominateur, Homogene point);

#endif /* Algebre_h */
