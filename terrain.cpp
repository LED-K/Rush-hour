#include <iostream>
#include "terrain.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>

//constructeur vide pour test
Terrain::Terrain(){
	compteurVehicule = voiture.size();

}

Terrain::Terrain(vector <Vehicule> vv){
	//vv est un vecteur de véhicule
	voiture = vv; 
	compteurVehicule = voiture.size();
}

static int  get_int_length(int prout){ // fonction pour renvoyer la longueur d'un int (j'ai eu des soucis avec to_string --')
	unsigned int number_of_digits = 0;
	do {
     	++number_of_digits; 
     	prout /= 10;
	} while (prout);
	return number_of_digits;
}

vector<Vehicule> Terrain::create_tab_voiture(string file){
	// recup le contenu du fichier et le stock dans un tableau de string temporaire
	std::vector<string> tmp;
	string line;
	ifstream infile(file.c_str());
   	while (std::getline(infile, line)) {
			std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' '); //supprimer les espaces dans les lignes du fichiers
			line.erase(end_pos, line.end());
    		tmp.push_back(line);
    		//cout << line << endl;
	}
	unsigned int res;
	unsigned int posx;
	unsigned int posy;
	unsigned int size;
	unsigned int hori_vert; //vector de string temporaire pour recup le terrain
	for(int i=1;i<tmp.size();i++){ // on part de la 1ere ligne car elle correspond a la position de la sortie
			//cout << "veritable ligne en cour de lecture " << tmp[i] << endl;
		    istringstream iss (tmp[i]);// conversion de la ligne en int
		    iss >> res; //cout << "ligne en cour de lecture apres conversion " << res << endl;
		    int  longueur_int = get_int_length(res); // on recupere la longueur du int 
		  //  cout << "longueur int " << longueur_int << endl;
		    if(longueur_int == 3){
		    	posx=0; //cout << "voiture "<< i << "posx " << posx << endl;
		    	hori_vert=res%10; 
		 		res=res/10;
			 	size=res%10; //cout << "voiture "<< i << "size " << size << endl;
			 	res=res/10;
			 	posy=res%10; ///cout << "voiture "<< i << "posy " << posy << endl;
		    }else if(longueur_int == 2){
		    	posx=0;//cout << "voiture "<< i << "posx " << posx << endl;
		    	posy=0; ///cout << "voiture "<< i << "posy " << posy << endl;
			 	hori_vert=res%10;
			 	res=res/10;
			 	size=res%10;
		    }else{
		 	hori_vert=res%10;  // serie d'operations pour parser le int est initialiser les attributs de la voiture qu'on manipule
		 	res=res/10; 
		 	size=res%10; //cout << "voiture "<< i << "size " << size << endl;
		 	res=res/10;
		 	posy=res%10;//cout << "voiture "<< i << "posy " << posy << endl;
		 	res=res/10;
		 	posx=res%10; //cout << "voiture " << i <<   "posx " <<posx << endl;
		 	
		 }
		 //cout << "je vais inserer : orientation " << hori_vert  << "et size  " << size << endl;
		 this->voiture.push_back(Vehicule(posx,posy,size,hori_vert));
		 //cout << "voiture "<< i << "posx " <<  voiture[i-1].taille << endl; // pour tester si voiture a bien ete remplit
		 
	 }
	return voiture; // on renvoie le tableau de voiture
}

