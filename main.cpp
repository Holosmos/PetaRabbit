
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "lodepng.h"

#include "Algebre.cpp"
#include "Julia.cpp"
#include "Cycle.cpp"


using namespace sf;
using namespace std;


// Conversion de deux polynômes en une fraction rationnelle utilisable avec les coordonnées homogènes

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);
	
	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


int main(){
	unsigned int hauteur = 300 -1; //29160 - 1; // HAUTEUR     4320 * 7680  = 4 * 4 * 1920 * 1080
	unsigned int longueur =  350 - 1; // 900 - 1; //34830 - 1; // LONGUEUR
	
	Complexe i(0,1);
	
	// Création de la fenêtre
 
	RenderWindow window(VideoMode(longueur, hauteur), "Simulation Julia");
 
	window.setFramerateLimit(5);
 
	bool remakeSize = false, remake = false;
 
	// Principaux paramètres de la simulation
	
	double echelle = 0.005 ;
	double o_x = 0.0,o_y=0.0;
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
	VertexArray tab = julia.creeLaMatrice(longueur, hauteur, echelle, origine);

	
	const char* filename =  "/Users/Raphael/Desktop/PhotoJulia.png";
	
	//generate some image
	unsigned lon = longueur+1;
	unsigned hau = hauteur+1;
	
	std::vector<unsigned char> image;
	image.resize(lon * hau * 4);
	for(unsigned long long int y = 0; y < hau; y++)
		for(unsigned long long int x = 0; x < lon; x++)
		{
	  image[4 * y * lon + 4 * x + 0] = tab[y * lon + x].color.r;
	  image[4 * y * lon + 4 * x + 1] = tab[y * lon + x].color.g,
	  image[4 * y * lon + 4 * x + 2] = tab[y * lon + x].color.b;
	  image[4 * y * lon + 4 * x + 3] = tab[y * lon + x].color.a;
		}
	
	encodeOneStep(filename, image, lon, hau);
	
	
	// Gestion de la fenêtre et des interactions avec l'utilisateur
	
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
				julia.peindreEnBlanc = true;
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::X)) {
				julia.peindreEnBlanc = false;
				remake = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::C)) {
				julia.chercheANouveau(origine, echelle, longueur, hauteur);
				remake = true;
			}
			
		}
		
		if (remakeSize) {
			
			Vector2u size=window.getSize();
			longueur = size.x;
			hauteur = size.y;
			
			tab.clear();
			tab.resize(longueur*hauteur);
			tab = julia.creeLaMatrice(longueur, hauteur, echelle, origine);
			
			Vector2i position = window.getPosition();
			window.create(VideoMode(longueur, hauteur), "Simulation Julia");
			window.setPosition(position);
			
			remakeSize = false;
		}
		if (remake) {
			
			tab.clear();
			julia.borneDIteration = borne;
			tab = julia.creeLaMatrice(longueur, hauteur, echelle, origine);
			remake = false;
		}
		
		window.clear(Color::White);
		
		window.draw(tab);
		
		window.display();
		
	}
 //*/
	return 0;
}
