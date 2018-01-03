
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Algebre.h"
#include "Julia.h"
#include "Cycle.h"
#include "Dynamicien.h"
#include "Mandelbrot.h"


using namespace sf;
using namespace std;


int main(){
    double scale = 1;  //    // rupture à 1 047 809 880 pixels ~= 22^2 * 1920 * 1080
	unsigned int hauteur = scale*1080 ; //
	unsigned int longueur =  scale*1920 ;
	
	Complexe i(0,1);
 
	// Principaux paramètres de la simulation
	
	double echelle = 0.00215 / scale ;
	double o_x = 0.0, o_y=0.0;
	Complexe origine(o_x,o_y);
	int borne = 1200;
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
	
	
	Dynamicien dynamicien;
	dynamicien.borneDIteration = borne;
	function<Complexe(Homogene)> dyn;
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
	//
	// Mandelbrot
	if (estMandelbrot) {
		dynamicien.peindreEnBlanc = true;
		
		dyn = [borne](Homogene point){
			Mandelbrot mandel;
			mandel.borneDIteration = borne;
			return mandel.convergencePourParametre(point.carteY());
		};
	}
	//
	
    dynamicien.dynamique = dyn;
    
    
    // ===== Fabrication de l'image seule et en noir&blanc
    
    
    // Utilisation d'une symétrie verticale
    bool symetrieVerticale = false;
    
    if (symetrieVerticale){
        hauteur = (hauteur/2)*2;
        origine.partieImaginaire(0.);
        
        Complexe origineBis = origine + Complexe(0,hauteur) * (echelle/4.0);
        unsigned int hauteurBis = hauteur/2;
        
        std::vector<Complexe> matrice = dynamicien.creeLaMatrice(longueur, hauteurBis, echelle, origineBis);
        
        std::vector<unsigned char> image;
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
        const char* filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
        lodepng::encode(filename, image, longueur, hauteur);
    }
    else{
        std::vector<Complexe> matrice = dynamicien.creeLaMatrice(longueur, hauteur, echelle, origine);
        
        std::vector<unsigned char> image;
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
        const char* filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
        lodepng::encode(filename, image, longueur, hauteur);
    }
    //*/ =====
    
	
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
				origine = Complexe(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				o_y -= 10*echelle;
				origine = Complexe(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				o_x -= 10*echelle;
				origine = Complexe(o_x,o_y);
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				o_x += 10*echelle;
				origine = Complexe(o_x,o_y);
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
				function<Complexe(Homogene)> dyn = [methode, borne, cycles](Homogene point){
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
