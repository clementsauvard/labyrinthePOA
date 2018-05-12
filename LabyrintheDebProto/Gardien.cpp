#include "Chasseur.h"
#include "Gardien.h"
#include "Labyrinthe.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stack>

using namespace std;

Gardien::Gardien (Labyrinthe* l,const char* modele) : Mover (100, 80, l, modele)
{
	glife=5;
	mort = false;
	alloc=false;
	attaque = false;
	touche = false;
	waitLife = 300 * _l -> _nguards;
	tir = false;
}
void Gardien::update (void) {
		
	int haut;
	int gauche;
	int droite;
	int bas;

	// Trouve la plus grande valeur (distance) dans le tableau de dikjstra dist
	int tempRange = 0;
	for (int i = 0; i < _l -> width(); i++){
		for (int j = 0; j < _l -> height(); j++){
			if (reinterpret_cast<Labyrinthe*>(_l) -> dist(i,j) > tempRange){
				tempRange = reinterpret_cast<Labyrinthe*>(_l) -> dist(i,j);
			}
		}
	}

	// Si le gardien est près du trésor, il passe en mode attaque
	if (reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) < 15){

		attaque = true;

		// Voici comment nous avons implémenté le mode attaque : on crée un nouveau tableau résultant de notre algorithme de dikjstra
		// et fabrique un chemin plus court non pas vers le trésor mais vers un point aléatoire du labyrinthe, le gardien va donc 
		// si diriger et une fois qu'il dépassera un certain seuil, une certaine distance il revient en mode défense et se rapproche du trésor

		//Définition du tableau
		_distToC = (int**)malloc(sizeof(int*) * (_l -> width()));
		for (int i = 0; i < _l -> width(); i++)
		_distToC[i] = (int*)malloc(sizeof(int) * (_l -> height()));
		alloc=true;
		for(int j = 0; j < _l -> width(); j++)
		{
		    for (int i = 0; i < _l -> height(); i++){
		        _distToC[j][i]=-1;
		    }
		}
		bool done=false;
        bool fini=false;
		int cpt=0;
        int x1;
        int y1;
		stack< pair <int,int> > i2;
		//On choisit un point random de la map, tant que ce n'est pas un mur
		while(!fini){
            x1 = rand() % _l -> width();
            y1 = rand() % _l -> height();
            if (reinterpret_cast<Labyrinthe*>(_l) -> dist(x1,y1) > 0){
                fini = true;
            }
        }
        //dikjstra
		i2.push(make_pair (x1,y1));
		pair <int,int> x2;
		while(!done)
		{
		    x2=i2.top();
		    cpt=INT_MAX;
		    if(x2.second + 1 <= _l -> height() && _distToC[x2.first][x2.second+1] >-1 )
		      {cpt= min(cpt,_distToC[x2.first][x2.second+1]+1);}
		    if(x2.second - 1 <= _l -> height() && _distToC[x2.first][x2.second-1] >-1 )
		      {cpt= min(cpt,_distToC[x2.first][x2.second-1]+1);}
		    if(x2.first + 1 <= _l -> width() && _distToC[x2.first+1][x2.second] >-1 )
		      {cpt= min(cpt,_distToC[x2.first+1][x2.second]+1);}
		    if(x2.first - 1 <= _l -> width() && _distToC[x2.first-1][x2.second] >-1 )
		      {cpt= min(cpt,_distToC[x2.first-1][x2.second]+1);}
		    
		    if (cpt==INT_MAX)
		      {cpt=0;}
		    i2.pop();
		    
		    _distToC[x2.first][x2.second]=cpt;
		    
		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second+1) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second+1) >= 4 ) {
		        if(_distToC[x2.first][x2.second+1] == -1 || cpt+1 < _distToC[x2.first][x2.second+1]  )
		        {
		            if(x2.second+1 <= _l -> height())
		            {
		                i2.push(make_pair (x2.first,x2.second+1));
		            }
		        }
		    }

		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first+1,x2.second) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first+1,x2.second) >= 4 ) 
		    {
		        if(_distToC[x2.first+1][x2.second] == -1 || cpt+1 < _distToC[x2.first+1][x2.second]  )
		        {
		            if(x2.first+1 <= _l -> width())
		            {
		                i2.push(make_pair (x2.first+1,x2.second));
		            }
		        }
		    }


		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first-1,x2.second) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first-1,x2.second) >= 4 ) 
		    {
		        if(_distToC[x2.first-1][x2.second] == -1 || cpt+1 < _distToC[x2.first-1][x2.second]  )
		        {
		            if(x2.first-1 >= 0)
		            {
		               i2.push(make_pair (x2.first-1,x2.second));
		            }
		        }
		    }
		    
		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second-1) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second-1) >= 4 ) {
		        if(_distToC[x2.first][x2.second-1] == -1 || cpt+1 < _distToC[x2.first][x2.second-1]  )
		        { 
		            if(x2.second-1 >= 0)
		            {
		              i2.push(make_pair (x2.first,x2.second-1));
		            }
		        }
		    }

		   
		    
		    
		    cpt++;
		    if(i2.empty()){
		        done=true;
		    }
		    
		}
		//fin dikjstra
	}
	// Si le gardien dépasse un certain seuil, ou qu'il s'est suffisament rapprocher du point qu'il lui a été indiqué en mode attaque
	// Il revient en mode défense et se rapproche du trésor
	else if (reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) > (tempRange - 40) || (alloc && distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) < 2))
	{
		attaque = false;
	}


	// si le gardien est en mode défense, il regarde les cellules à sa gauche droite haut bas
	// par rapport au tableau du plus court chemin ers le trésor
	if (!attaque){
		haut = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
		gauche = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
		droite = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale)+1,floor(_y/_l -> scale));
		bas = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale),floor(_y/_l -> scale)+1);
	}
	//sinon il regarde les cellules du plus court chemin vers le point désigné par le mode attaque
	else {
		haut = distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
		gauche = distToC(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
		droite = distToC(ceil(_x/_l -> scale)+1,ceil(_y/_l -> scale));
		bas = distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)+1);
	}

	//Si la cellule est un mur, accès impossible 
	if (haut == -1){
		haut = INT_MAX;
	}
	if (bas == -1){
		bas = INT_MAX;
	}
	if (droite == -1){
		droite = INT_MAX;
	}
	if (gauche == -1){
		gauche = INT_MAX;
	}

	vector<pair<int,int> > tempDir;
	
	// On récupère la plus petite valeur des celulles
	int temp = min(min(min(haut,gauche),droite),bas);
	
	// Si plusieurs céllules possédent cette valeur minimal, on met dans le tableau tempDir les directions possibles
	if (temp == haut && temp != 0 ){
		tempDir.push_back(make_pair(0,-1));
	}
	if (temp == bas && temp != 0 ){
		tempDir.push_back(make_pair(0,1));
	}
	if (temp == droite && temp != 0 ){
		tempDir.push_back(make_pair(1,0));
	}
	if (temp == gauche && temp != 0 ){
		tempDir.push_back(make_pair(-1,0));
	}

	// Si il y a une ou plusieurs direction possible, on va toujours dans la direction
	// contenu dans la première case du tableau, nous avons procédé comme cela au lieu de faire de l'aléatoire
	// car nous avons remarqué que mettre de l'aléatoire dans ce cas provoquait des comportements bizarres
	if (tempDir.size() >= 1){
		//Si le gardien n'est pas mort, on modifie l'angle de son modèle et on le déplace dans la direction indiqué
		if (!mort){
			if (tempDir[0].first == 1){
				_angle = 270;
			}
			if (tempDir[0].first == -1){
				_angle = 90;
			}
			if (tempDir[0].second == 1){
				_angle = 0;
			}
			if (tempDir[0].second == -1){
				_angle = 180;
			}
			move(tempDir[0].first,tempDir[0].second);	
		}
		// SI le gardien est mort on l'enlève du tableau des collisions, pour plus qu'il ne dérange
		else {
			reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0);
		}
	}

	
	bool wallMet = false;
	int xChasseur = ((int)_l -> _guards[0] -> _x/Environnement::scale);
	int yChasseur = ((int)_l -> _guards[0] -> _y/Environnement::scale);
	int xGarde = ceil( _x/Environnement::scale );
	int yGarde = ceil( _y/Environnement::scale );

	// Algorithme qui détecte si un gardien "voit" un chasseur
	// si le gardien est sur une même ligne ou colonne que le chasseur et qu'aucun mur ne les sépare
	// le gardien tire sur le chasseur
	if ( (xChasseur - xGarde) == 0){
		if ((yChasseur - yGarde) > 0){
			for (int i = 0; i < (yChasseur - yGarde) ; i++){
				if ( reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde,yGarde+i) == 1 ){
					wallMet = true;
				}
			}
		}
		else {
			for (int i = 0; i > (yChasseur - yGarde); i--){
				if (reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde,yGarde+i) == 1){
					wallMet = true;
				}
			}
		}
	}
	else
	{	
		if ( (yChasseur - yGarde) == 0){
			if ((xChasseur - xGarde) > 0){
				for (int i = 0; i < (xChasseur - xGarde) ; i++){
					if ( reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde+i,yGarde) == 1 ){
						wallMet = true;
					}
				}
			}
			else {
				for (int i = 0; i > (xChasseur - xGarde); i--){
					if (reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde+i,yGarde) == 1 ){
						wallMet = true;
					}
				}
			}
		}
		else
		{
			wallMet=true;
		}
	}

	// Si le gardien peut tirer sur le chasseur et qu'il n'est pas mort, il tire
	if (!wallMet && !mort && !tir){
		fire(0);
		tir = true;
	}
	
	// Processus de régénération de vie pour les gardiens
	// Si ils ont moins de vie que leur maximum de vie et qu'ils n'ont pas été récemment touché
	// ils gagneront un point de vie au bout de quelques secondes
	if (!mort){
		if (!touche){
			if (glife < 5){
				glife++;
				touche = true;
				waitLife = 300;
			}
		}
		else {
			waitLife--;
			if (waitLife == 0){
				touche = false;
			}
		}
	}

	// Processus de régénération de vie pour le Chasseur
	// Si il a moins de vie que son maximum de vie et qu'il n'a pas été récemment touché
	// il gagnera un point de vie au bout de quelques secondes
	if (reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life > 0){
		if (reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> toucheC == false){
			if (reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life < 10){
				reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life++;
				reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> toucheC = true;
				reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> waitLifeC = 300 * _l -> _nguards;
			}
		}
		else {
			reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> waitLifeC--;
			if (reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> waitLifeC == 0){
				reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> toucheC = false;
			}
		}
	}
	// Si le chasseur meurt GAME OVER
	else if (reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life <= 0){
		partie_terminee(false);
	}


}

