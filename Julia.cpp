#include "Julia.h"

using namespace sf;
using namespace std;


// Initialisateur

Julia::Julia(std::function<Homogene (Homogene)> fonction): fonctionIteree(fonction), moteurDesCycles(Cycle(fonction)){
	
	srand (static_cast <unsigned> (time(0)));
	
	cyclesAttractifs = vector<Homogene>(0);
	
	
	// Etude du point à l'infini
	Homogene cycleInfini = moteurDesCycles.chercheUnCycleAuPoint(pointInfini, pointDefaut); // Tente le cycle à l'infini
	
	if (cycleInfini.x != pointDefaut.x || cycleInfini.y != pointDefaut.y) { // Regarde si on récupère un cycle ou le point par défaut
		cyclesAttractifs.push_back(cycleInfini);
	}
	
	// Tirage de quelques points
	unsigned int nombreDeTirages = 200;
	
	for (int j =1; j<= nombreDeTirages; j++) {
		
		Complexe z((((rand()%2==0)?-1:1)*rand()%45678)/45678.*j/10.,
				   (((rand()%2==0)?-1:1)*rand()%45678)/45678.*j/10.);
		
		Homogene z0(z);
		
		Homogene cycleZ0 = moteurDesCycles.chercheUnCycleAuPoint(z0, pointDefaut);
		
		if (cycleZ0.x != pointDefaut.x || cycleZ0.y != pointDefaut.y) {
			if (nEstPasDejaUnCycle(cycleZ0)){ // vérifie que le cycle n'est pas déjà existant dans la liste
				cyclesAttractifs.push_back(cycleZ0);
				cycleZ0.print();
			}
		}
		
	}
	cout << cyclesAttractifs.size() << endl;
	
}

// Recherche des cycles

void Julia::chercheANouveau(Complexe origine, double echelle, int longueur, int hauteur){
	
	// Recherche plus ciblée de cycles
	unsigned int nombreTirages = 100;
	
	for (int j =1; j<= nombreTirages; j++) {
		Complexe z((((rand()%2==0)?-1:1)*rand()%123456)/123456.*echelle/10.,
				   (((rand()%2==0)?-1:1)*rand()%123456)/123456.*echelle/10.);
		z = z + origine;
		
		Homogene z0(z);
		Homogene cycleZ0 = moteurDesCycles.chercheUnCycleAuPoint(z0, pointDefaut);
		
		if (cycleZ0.x != pointDefaut.x || cycleZ0.y != pointDefaut.y) {
			if (nEstPasDejaUnCycle(cycleZ0)){ // vérifie que le cycle n'est pas déjà existant dans la liste
				cyclesAttractifs.push_back(cycleZ0);
				cycleZ0.print();
			}
		}
	}
	cout << cyclesAttractifs.size() << endl;
}

bool Julia::nEstPasDejaUnCycle(Homogene point, double parametreDistance){
	
	// Vérification que le cycle n'est pas déjà répertorié
	
	unsigned long nombreDeCycles = cyclesAttractifs.size();
	
	for (int j = 0; j < nombreDeCycles; j++) {
		
		Homogene cycle = cyclesAttractifs[j];
		Homogene copie = point;
		
		if (copie.distanceAvec(cycle) < parametreDistance) {
			return false;
		}
		
		bool estDifferent = false;
		
		unsigned int nombreIterationsTests = 300;
		// On itère jusqu'à nombreIterationsTests qui représente la longueur maximale pour un cycle considéré
		for (int k = 1; k <= nombreIterationsTests && !estDifferent; k++) {
			copie = fonctionIteree(copie);
			if (copie.distanceAvec(cycle) < parametreDistance) {
				return false;
			}
			if (copie.distanceAvec(point) < parametreDistance) { // C'est le cas où le cycle s'est bouclé sans rencontrer l'autre cycle
				estDifferent = true;
			}
		}
	}
	return true;
}

// Test de convergence des itérées


