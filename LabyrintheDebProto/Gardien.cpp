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


using namespace std;

Gardien::Gardien (Labyrinthe* l,const char* modele) : Mover (100, 80, l, modele)
{
	glife=20;
	mort = false;
	attaque = true;
}
bool pute = true;
void Gardien::update (void) {
		
	int haut = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
	int gauche = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
	int droite = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale)+1,floor(_y/_l -> scale));
	int bas = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale),floor(_y/_l -> scale)+1);

if (!attaque){
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
}
else {
	if (haut == -1){
		haut = 0;
	}
	if (bas == -1){
		bas = 0;
	}
	if (droite == -1){
		droite = 0;
	}
	if (gauche == -1){
		gauche = 0;
	}
}

	vector<pair<int,int> > tempDir;
	int temp;
	if (!attaque){
		temp = min(min(min(haut,gauche),droite),bas);
	}
	else{
		temp = max(max(max(haut,gauche),droite),bas);
	}
	//cout << " temp : " << temp << endl;

	if (temp == haut && temp != 0){
		tempDir.push_back(make_pair(0,-1));
	}
	if (temp == bas && temp != 0){
		tempDir.push_back(make_pair(0,1));
	}
	if (temp == droite && temp != 0){
		tempDir.push_back(make_pair(1,0));
	}
	if (temp == gauche && temp != 0){
		tempDir.push_back(make_pair(-1,0));
	}
/*
	for (int i = 0; i < tempDir.size(); i++){
		cout << "x : " << tempDir[i].first << endl;
		cout << "y : " << tempDir[i].second << endl;
	}
	*/
	//cout << tempDir.size() << endl;
	/*
	if (tempDir.size() > 1){

		int v2 = rand() % tempDir.size();
		if (tempDir[v2].first == 1){
			_angle = 270;
		}
		if (tempDir[v2].first == -1){
			_angle = 90;
		}
		if (tempDir[v2].second == 1){
			_angle = 0;
		}
		if (tempDir[v2].second == -1){
			_angle = 180;
		}
		move(tempDir[v2].first,tempDir[v2].second);
		
	}*/
	if (tempDir.size() >= 1){
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
		
		if (!mort){
			move(tempDir[0].first,tempDir[0].second);	
		}
		else {
			reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0);
		}
	}


	if (pute){
		fire(0);
		pute = false;
	}
		
}

bool Gardien::move (double dx, double dy) {
	 if( (int) reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale)+dx,ceil(_y/_l -> scale)+dy) != 4  ) 
  	{   
		reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0); 

		//cout << (int) reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale)+dx,ceil(_y/_l -> scale)+dy) << endl;

		_x += dx;
		_y += dy;
		reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),4);
}
	return true;
}


bool Gardien::process_fireball (float dx, float dy) { 
	float   x = (_x - _fb -> get_x ()) / Environnement::scale;
    float   y = (_y - _fb -> get_y ()) / Environnement::scale;
    float   dist2 = x*x + y*y;
    float   dmax2;

    switch ( _l -> data ((int)((_fb -> get_x () + dx) / Environnement::scale),(int)((_fb -> get_y () + dy) / Environnement::scale)) )  
    {
        case EMPTY: 
            message("LE VIDE");
            return true;  
            break;  
        case 1:
        	cout << _x << endl;
        	cout << _fb -> get_x () << endl;
            message("UN MUR");  
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());  
            return false;
            break;
        case 2:
            message("UNE CAISSE");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
        case 3:  
            message("UN TRESOR");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
        case 5:  
            message("UN Gardien");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
         default:  
            message("wtfdidujustdidulilshit");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
    }
}
void Gardien::fire (int angle_vertical) {
	int p1 = ( ((rand() % 10) - 5)*((20-glife))/20 );
    int p2 = ( ((rand() % 10) - 5)*((20-glife))/20 );

	auto posxC = (_l -> _guards[0] -> _x)/ Environnement::scale;
	auto posyC = (_l -> _guards[0] -> _y)/ Environnement::scale;

	cout << posxC << endl;
	cout << _x/Environnement::scale << endl;

	auto angleTir = ceil(atan2(( posxC-_x/Environnement::scale ),(posyC-_y/Environnement::scale ) ) * 180 / M_PI);

	cout << angleTir << "fdp"<< endl;
    _fb -> init (/* position initiale de la boule */ _x, _y, 10.,
                /* angles de visée */ 0, angleTir);
}

void Gardien::isDead () {
	cout << glife << endl;
	if (glife <= 0) {
		cout << "t'es mort lel" << endl;
		mort = true;
		rester_au_sol();
	}

}