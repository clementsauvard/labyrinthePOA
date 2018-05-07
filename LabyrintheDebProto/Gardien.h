#ifndef GARDIEN_H
#define GARDIEN_H

#include <stdio.h>
#include "Mover.h"
#include "Sound.h"

class Labyrinthe;

class Gardien : public Mover {
private:
	int ** _distToC;

public:
	Gardien (Labyrinthe* l, const char* modele);

	int glife; // Vie du gardien
	bool mort; // Gardien mort ou en vie
	bool attaque; // true = mode attaque , false = mode défense
	//int rangeUp;
	//int rangeDown;
	bool alloc;
	bool touche;
	int waitLife;

	// mon gardien pense trï¿½s mal!
	void update (void);
	// et ne bouge pas!
	bool move (double dx, double dy);
	// ne sait pas tirer sur un ennemi.
	void fire (int angle_vertical);
	// quand a faire bouger la boule de feu...
	bool process_fireball (float dx, float dy);
	// Le gardien est il mort ?
	void isDead();
	//retourne la case du tableau _distoc[i][j] -> tableau dikjstra
	int distToC (int i, int j)
	{
		return _distToC [i][j];
	}
};

#endif
