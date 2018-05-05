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
}

void Gardien::update (void) {
	//cout << _l -> _nboxes << endl;
	//move(1,1);
	//cout << _l -> scale << endl;
	//cout << "lol" <<  reinterpret_cast<Labyrinthe*>(_l) -> dist(_x/_l -> scale,_y/_l -> scale) << endl;	

	int haut = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
	int gauche = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
	int droite = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale)+1,floor(_y/_l -> scale));
	int bas = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale),floor(_y/_l -> scale)+1);

	//cout << "haut : " << haut << " bas : " << bas << " droite : " << droite << " gauche : " << gauche << endl;
	//cout << "x : " << (_x/_l -> scale)<< " y : " << _y/_l -> scale << endl;
	if (haut == -1){
		haut = INT_MAX;
		cout << "haut "<< endl;
	}
	if (bas == -1){
		bas = INT_MAX;
		cout << "bas "<< endl;
	}
	if (droite == -1){
		droite = INT_MAX;
		cout << "droite "<< endl;
	}
	if (gauche == -1){
		gauche = INT_MAX;
		cout << "gquche "<< endl;
	}


	vector<pair<int,int> > tempDir;

	int temp = min(min(min(haut,gauche),droite),bas);
	
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
		move(tempDir[0].first,tempDir[0].second);
	}
}

bool Gardien::move (double dx, double dy) {
	reinterpret_cast<Labyrinthe*>(_l) -> setData (round(_x/_l -> scale),round(_y/_l -> scale),0);

	_x += dx;
	_y += dy;
	reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),4);
	}
	return true;
}

void Gardien::fire (int angle_vertical) {

}

bool Gardien::process_fireball (float dx, float dy) { 
	return false; 
}

void Gardien::isDead () {
	if (glife == 0) {
		cout << "t'es mort lel" << endl;
		rester_au_sol();
	}

}