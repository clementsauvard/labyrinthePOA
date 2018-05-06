#ifndef GARDIEN_H
#define GARDIEN_H

#include <stdio.h>
#include "Mover.h"
#include "Sound.h"

class Labyrinthe;

class Gardien : public Mover {
public:
	Gardien (Labyrinthe* l, const char* modele);

	int glife;
	bool mort;
	bool attaque;

	int setGlife (){ glife = glife - 5; return glife;}
	// mon gardien pense très mal!
	void update (void);
	// et ne bouge pas!
	bool move (double dx, double dy);
	// ne sait pas tirer sur un ennemi.
	void fire (int angle_vertical);
	// quand a faire bouger la boule de feu...
	bool process_fireball (float dx, float dy);

	void isDead();
};

#endif