Complexe Julia::convergenceDe(Homogene z, double parametreConvergence){

	// Etude de la convergence d'un point donné
	
	Homogene copie = z; // Utile pour la seconde partie de la fonction
	
	for (int j = 0; j <= borneDIteration; j++){
		for (int k = 0; k < cyclesAttractifs.size(); k++) {
			Homogene cycle = cyclesAttractifs[k];
			if (cycle.distanceAvec(z) < parametreConvergence) {
				return Complexe(j,k+1); // correspond au message : j itérées, proche du cycle k
			}
		}
		z = fonctionIteree(z);
	}
	
	// Recherche d'un cycle en cas de non convergence
	// À activer selon les cas, peut allonger la durer d'execution.
	//
	
	Homogene cycle = moteurDesCycles.chercheUnCycleAuPoint(z, pointDefaut);
	
	if ((cycle.x != pointDefaut.x || cycle.y != pointDefaut.y)) {
		cyclesAttractifs.push_back(cycle);
		cout << "+1";
		cycle.print();
		for (int j = 0; j<= borneDIteration ; j++) {
			if ( copie.distanceAvec(cycle) < parametreConvergence) {
				return Complexe(j, cyclesAttractifs.size());
			}
			copie = fonctionIteree(copie);
		}
	}
	
	//*/
	 
	return Complexe(borneDIteration); // renvoie le message qu'il n'y a pas eu de convergence

}

// Création de la matrice


void calculeLigne(int y, int longueur, int hauteur,
				  double echelle, Complexe origine,
				  int borneDIteration, bool peindreEnBlanc,
				  function<Complexe(Homogene)> convergenceDe,
				  VertexArray *matrice){
	
	int k = y*(longueur + 1); // Ce sera la case du tableau matrice : correspond au nombre de points déjà calculés
	
	for (int j = 0; j<= longueur ; j++){
		
		// Calculs des coordonnées du pixel choisi
		
		Complexe z0 = Complexe(j,hauteur-y) * echelle;
		z0 = z0 + origine;
		
		// Calculs sur la convergence du point
		
		Homogene z(z0,Complexe(1,0));
		Complexe resultatConvergence = convergenceDe(z);
		int nombreIteree = resultatConvergence.partieReelle();
		
		// Coloration en fonction du nombre d'itérées
		
		int couleur = 255 - ((nombreIteree>=35) ?
						 (137 + (int)(0.5 + nombreIteree*1.0 / borneDIteration*118))
						 : nombreIteree * 4);  // formule maison pour une harmonie
		if (peindreEnBlanc) {
			(*matrice)[k] = Vertex(Vector2f(j,y), Color(couleur,couleur,couleur));
		}
		else{
			switch (int(resultatConvergence.partieImaginaire())%7) { // 7 couleurs prévues
				case 0:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(couleur,couleur,couleur));
					break;
				case 1:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(couleur,0,0));
					break;
				case 2:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(0,couleur,0));
					break;
				case 3:
					(*matrice)[k] = Vertex(Vector2f(j,y),Color(0,0,couleur));
					break;
				case 4:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(couleur,couleur,0));
					break;
				case 5:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(0,couleur,couleur));
					break;
				case 6:
					(*matrice)[k] = Vertex(Vector2f(j,y), Color(couleur,0,couleur));
					break;
			}
			
		}
		
		k++;
		
	}
	
}
VertexArray Julia::creeLaMatrice(int longueur, int hauteur, double echelle, Complexe origine){
	
	// Pré-calculs pour les coordonnées des points étudiés
	
	Complexe origineFenetre = Complexe(longueur,hauteur) * (echelle/2.0);
    origine = origine - origineFenetre;
	
    VertexArray matrice(Points,(longueur+1)*(hauteur+1));
	
	function<Complexe(Homogene)> convergenceDuPoint = [this](Homogene p){return convergenceDe(p);};
	
	int y;
    for (y = 0; y <= hauteur -1 ; y ++){ // on parcourt les lignes puis les colonnes
		
		// Deux threads pour profiter pleinement d'un processeur dual-core
		thread a(calculeLigne, y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, convergenceDuPoint, &matrice);
		y++;
		thread b(calculeLigne, y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, convergenceDuPoint, &matrice);
		a.join();
		b.join();

	}
	if (y != hauteur) { // s'il y a un nombre impair de lignes
		thread a(calculeLigne, y, longueur, hauteur, echelle, origine, borneDIteration, peindreEnBlanc, convergenceDuPoint, &matrice);
		a.join();
	}
	
    return matrice;
}