vector <vector <string> > Terrain::getTerrain(){


	//initialisation du terrain
	vector <vector <string> > terrain(TAILLE_TERRAIN);
	for (int i(0); i < TAILLE_TERRAIN; i++){
		for (int j(0); j < TAILLE_TERRAIN; j++){
			terrain[i].push_back(" _ ");
		}
	}

	//Place la voiture joueur
	for (int i = 0; i < compteurVehicule; i++)
    {
        if(i == 0)
        {


            for(int j = 0; j < voiture[i].taille; j++)

                terrain[voiture[i].ligne][voiture[i].colonne + j] = " X ";

        }
        else
        {


            if(voiture[i].orientation == 1)
            {

                for(int j = 0; j < voiture[i].taille; j++){
                	if(i<10){
                		terrain[voiture[i].ligne][voiture[i].colonne + j] =" " + to_string(i) +  " ";
            		}else{ 
            			terrain[voiture[i].ligne][voiture[i].colonne + j] = " " + to_string(i) ;

            		}   
            	}
            }else{
            
                for(int j = 0; j < voiture[i].taille; j++){
                	if(i<10)
                    terrain[voiture[i].ligne + j][voiture[i].colonne] = " " + to_string(i) +  " " ;
                	else
                	terrain[voiture[i].ligne + j][voiture[i].colonne] = " " + to_string(i);
                }

            }


        }


    }

	return terrain; 
}

void Terrain::afficheTerrain(){
	//cout << " je veux afficher le terrain" << endl;
	vector <vector <string> > terrain = getTerrain();
	for (int i(0); i < TAILLE_TERRAIN; i++){
		for (int j(0); j < TAILLE_TERRAIN; j++){
			cout << terrain[i][j];
		}
		cout << endl;
	}
}

bool Terrain::estResolu(){
	return (voiture[0].colonne + voiture[0].taille == TAILLE_TERRAIN);
}

vector <Terrain> Terrain::getActions(){

	vector <Terrain> actions;
	vector <vector <string> > terrain = getTerrain();
	vector <Vehicule> copieVoiture;
	for (int i(0); i < compteurVehicule; i++){
		int l = voiture[i].ligne;
		int c = voiture[i].colonne;
		int t = voiture[i].taille;
		int o = voiture[i].orientation;
		if ( o == 1){
			//bouger à gauche
			for(int j =1;j<2;j++){//on essaye pour 2 cases
				if((c -j >= 0) && terrain[l][c-j] == " _ "){
				Vehicule newVehicule(l, c -j, t, o);
				copieVoiture = voiture; 
				copieVoiture[i] = newVehicule;
				actions.push_back(Terrain(copieVoiture));
			}

		}
			
			//Bouger à droite
			for(int j=1;j<2;j++){
				if ((c + t + (j-1) <= 5) && (terrain[l][c + t+(j-1)] == " _ ")){
					Vehicule newVehicule(l, c + j, t, o);
					copieVoiture = voiture; 
					copieVoiture[i] = newVehicule; 
					actions.push_back(Terrain(copieVoiture));
				}
			}
			
		}
		else{
			//Bouger en haut
			for(int j=1;j<2;j++){
				if ((l - j >= 0) && (terrain[l - j][c] == " _ ")){
					Vehicule newVehicule(l - j, c, t, o);
					copieVoiture = voiture; 
					copieVoiture[i] = newVehicule; 
					actions.push_back(Terrain(copieVoiture));
				}
			}
			for(int j=1;j<2;j++){
				if ((l +t + (j-1) <= 5) && (terrain[l+t+(j-1)][c] == " _ ")){
					Vehicule newVehicule(l + j, c, t, o);
					copieVoiture = voiture; 
					copieVoiture[i] = newVehicule; 
					actions.push_back(Terrain(copieVoiture));
				}
			}
			
		}
	}
	return actions; 
}
//operateur == ca servira pour plus tard -> map/set
bool operator == (const Terrain & t1, const Terrain &t2){
	return t1.voiture == t2.voiture;
}


bool operator < (const Terrain t1 , const Terrain t2){
	int distance_t1=TAILLE_TERRAIN-(t1.voiture[0].colonne+t1.voiture[0].taille);
	int distance_t2=TAILLE_TERRAIN-(t2.voiture[0].colonne+t2.voiture[0].taille);
		if(distance_t1<distance_t2){
			return false; //la voiture joueur est plus proche de la sortie dans le terrain t1
		} else {
			return true; //la voiture joueur est plus proche de la sortie dans le terrain t1
		}
}



