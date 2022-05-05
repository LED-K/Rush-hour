#include "solver.h"
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <algorithm>



Solver::Solver(){}


  static  bool compareTerrain(const Terrain t1 , const Terrain t2){
	int distance_t1=TAILLE_TERRAIN-(t1.voiture[0].colonne+t1.voiture[0].taille);
	int distance_t2=TAILLE_TERRAIN-(t2.voiture[0].colonne+t2.voiture[0].taille);
		if(distance_t1<distance_t2){
			return false; //la voiture joueur est plus proche de la sortie dans le terrain t1
		} else {
			return true; //la voiture joueur est plus proche de la sortie dans le terrain t1
		}
	}



void Solver::Parcour_largeur(Terrain * terrain){
	Terrain premier_terrain(terrain->voiture);	//// on recup une copie du terrain
    vector <Terrain> premier_chemin;			//// premier element de la file  de chemins decouverts

    vector <Terrain> chemins_decouvert; //chemin decouvert /, l'ideal serait de le remplacer par un set ou un map pour reduire la complexite
    vector <vector <Terrain> > solutions;

    vector <Terrain> coups;
    queue <Terrain> file_terrain;			//// File de de situations de jeu
    file_terrain.push(premier_terrain);

    queue <vector <Terrain> > file_chemins;	//// File des chemins decouverts
    vector <Terrain> nouveau_chemin; // la ou on va stocker les nouveaux chemins decouverts

    while (file_terrain.size() != 0)
    {
        premier_terrain = file_terrain.front();


        file_terrain.pop();
        if (file_chemins.size() != 0)
        {
            premier_chemin = file_chemins.front();
            file_chemins.pop();
        }
        premier_chemin.push_back(premier_terrain);
        nouveau_chemin = premier_chemin;

        //// If board is chemins_decouvert, continue
        if (find(chemins_decouvert.begin(), chemins_decouvert.end(), premier_terrain) != chemins_decouvert.end()){
        	//chemins_decouvert[sizet-1].afficheTerrain();
        	//cout << " i'm here" << endl;
            continue;
         }
        else{
        	//cout << "i'am never here " << endl;
            chemins_decouvert.push_back(premier_terrain);
        }

        //// If board is solved
        if (premier_terrain.estResolu())
            solutions.push_back(nouveau_chemin);
        else
        {
            coups = premier_terrain.getActions();
            for (int i=0; i<coups.size(); i++)
            {

                file_terrain.push(coups[i]);

                file_chemins.push(nouveau_chemin);

            }
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Etat final" << endl;
    nouveau_chemin[nouveau_chemin.size()-1].afficheTerrain();
    //// solution optimale dans solution_optimale
    vector <Terrain> solution_optimale;
    if (solutions.size() != 0)
    {
        solution_optimale = solutions[0];
        for (int i=1; i<solutions.size(); i++)
        {
            if (solutions[i].size() < solution_optimale.size())
                solution_optimale = solutions[i];
        }
    }
    cout << "TOTAL SOLUTIONS:" << solutions.size() << endl;
    cout << "SOLUTION OPTIMALE:" << solution_optimale.size() - 1 << endl;
    cout << "NOMBRES DE NOEUDS TOTAL" << chemins_decouvert.size() << endl;

}

void Solver::Parcour_largeur_V2(Terrain * terrain){
	Terrain premier_terrain(terrain->voiture);	//// on recup une copie du terrain
    vector <Terrain> premier_chemin;			//// premier element de la file  de chemins decouverts

    vector <Terrain> chemins_decouvert;  //chemin decouvert /, l'ideal serait de le remplacer par un set ou un map pour reduire la complexite
    vector <vector <Terrain> > solutions;

    vector <Terrain> coups;	//// situations de jeu decouvert a chaque profondeur

    queue <Terrain> file_terrain;			//// File de de situations de jeu
    file_terrain.push(premier_terrain);

    queue <vector <Terrain> > file_chemins;	//// File des chemins decouverts
    vector <Terrain> nouveau_chemin; // la ou on va stocker les nouveaux chemins decouverts
    Terrain premier_terrain2; 

    while (file_terrain.size() != 0)
    {
        premier_terrain = file_terrain.front();


        file_terrain.pop();
        if (file_chemins.size() != 0)
        {
            premier_chemin = file_chemins.front();
            file_chemins.pop();
        }
        premier_chemin.push_back(premier_terrain);
        nouveau_chemin = premier_chemin;

        //// si terrain dans chemins_decouvert, on continue
        int sizet = chemins_decouvert.size()-1;
        if(sizet>=1)
        premier_terrain2=chemins_decouvert[sizet];
        if (find(chemins_decouvert.begin(), chemins_decouvert.end(), premier_terrain)  != chemins_decouvert.end() && compareTerrain(premier_terrain,premier_terrain2)){
        	//chemins_decouvert[sizet-1].afficheTerrain();
        	//cout << " i'm here" << endl;
            continue;
         }
        else{//sinon on le rajoute dans la file des chemins decouverts
        	//cout << "i'am never here " << endl;
            chemins_decouvert.push_back(premier_terrain);
        }

        //// If board is solved
        if (premier_terrain.estResolu())
            solutions.push_back(nouveau_chemin);
        else
        {
            coups = premier_terrain.getActions();
            for (int i=0; i<coups.size(); i++)
            {

                file_terrain.push(coups[i]);

                file_chemins.push(nouveau_chemin);

            }
        }
    }


    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Etat final" << endl;
    nouveau_chemin[nouveau_chemin.size()-1].afficheTerrain();


    //// solution optimale dans solution_optimale
    vector <Terrain> solution_optimale;
    if (solutions.size() != 0)
    {
        solution_optimale = solutions[0];
        for (int i=1; i<solutions.size(); i++)
        {
            if (solutions[i].size() < solution_optimale.size())
                solution_optimale = solutions[i];
        }
    }
    cout << "TOTAL SOLUTIONS:" << solutions.size() << endl;
    cout << "SOLUTION OPTIMALE:" << solution_optimale.size() - 1 << endl;
    cout << "NOMBRES DE NOEUDS TOTAL" << chemins_decouvert.size() << endl;
}
