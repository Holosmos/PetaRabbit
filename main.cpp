
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <complex>

using namespace sf;
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

    // == Paramètres simulation
    
    double facteur = facteurResolutionInitiale;  //    // rupture à 1 047 809 880 pixels ~= 22^2 * 1920 * 1080
    unsigned int hauteur = facteur * 1080 ;
    unsigned int longueur =  facteur * 1920 ;
    
    double echelle = echelleInitiale / facteur ;
    double o_x = origineInitale.real(), o_y = origineInitale.imag();
    complex<double> origine(o_x,o_y);

    unsigned int borne = borneInitiale;

    // == Préparation du moteur de la dynamique

	Dynamicien dynamicien(borne, peindreEnBlanc);
	function<complex<double>(Homogene)> dyn;

    // == Préparation de la fonction qui sera utilisée

    //const function<Homogene(Homogene)> fonction = fracJulia.fonctionRationnelle;
    const function<Homogene(Homogene)> fonction = fonctionJulia;
    
	// Cas d'un Julia
    vector<Homogene>* cycles = new vector<Homogene>;
    Cycle moteurDesCycles(fonction, cycles);
    Julia julia(fonction, borne, cycles);
	if (estJulia) {
        moteurDesCycles.calculeLesCyclesAttractifs();
		dyn = [&julia](Homogene point){
			return julia.convergenceDe(point);
		};
	}
	// Cas d'un Mandelbrot
    Mandelbrot mandel(borne);
	if (estMandelbrot) {
		dyn = [&mandel](Homogene point){
			return mandel.convergencePourParametre(point.carteY());
		};
	}

    dynamicien.dynamique = dyn;

    // ===== Fabrication de l'image seule =====
    if (fabricationImage){
        vector<unsigned char> image = faireImage(hauteur, longueur, origine, echelle, peindreEnBlanc, symetrieVerticale, dynamicien);
        
        string filename;
        if (argc > 1)
            filename = argv[1];
        else
            filename =  cheminFichierPhoto;
        lodepng::encode(filename, image, longueur, hauteur);
    }
    //*/ // =====


	// ===== Gestion de la fenêtre et des interactions avec l'utilisateur =====
    if (fenetreSimulation){
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
                if (estJulia && Keyboard::isKeyPressed(Keyboard::C)) {
                    moteurDesCycles.chercheANouveau(origine, echelle);
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
                
                dynamicien.peindreEnBlanc = peindreEnBlanc;
                dynamicien.borneDIteration = borne;
                
                // Selectionner selon la dynamique
                
                //  Julia
                if (estJulia)
                    julia.borneDIteration = borne;
                
                //  Mandelbrot
                if (estMandelbrot)
                    mandel.borneDIteration = borne;
                
                tab = dynamicien.creeLaMatriceWin(longueur, hauteur, echelle, origine);
                remake = false;
            }
            
            window.clear(Color::White);
            
            window.draw(tab);
            
            window.display();
        }
    }
 //*/
	return 0;
}
