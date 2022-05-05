#include <iostream>
#include <vector>
#include <string>

#include "vehicule.h"

Vehicule::Vehicule(unsigned int _ligne, unsigned int _colonne, unsigned int _taille, unsigned int _orientation){

	this->ligne = _ligne;
	this->colonne = _colonne;
	this->taille = _taille;
	this->orientation = _orientation;

}



bool operator == (const Vehicule &a, const Vehicule &b){
	return ((a.ligne == b. ligne) && (a.colonne == b.colonne) && (a.taille == b.taille) && (a.orientation == b. orientation));
}

