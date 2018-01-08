//
//  Algebre.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 31/12/2017.
//  Copyright © 2017 Raphaël Alexandre. All rights reserved.
//

#include "Algebre.h"

// --------------------------------
// --------------------------------
// ---------------- POLYNOME
// --------------------------------
// --------------------------------

// Initialisateurs

Polynome::Polynome() : degreDuPolynome(0) {
	std::vector<complex<double>> coeff(0);
	coeff.push_back(complex<double>(0.0,0.0));
	coefficientsDuPolynome = coeff;
}
Polynome::Polynome(std::vector<complex<double>> coefficientsDuPolynome): coefficientsDuPolynome(coefficientsDuPolynome){
	degreDuPolynome = coefficientsDuPolynome.size() - 1;
}
Polynome::Polynome(complex<double> constante){
	std::vector<complex<double>> coeff(0);
	coeff.push_back(constante);
	coefficientsDuPolynome = coeff ;
	degreDuPolynome = coeff.size() - 1;
}


void Polynome::print(){
	for (int i = 0; i <= degreDuPolynome ; i++){
		std::cout << coefficientsDuPolynome[i].real();
		if (coefficientsDuPolynome[i].imag() != 0) {
			std::cout << " + i * " << coefficientsDuPolynome[i].imag();
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
}

complex<double> Polynome::coefficientDIndice(unsigned int i){
	return coefficientsDuPolynome[i+1];
}


// Opérations algébriques

unsigned int max(unsigned int a, unsigned int b){return a<b ? b : a;}
unsigned int min(unsigned int a, unsigned int b){return a<b ? a : b;}


Polynome Polynome::additionAvec(Polynome polynome){
	std::vector<complex<double>> nouveauxCoefficients(0);

	unsigned int nouveauDegre = max(degreDuPolynome, polynome.degreDuPolynome);
	unsigned int minDegre = min(degreDuPolynome, polynome.degreDuPolynome);

	for (unsigned int i = 0 ; i <= minDegre ; i++){
		nouveauxCoefficients.push_back(coefficientsDuPolynome[i] + polynome.coefficientDIndice(i));
	}
	for (unsigned int i = minDegre + 1 ; i <= nouveauDegre ; i++){
		if (nouveauDegre == degreDuPolynome){
			nouveauxCoefficients.push_back(coefficientsDuPolynome[i]);
		}
		else{
			nouveauxCoefficients.push_back(polynome.coefficientDIndice(i));
		}
	}
	return Polynome(nouveauxCoefficients);
}
Polynome Polynome::multiplicationAvec(complex<double> scalaire){
	std::vector<complex<double>> nouveauxCoefficients(0);
	for (unsigned int i = 0; i <= degreDuPolynome; i++) {
		nouveauxCoefficients.push_back(scalaire*coefficientsDuPolynome[i]);
	}
	return Polynome(nouveauxCoefficients);
}
Polynome Polynome::multiplicationAvec(Polynome polynome){
	std::vector<complex<double>> nouveauxCoefficients(0);
	unsigned int nouveauDegre = degreDuPolynome + polynome.degreDuPolynome;

	bool premierDegrePlusGrand = degreDuPolynome >= polynome.degreDuPolynome;

	for (unsigned int i = 0; i <= nouveauDegre; i++) {

		complex<double> scalaireDegreI;

		if (premierDegrePlusGrand){
			for (unsigned int j = 0; j <= polynome.degreDuPolynome; j++){
				unsigned int k = i-j ;
				scalaireDegreI = scalaireDegreI + (coefficientsDuPolynome[k] * polynome.coefficientDIndice(j));
			}
		}
		else{
			for (unsigned int j = 0; j <= degreDuPolynome; j++){
				unsigned int k = i-j ;
				scalaireDegreI = scalaireDegreI + (coefficientsDuPolynome[j] * polynome.coefficientDIndice(k));
			}
		}

		nouveauxCoefficients.push_back(scalaireDegreI);
	}

	return Polynome(nouveauxCoefficients);
}

complex<double> Polynome::evaluationAuPoint(complex<double> point){
	complex<double> valeur(0);
	complex<double> puissanceDuPoint(1);
	for (unsigned int i = 0; i <= degreDuPolynome; i++) {
		valeur = valeur + (puissanceDuPoint * coefficientsDuPolynome[i]) ;
		puissanceDuPoint = point * puissanceDuPoint;
	}
	return valeur;
}

Polynome Polynome::polynomeDerive(){
	std::vector<complex<double>> nouveauxCoefficients(0);

	for (unsigned int i = 1; i <= degreDuPolynome - 1; i++) {
		complex<double> coefficient = complex<double>(i,0.) * coefficientsDuPolynome[i];
		nouveauxCoefficients.push_back(coefficient);
	}
	return Polynome(nouveauxCoefficients);
}
Polynome Polynome::polynomeDeriveNeme(unsigned int n){
	Polynome resultat(coefficientsDuPolynome);
	for (unsigned int i = 1; i <= n; i++) {
		resultat = resultat.polynomeDerive();
	}
	return resultat;
}



Polynome operator+(Polynome A, Polynome B){
	return A.additionAvec(B);
}
Polynome operator+(Polynome A, complex<double> B){
	return A + Polynome(B);
}
Polynome operator+(Polynome A, double B){
	return A + Polynome(complex<double>(B));
}

Polynome operator*(Polynome A, Polynome B){
	return A.multiplicationAvec(B);
}
Polynome operator*(Polynome A, complex<double> B){
	return A.multiplicationAvec(B);
}
Polynome operator*(Polynome A, double B){
	return A.multiplicationAvec(complex<double>(B));
}

Polynome operator/(Polynome A, complex<double> B){
	return A * (1.0/B);
}
Polynome operator/(Polynome A, double B){
	return A * (1.0/B);
}

Polynome operator-(Polynome A){
	return A*(-1.0);
}
Polynome operator-(Polynome A, Polynome B){
	return A + (-B);
}
Polynome operator-(Polynome A, complex<double> B){
	return A - Polynome(B);
}
Polynome operator-(Polynome A, double B){
	return A - Polynome(complex<double>(B));
}



// --------------------------------
// --------------------------------
// ---------------- HOMOGENE
// --------------------------------
// --------------------------------


Homogene::Homogene() : x(0.0), y(1.0) {}

Homogene::Homogene(complex<double> a, complex<double> b){
	x = a;
	y = b;
}
Homogene::Homogene(complex<double> a){
	x = a;
	y = complex<double>(1.0);
}
Homogene::Homogene(double a, double b){
	x = complex<double>(a);
	y = complex<double>(b);
}
Homogene::Homogene(double a){
	x = complex<double>(a);
	y = complex<double>(1.0);
}

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

// --------------------------------
// --------------------------------
// ---------------- FRACTION RATIONNELLE
// --------------------------------
// --------------------------------


FractionRationnelle::FractionRationnelle(){
	numerateur = Polynome();
	denominateur = Polynome(complex<double>(1.0));

	Polynome nume = numerateur;
	Polynome deno = denominateur;
	fonctionRationnelle = [nume, deno](Homogene point){return evaluationAuPoint(nume, deno, point);};
}
FractionRationnelle::FractionRationnelle(Polynome num){
	numerateur = num;
	denominateur = Polynome(complex<double>(1.0));

	Polynome nume = numerateur;
	Polynome deno = denominateur;
	fonctionRationnelle = [nume, deno](Homogene point){return evaluationAuPoint(nume, deno, point);};
}
FractionRationnelle::FractionRationnelle(Polynome num, Polynome denom){
	numerateur = num;
	denominateur = denom;

	Polynome nume = numerateur;
	Polynome deno = denominateur;
	fonctionRationnelle = [nume, deno](Homogene point){return evaluationAuPoint(nume, deno, point);};
}

Homogene evaluationAuPoint(Polynome numerateur, Polynome denominateur, Homogene point){
	// Cas complexe
	if (point.y != 0.0) {
		complex<double> a = point.carteY();
		return Homogene(numerateur.evaluationAuPoint(a),
						denominateur.evaluationAuPoint(a));
	}
	// Cas à l'infini
	else{
		if (numerateur.degreDuPolynome > denominateur.degreDuPolynome) {
			return Homogene(1.0,0.0);
		}
		else if(denominateur.degreDuPolynome > numerateur.degreDuPolynome){
			return Homogene(0.0);
		}
		else{
			return Homogene(numerateur.coefficientDIndice(numerateur.degreDuPolynome)
							/ denominateur.coefficientDIndice(denominateur.degreDuPolynome));
		}
	}
}


