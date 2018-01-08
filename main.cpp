
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <complex>

#include "Algebre.h"
#include "Julia.h"
#include "Cycle.h"
#include "Dynamicien.h"
#include "Mandelbrot.h"
#include "Exemples.h"


using namespace sf;
using namespace std;

int main(int argc, char** argv){
    double scale = 0.5;  //    // rupture à 1 047 809 880 pixels ~= 22^2 * 1920 * 1080
	unsigned int hauteur = scale*1080 ; //
	unsigned int longueur =  scale*1920 ;

	complex<double> i(0,1);

	// Principaux paramètres de la simulation

	double echelle = 0.00215 / scale ;
	double o_x = 0.0, o_y=0.0;
	complex<double> origine(o_x,o_y);
	int borne = 100;
	bool makeW = true;

	// Préparation de la fonction qui sera utilisée
	FractionRationnelle frac = exemple(0);
	std::function<Homogene(Homogene)> methode = frac.fonctionRationnelle;


	Dynamicien dynamicien;
	dynamicien.borneDIteration = borne;
	function<complex<double>(Homogene)> dyn;
	bool estJulia = true;
	bool estMandelbrot = !estJulia;

	// Julia
	Cycle moteurDesCycles(methode);
	std::vector<Homogene>* cycles;
	if (estJulia) {
		cycles = moteurDesCycles.getCyclesAttractifs();
		dynamicien.peindreEnBlanc = makeW;

		dyn = [methode, borne, cycles](Homogene point){
			Julia julia(methode, borne, cycles);
			return julia.convergenceDe(point);
		};
	}
	// Mandelbrot
	if (estMandelbrot) {
		dynamicien.peindreEnBlanc = true;

		dyn = [borne](Homogene point){
			Mandelbrot mandel;
			mandel.borneDIteration = borne;
			return mandel.convergencePourParametre(point.carteY());
		};
	}

    dynamicien.dynamique = dyn;


    // ===== Fabrication de l'image seule et en noir&blanc

    // Utilisation d'une symétrie verticale
    bool symetrieVerticale = false;

    std::vector<unsigned char> image;
    if (symetrieVerticale){
        hauteur = (hauteur/2)*2;
        origine.imag(0.);

        complex<double> origineBis = origine + complex<double>(0,hauteur) * (echelle/4.0);
        unsigned int hauteurBis = hauteur/2;

        std::vector<complex<double>> matrice = dynamicien.creeLaMatrice(longueur, hauteurBis, echelle, origineBis);

        image.resize(longueur * hauteur * 4);

        for (unsigned int y = 0; y < hauteurBis; y++) {
            for (unsigned int x = 0; x < longueur; x++) {
                vector<double> couleur = coloration(matrice[y*longueur+x], makeW);
                for (unsigned int k = 0; k < 3; k++) {
                    image[4 * (y * longueur + x) + k] = couleur[k];
                    image[4 * ((hauteur-1 - y) * longueur + x) + k] = couleur[k];
                }
                image[4 * (y * longueur + x) + 3] = 255;
                image[4 * ((hauteur-1 - y) * longueur + x) + 3] = 255;
            }
        }
    }
    else{
        std::vector<complex<double>> matrice = dynamicien.creeLaMatrice(longueur, hauteur, echelle, origine);

        image.resize(longueur * hauteur * 4);

        for (unsigned int y = 0; y < hauteur; y++) {
            for (unsigned int x = 0; x < longueur; x++) {
                vector<double> couleur = coloration(matrice[y*longueur+x], makeW);
                image[4 * (y * longueur + x) + 0] = couleur[0];
                image[4 * (y * longueur + x) + 1] = couleur[1];
                image[4 * (y * longueur + x) + 2] = couleur[2];
                image[4 * (y * longueur + x) + 3] = 255;
            }
        }
    }
    string filename;
    if (argc > 1)
        filename = argv[1];
    else
        filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
    lodepng::encode(filename, image, longueur, hauteur);
    //*/ // =====


	/*/ ==== Gestion de la fenêtre et des interactions avec l'utilisateur

    // Création de la fenêtre

    RenderWindow window(VideoMode(longueur, hauteur), "Simulation Julia");

    window.setFramerateLimit(5);

    bool remakeSize = false, remake = false;

    VertexArray tab = dynamicien.creeLaMatriceWin(longueur, hauteur, echelle, origine);

	while (window.isOpen()){

		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed){
				window.close();
			}

			if (event.type == Event::Resized){
				remakeSize = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				echelle /= 1.3;
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)){
				echelle *= 1.3;
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)){
				borne += (int) (borne*1.0/4);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)){
				borne -= (int) (borne*1.0/4);
				remake = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				o_y += 10*echelle;
				origine = complex<double>(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				o_y -= 10*echelle;
				origine = complex<double>(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				o_x -= 10*echelle;
				origine = complex<double>(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				o_x += 10*echelle;
				origine = complex<double>(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				dynamicien.peindreEnBlanc = true;
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::X)) {
				dynamicien.peindreEnBlanc = false;
				remake = true;
			}
			if (estJulia && Keyboard::isKeyPressed(Keyboard::C)) {
				moteurDesCycles.chercheANouveau(origine, echelle);
				std::vector<Homogene>* cycles = moteurDesCycles.getCyclesAttractifs();
				function<complex<double>(Homogene)> dyn = [methode, borne, cycles](Homogene point){
					Julia julia(methode, borne, cycles);
					return julia.convergenceDe(point);
				};
				dynamicien.dynamique = dyn;

				remake = true;
			}

		}

		if (remakeSize) {
			Vector2u size=window.getSize();
			longueur = size.x;
			hauteur = size.y;

			tab.clear();
			tab.resize(longueur*hauteur);
			tab = dynamicien.creeLaMatriceWin(longueur, hauteur, echelle, origine);

			Vector2i position = window.getPosition();
			window.create(VideoMode(longueur, hauteur), "Simulation Julia");
			window.setPosition(position);

			remakeSize = false;
		}
		if (remake) {
			tab.clear();

			dynamicien.peindreEnBlanc = makeW;
			dynamicien.borneDIteration = borne;


			// Selectionner selon la dynamique

			//  Julia
			if (estJulia) {
				dyn = [methode, borne, cycles](Homogene point){
					Julia julia(methode, borne, cycles);
					return julia.convergenceDe(point);
				};
			}

			//  Mandelbrot
			if (estMandelbrot) {
				dyn = [borne](Homogene point){
					Mandelbrot mandel;
					mandel.borneDIteration = borne;
					return mandel.convergencePourParametre(point.carteY());
				};
			}
			dynamicien.dynamique = dyn;

			tab = dynamicien.creeLaMatriceWin(longueur, hauteur, echelle, origine);

			remake = false;
		}

		window.clear(Color::White);

		window.draw(tab);

		window.display();

	}
 //*/
	return 0;
}
