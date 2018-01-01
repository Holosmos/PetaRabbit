#include <cstdlib>
#include <iostream>
#include <vector>

#include "lodepng.h"

#include "Algebre.h"
#include "Julia.h"
#include "Cycle.h"


using namespace std;


// Conversion de deux polynômes en une fraction rationnelle utilisable avec les coordonnées homogènes

// retourne false si il y a eu un problème lors de l'encodage
bool encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) {
            std::cout << "encoder error "
                      << error << ": "
                      << lodepng_error_text(error)
                      << std::endl;
            return false;
        }
        return true;
}


int main(int argc, char **argv){
	unsigned int hauteur = 300; //29160 - 1; // HAUTEUR     4320 * 7680  = 4 * 4 * 1920 * 1080
	unsigned int longueur =  350; // 900 - 1; //34830 - 1; // LONGUEUR

	double echelle, o_x, o_y;


	if(argc != 4){
		std::cout<< "Usage: " << argv[0] << "zoom offset_x offset_y" << std::endl;
		std::cout<< "If format is incorrect value is set to 0" << std::endl;
		std::cout<< "Exemple: " << argv[0] << " 0.005 0 0";
		return EXIT_FAILURE;
	}

	echelle = atof(argv[1]);
	o_x = atof(argv[2]);
	o_y = atof(argv[3]);

	Complexe i(0,1);

	// Création de la fenêtre

	// Principaux paramètres de la simulation

	Complexe origine(o_x,o_y);
	int borne = 500;
	bool makeW = true;

	// La fraction rationnelle étudiée

	vector<Complexe> p1(3,0*i);    // LAPIN
	p1[2] = 1. + 0*i;
	p1[0] = -0.123 + 0.745*i;
	vector<Complexe> p2(1,1 +0*i);

	// D'autres exemples

	/*/

	vector<Complexe> p1(3,0*i);    // LAPIN
	p1[2] = 1. + 0*i;
	p1[0] = -0.123 + 0.745*i;
	vector<Complexe> p2(1,1 +0*i);

	 vector<Complexe> p1(3,0*i);  // COLLIER
	 p1[2] = 1. + 0*i;
	 p1[0] = -1 + 0*i;
	 vector<Complexe> p2(3,0*i);
	 p2[2] = 1. + 0*i;

	 vector<Complexe> p1(3,0*i); // GALAXIE
	 p1[2] = -0.138 + 0*i;
	 p1[1] = -0.303 + 0*i;
	 p1[0] = -0.138 + 0*i;
	 vector<Complexe> p2(2,0*i);
	 p2[1] = 1 +0*i;

	 vector<Complexe> p1(3,0*i); // STRANGE
	 p1[2] = 1. + 0*i;
	 p1[0] = -0.8 + 0.*i;
	 vector<Complexe> p2(1,1 +0*i);

	 vector<Complexe> p1(4,0*i);  // NEWTON
	 p1[3] = 2. + 0*i;
	 p1[0] = -2. + 0*i;
	 vector<Complexe> p2(3,0*i);
	 p2[2] = 3. + 0*i;
	 p2[0] = -2. + 0*i;


	 vector<Complexe> p1(26,0*i);   // PENTAGONE
	 p1[25] = 87. + 0*i;
	 p1[20] = -3335. + 0*i;
	 p1[10] = -6670. + 0*i;
	 p1[5] = -435. + 0*i;
	 p1[0] = 1. + 0*i;
	 vector<Complexe> p2(30,0*i);
	 p2[29] = -1.+0*i;
	 p2[24] = -435. + 0*i;
	 p2[19] = 6670. + 0*i;
	 p2[9] = 3335. + 0*i;
	 p2[4]  = 87. + 0*i;



	//*/



	// Préparation de la fonction qui sera utilisée

	Polynome nume = Polynome(p1), deno = Polynome(p2);
	FractionRationnelle frac(nume, deno);
	std::function<Homogene(Homogene)> methode = frac.fonctionRationnelle;


	// Lancement de l'objet Julia

	Julia julia(methode);
	julia.borneDIteration = borne;
	julia.peindreEnBlanc = makeW;

	const char* filename =  "photoJulia.png";
	std::vector<unsigned char> image;
	image.resize(longueur * hauteur * 4);

        julia.creeLaMatrice(image, longueur, hauteur, echelle, origine); // Fill image
	if(encodeOneStep(filename, image, longueur, hauteur) == false)
            return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
