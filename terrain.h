
#include <vector>
#include "vehicule.h"
#define TAILLE_TERRAIN 6


class Terrain{
public:
	std::vector <Vehicule> voiture; 
	int compteurVehicule;

public:
	Terrain();
	Terrain(vector <Vehicule>);
	std::vector <Vehicule> create_tab_voiture(string file);
	std::vector <vector <string> > getTerrain();
	void afficheTerrain();
	bool estResolu();
	vector <Terrain> getAction();
	vector <Terrain> getActions();
	friend bool operator == (const Terrain & t1, const Terrain &t2);
};
