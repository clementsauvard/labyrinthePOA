#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Environnement.h"

class Labyrinthe : public Environnement {
private:
	char **_data; // Tableau pour les collisions
	int **_dist; // Dikjstra plus court chemin vers le trésor
	int	 heightl; // Hauteur laby
	int  widthl; // Width laby

public:
	Labyrinthe (char*);
	void setHeight(int h){heightl=h;} // définit la hauteur du labyrinthe
	void setWidth(int w){widthl=w;} // définit la largeur du labyrinthe
	void setData(int x, int y, int z){_data[x][y] = z;}
	int width () { return widthl;}	// retourne la largeur du labyrinthe.
	int height () { return heightl;}	// retourne la longueur du labyrinthe.
	int dist (int i, int j)
	{
		return _dist [i][j];
	}
	
	char data (int i, int j)
	{
		return _data [i][j];
	}	// retourne la case (i, j).
};

#endif
