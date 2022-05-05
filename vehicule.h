#include <iostream>
#include <string>

using namespace std;

class Vehicule{
public:

	int ligne, colonne, taille, orientation;


public:
	//Constructeur du véhicule
	Vehicule(unsigned int ligne, unsigned int colonne, unsigned int taille, unsigned int orientation);


	//Fonction d'affichage du véhicule
	void afficheVehicule();


	//Surcharge de l'opérateur de comparaison d'égalité pour les Véhicules
	friend bool operator == (const Vehicule & v1, const Vehicule & v2);

};