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
// ---------------- COMPLEXE
// --------------------------------
// --------------------------------

// Initialisateurs

Complexe::Complexe() : partieRe(0), partieIm(0){}

Complexe::Complexe(double partieReelle): partieRe(partieReelle), partieIm(0){}

Complexe::Complexe(double partieReelle,double partieImaginaire) : partieRe(partieReelle), partieIm(partieImaginaire){}


// Setter-Getter

void Complexe::print(){
	if (partieRe != 0) {
		std::cout << partieRe;
		if (partieIm > 0) {
			std::cout << " + " << partieIm << " * i";
		}
		if (partieIm < 0) {
			std::cout << " - " << partieIm * -1 << " * i";
		}
		std::cout << std::endl;
	}
	else{
		if (partieIm != 0) {
			std::cout << partieIm << " * i"  << std::endl;
		}
		else{
			std::cout << 0 << std::endl;
		}
	}
}


double Complexe::partieReelle(){return partieRe;}
double Complexe::partieImaginaire(){return partieIm;}

void Complexe::partieReelle(double partieReelle){partieRe = partieReelle;}
void Complexe::partieImaginaire(double partieImaginaire){partieIm = partieImaginaire;}

// Opérations algébriques


double Complexe::moduleAuCarre(){
	return partieRe*partieRe + partieIm*partieIm;
}
double Complexe::module(){
	return sqrt(moduleAuCarre());
}
Complexe Complexe::conjugue(){
	return Complexe(partieRe, -partieIm);
}

Complexe Complexe::additionAvec(Complexe nombreComplexe){
	return Complexe(partieRe + nombreComplexe.partieReelle(),
					partieIm + nombreComplexe.partieImaginaire());
}
Complexe Complexe::oppose(){
	return Complexe(-partieRe, -partieIm);
}
Complexe Complexe::multiplicationAvec(Complexe nombreComplexe){
	return Complexe(partieRe * nombreComplexe.partieReelle() - partieIm * nombreComplexe.partieImaginaire(),
					partieIm * nombreComplexe.partieReelle() + partieRe* nombreComplexe.partieImaginaire());
}
Complexe Complexe::multiplicationAvec(double scalaire){
	return Complexe(scalaire * partieRe, scalaire * partieIm);
}
Complexe Complexe::inverse(){
	return conjugue().multiplicationAvec(1.0/moduleAuCarre());
}

Complexe Complexe::racineCarree(){
	double mod = module();
	double theta = acos(partieRe/mod);
	return sqrt(mod) * Complexe(cos(theta/2.0),sin(theta/2.0));
}


Complexe operator+(Complexe a,Complexe b){
	return a.additionAvec(b);
}
Complexe operator+(Complexe a, double b){
	return a + Complexe(b);
}
Complexe operator+(double a, Complexe b){
	return Complexe(a) + b;
}

Complexe operator-(Complexe a){
	return a.oppose();
}
Complexe operator-(Complexe a,Complexe b){
	return a + (-b);
}
Complexe operator-(Complexe a, double b){
	return a + (-Complexe(b));
}
Complexe operator-(double a, Complexe b){
	return Complexe(a) - b;
}

Complexe operator*(Complexe a,Complexe b){
	return a.multiplicationAvec(b);
}
Complexe operator*(Complexe a, double b){
	return a.multiplicationAvec(b);
}
Complexe operator*(double a, Complexe b){
	return b.multiplicationAvec(a);
}

Complexe operator/(Complexe a,Complexe b){
	return a * b.inverse();
}
Complexe operator/(Complexe a, double b){
	return a.multiplicationAvec(1.0/b);
}
Complexe operator/(double a, Complexe b){
	return b.multiplicationAvec(1.0/a);
}

bool operator==(Complexe a, Complexe b){
	return a.partieReelle() == b.partieReelle() &&
	       a.partieImaginaire() == b.partieImaginaire();
}
bool operator==(Complexe a, double b){
	return a == Complexe(b);
}
bool operator!=(Complexe a, Complexe b){
	return !(a==b);
}
bool operator!=(Complexe a, double b){
	return !(a==b);
}



// --------------------------------
// --------------------------------
// ---------------- POLYNOME
// --------------------------------
// --------------------------------

// Initialisateurs

Polynome::Polynome() : degreDuPolynome(0), uniteImaginaire(0,1) {
	std::vector<Complexe> coeff(0);
	coeff.push_back(Complexe(0));
	coefficientsDuPolynome = coeff;
}
Polynome::Polynome(std::vector<Complexe> coefficientsDuPolynome): coefficientsDuPolynome(coefficientsDuPolynome), uniteImaginaire(0,1){
	degreDuPolynome = coefficientsDuPolynome.size() - 1;
}
Polynome::Polynome(Complexe constante){
	std::vector<Complexe> coeff(0);
	coeff.push_back(constante);
	coefficientsDuPolynome = coeff ;
	uniteImaginaire = Complexe(0,1);
	degreDuPolynome = coeff.size() - 1;
}


// Getter-Setter

