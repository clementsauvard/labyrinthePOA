#include "Chasseur.h"
#include "Gardien.h"
#include "Labyrinthe.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

Gardien::Gardien (Labyrinthe* l,const char* modele) : Mover (100, 80, l, modele)
{
	
}

void Gardien::update (void) {
	//cout << _l -> _nboxes << endl;
	//move(1,1);
	//cout << _l -> scale << endl;
	//cout << "lol" <<  reinterpret_cast<Labyrinthe*>(_l) -> dist(_x/_l -> scale,_y/_l -> scale) << endl;


	int haut = reinterpret_cast<Labyrinthe*>(_l) -> dist((_x/_l -> scale),(_y/_l -> scale)-1);
	int gauche = reinterpret_cast<Labyrinthe*>(_l) -> dist((_x/_l -> scale)-1,(_y/_l -> scale));
	int droite = reinterpret_cast<Labyrinthe*>(_l) -> dist((_x/_l -> scale)+1,(_y/_l -> scale));
	int bas = reinterpret_cast<Labyrinthe*>(_l) -> dist((_x/_l -> scale),(_y/_l -> scale)+1);

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

	vector<pair<double,double>> tempDir;

	int temp = min(min(min(haut,gauche),droite),bas);
	
	if (temp == haut && temp != 0){
		tempDir.push_back(make_pair(0,-1));
	}
	if (temp == bas && temp != 0){
		tempDir.push_back(make_pair(0,+1));
	}
	if (temp == droite && temp != 0){
		tempDir.push_back(make_pair(+1,0));
	}
	if (temp == gauche && temp != 0){
		tempDir.push_back(make_pair(-1,0));
	}

	for (int i = 0; i < tempDir.size(); i++){
		cout << "x : " << tempDir[i].first << " y : " << tempDir[i].second << endl;
	}
	
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
		reinterpret_cast<Labyrinthe*>(_l) -> setData ((_x/_l -> scale),(_y/_l -> scale),4);
	}
	
}

bool Gardien::move (double dx, double dy) {
	reinterpret_cast<Labyrinthe*>(_l) -> setData ((_x/_l -> scale),(_y/_l -> scale),0);
	_x += dx;
	_y += dy;
	return true;
}

void Gardien::fire (int angle_vertical) {

}

bool Gardien::process_fireball (float dx, float dy) { 
	return false; 
}