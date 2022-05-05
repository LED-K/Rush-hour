#include <iostream>
#include <vector>
#include "solver.h"


using namespace std;


int main(int argc, char* argv[]){
	std::vector<Vehicule> tab_vehicule;

	Terrain * init = new Terrain();
	tab_vehicule= init->create_tab_voiture(argv[1]);
	Terrain * t = new Terrain(tab_vehicule);
	t->afficheTerrain();
	clock_t t0 = clock();
	Solver s;
	s.Parcour_largeur(t);
	//s.Parcour_largeur_V2(t);
	
	cout<<"temps total : "<< double(clock() - t0)/CLOCKS_PER_SEC << " seconds" << endl;
	


	return 0;
}