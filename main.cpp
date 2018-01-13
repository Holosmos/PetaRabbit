#include <cstdlib>
#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#include "Parametres.h"

// Premier axe

#include "Algebre.h"

#include "Cycle.h"
#include "Julia.h"
#include "Mandelbrot.h"

// Deuxième axe

#include "Dynamicien.h"

// Troisième axe

#include "Moteur.h"


int main(int argc, char** argv){

    // Récupération input
    string filename =  cheminFichierPhoto;
    double zoom = 1.;
    double offSetX = 0;
    double offSetY = 0;
    if (argc > 1)
        zoom = atof(argv[1]);
    if (argc > 2)
        offSetX = atof(argv[2]);
    if (argc > 3)
        offSetY = atof(argv[3]);
    if (argc > 4)
        filename = argv[4];
    
    zoom = pow(2,zoom);
    double echelle = echelleInitiale/zoom;
    
    // == Paramètres simulation

    unsigned int hauteur = facteur * 100 ;
    unsigned int longueur =  facteur * 100 ;
    
    double o_x = origineInitale.real(), o_y = origineInitale.imag();
    o_x += offSetX*echelle - longueur*echelle/2.;
    o_y += offSetY*echelle - hauteur*echelle/2.;
    complex<double> origine(o_x,o_y);

    // == Préparation du moteur de la dynamique

	Dynamicien dynamicien(peindreEnBlanc);
	function<complex<double>(Homogene)> dyn;

    // == Préparation de la fonction qui sera utilisée
    const function<Homogene(Homogene)> fonction = fonctionJulia;
    
	// Cas d'un Julia
    vector<Homogene>* cycles = new vector<Homogene>;
    Cycle moteurDesCycles(fonction, cycles);
    Julia julia(fonction, cycles);
	if (estJulia) {
        moteurDesCycles.calculeLesCyclesAttractifs();
		dyn = [&julia](Homogene point){
			return julia.convergenceDe(point);
		};
	}
	// Cas d'un Mandelbrot
    Mandelbrot mandel;
	if (estMandelbrot) {
		dyn = [&mandel](Homogene point){
			return mandel.convergencePourParametre(point.carteY());
		};
	}
    dynamicien.dynamique = dyn;

    // Création de l'image
    vector<unsigned char> image = faireImage(hauteur, longueur, echelle, origine, dynamicien);
    lodepng::encode(filename, image, longueur, hauteur);
 
	return 0;
}