bool Gardien::move (double dx, double dy) {
	
	//La case actuel du gardien n'est plus dans le tableau des collisions	
	if(reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale),ceil(_y/_l -> scale)) == 4 )
	{
		reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0); 
	}

	_x += dx;
	_y += dy;

	//la nouvelle position du gardien est mise dans le tableau des collisions
	if(reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale),ceil(_y/_l -> scale)) == 0 )
	{
		reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),4);
	}

	return true;
}


bool Gardien::process_fireball (float dx, float dy) { 

    switch ( _l -> data ((int)((_fb -> get_x () + dx) / Environnement::scale),(int)((_fb -> get_y () + dy) / Environnement::scale)) )  
    {
        case EMPTY: 
            return true;  
            break;  
        case 1:
        	tir = false;
            return false;
            break;
        case 2:
            message("UNE CAISSE");
            tir = false;
            return false;
            break;
        case 3:  
            message("UN TRESOR");
            tir = false;
            return false;
            break;
        case 4:  
            message("");
            return true;
            break;    
        case 5:
        	message("LE CHASSEUR");
        	tir = false;
        	// Le chasseur a été touché, on reset le timer de récupération de vie
        	reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life = reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life - 1;
        	cout << "Chasseur toucher ! Vie du Chasseur : " << reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> life << endl;
        	reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> toucheC = true;
            reinterpret_cast<Chasseur*> (_l -> _guards[0]) -> waitLifeC = 300 * _l -> _nguards;
            return false;
            break;
         default:
         	tir = false;
            return false;
    }
}
void Gardien::fire (int angle_vertical) {
	// Calcul permettant de définir la précision du tir selon la vie du gardien
	int p1 = ( ((rand() % 10) - 5)*((5-glife))/5 );
    //int p2 = ( ((rand() % 10) - 5)*((5-glife))/5 );

	auto posxC = (_l -> _guards[0] -> _x)/ Environnement::scale;
	auto posyC = (_l -> _guards[0] -> _y)/ Environnement::scale;

	auto angleTir = ceil(atan2(( posxC-_x/Environnement::scale ),(posyC-_y/Environnement::scale ) ) * 180 / M_PI);

    _fb -> init (/* position initiale de la boule */ _x, _y, 10.,
                /* angles de visée */ 0, angleTir+p1);
}

void Gardien::isDead () {
	// Si le gardien est mort on le laisse au sol
	if (glife <= 0) {
		mort = true;
		rester_au_sol();
	}

}