void Polynome::print(){
	for (int i = 0; i <= degreDuPolynome ; i++){
		std::cout << coefficientsDuPolynome[i].partieReelle();
		if (coefficientsDuPolynome[i].partieImaginaire() != 0) {
			std::cout << " + i * " << coefficientsDuPolynome[i].partieImaginaire();
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
}

unsigned int Polynome::degre(){
	return degreDuPolynome;
}
Complexe Polynome::coefficientDIndice(unsigned int i){
	return coefficientsDuPolynome[i+1];
}


// Opérations algébriques

unsigned int max(unsigned int a, unsigned int b){return a<b ? b : a;}
unsigned int min(unsigned int a, unsigned int b){return a<b ? a : b;}


Polynome Polynome::additionAvec(Polynome polynome){
	std::vector<Complexe> nouveauxCoefficients(0);

	unsigned int nouveauDegre = max(degreDuPolynome, polynome.degre());
	unsigned int minDegre = min(degreDuPolynome, polynome.degre());

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
Polynome Polynome::multiplicationAvec(Complexe scalaire){
	std::vector<Complexe> nouveauxCoefficients(0);
	for (unsigned int i = 0; i <= degreDuPolynome; i++) {
		nouveauxCoefficients.push_back(scalaire*coefficientsDuPolynome[i]);
	}
	return Polynome(nouveauxCoefficients);
}
Polynome Polynome::multiplicationAvec(Polynome polynome){
	std::vector<Complexe> nouveauxCoefficients(0);
	unsigned int nouveauDegre = degreDuPolynome + polynome.degre();

	bool premierDegrePlusGrand = degreDuPolynome >= polynome.degre();

	for (unsigned int i = 0; i <= nouveauDegre; i++) {

		Complexe scalaireDegreI;

		if (premierDegrePlusGrand){
			for (unsigned int j = 0; j <= polynome.degre(); j++){
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

Complexe Polynome::evaluationAuPoint(Complexe point){
	Complexe valeur(0);
	Complexe puissanceDuPoint(1);
	for (unsigned int i = 0; i <= degreDuPolynome; i++) {
		valeur = valeur + (puissanceDuPoint * coefficientsDuPolynome[i]) ;
		puissanceDuPoint = point * puissanceDuPoint;
	}
	return valeur;
}

Polynome Polynome::polynomeDerive(){
	std::vector<Complexe> nouveauxCoefficients(0);

	for (unsigned int i = 1; i <= degreDuPolynome - 1; i++) {
		Complexe coefficient = i * coefficientsDuPolynome[i];
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
Polynome operator+(Polynome A, Complexe B){
	return A + Polynome(B);
}
Polynome operator+(Polynome A, double B){
	return A + Polynome(Complexe(B));
}

Polynome operator*(Polynome A, Polynome B){
	return A.multiplicationAvec(B);
}
Polynome operator*(Polynome A, Complexe B){
	return A.multiplicationAvec(B);
}
Polynome operator*(Polynome A, double B){
	return A.multiplicationAvec(Complexe(B));
}

Polynome operator/(Polynome A, Complexe B){
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
Polynome operator-(Polynome A, Complexe B){
	return A - Polynome(B);
}
Polynome operator-(Polynome A, double B){
	return A - Polynome(Complexe(B));
}



// --------------------------------
// --------------------------------
// ---------------- HOMOGENE
// --------------------------------
// --------------------------------


Homogene::Homogene() : x(0.0), y(1.0) {}

Homogene::Homogene(Complexe a, Complexe b){
	x = a;
	y = b;
}
Homogene::Homogene(Complexe a){
	x = a;
	y = Complexe(1.0);
}
Homogene::Homogene(double a, double b){
	x = Complexe(a);
	y = Complexe(b);
}
Homogene::Homogene(double a){
	x = Complexe(a);
	y = Complexe(1.0);
}

void Homogene::print(){

	if (y != 0.0) {
		x = x/y;
		y = Complexe(1.0);
	}
	else{
		x = Complexe(1.0);
	}
	double a1 = x.partieReelle();
	double a2 = x.partieImaginaire();

	double b1 = y.partieReelle();
	double b2 = y.partieImaginaire();

	std::cout << "["<<a1<< " + "<<a2<<" * i  :  "<<b1<<" + "<<b2<<" * i]"<<std::endl;
}

Complexe Homogene::carteY(){return x/y;}
Complexe Homogene::carteX(){return y/x;}

double Homogene::distanceAvec(Homogene b){
	if (y != 0 && b.y != 0) {
		return (x * b.y - y * b.x).module()/(y * b.y).module();
	}
	else{
		if (y == 0.0 && b.y == 0.0){
			return 0.0;
		}
		else if (b.y == 0.0){
			return y.module()/x.module() ;
		}
		else{
			return b.y.module()/b.x.module() ;
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
	denominateur = Polynome(Complexe(1.0));

	Polynome nume = numerateur;
	Polynome deno = denominateur;
	fonctionRationnelle = [nume, deno](Homogene point){return evaluationAuPoint(nume, deno, point);};
}
FractionRationnelle::FractionRationnelle(Polynome num){
	numerateur = num;
	denominateur = Polynome(Complexe(1.0));

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
		Complexe a = point.carteY();
		return Homogene(numerateur.evaluationAuPoint(a),
						denominateur.evaluationAuPoint(a));
	}
	// Cas à l'infini
	else{
		if (numerateur.degre() > denominateur.degre()) {
			return Homogene(1.0,0.0);
		}
		else if(denominateur.degre() > numerateur.degre()){
			return Homogene(0.0);
		}
		else{
			return Homogene(numerateur.coefficientDIndice(numerateur.			degre())
							/ denominateur.coefficientDIndice(denominateur.degre()));
		}
	}
}


