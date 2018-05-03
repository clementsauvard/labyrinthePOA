#include "Chasseur.h"
#include "Gardien.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Gardien::Gardien (Labyrinthe* l,const char* modele) : Mover (100, 80, l, modele)
{
	
}

void Gardien::update (void) {
	//cout << _l -> _nboxes << endl;
	//move(1,1);
}

bool Gardien::move (double dx, double dy) { 
	_x += dx;
	_y += dy;
	return true;
}

void Gardien::fire (int angle_vertical) {

}

bool Gardien::process_fireball (float dx, float dy) { 
	return false; 
}