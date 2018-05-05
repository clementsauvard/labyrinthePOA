#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Environnement.h"

class Labyrinthe : public Environnement {
private:
	char **_data;
	int	 heightl;
	int  widthl;

public:
	Labyrinthe (char*);
	void setHeight(int h){heightl=h;}
	void setWidth(int w){widthl=w;}
	int width () { return widthl;}	// retourne la largeur du labyrinthe.
	int height () { return heightl;}	// retourne la longueur du labyrinthe.
	char data (int i, int j)
	{
		return _data [i][j];
	}	// retourne la case (i, j).
};

#endif
