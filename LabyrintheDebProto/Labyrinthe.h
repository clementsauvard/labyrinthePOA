#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Environnement.h"

class Labyrinthe : public Environnement {
private:
	char **_data;
	int **_dist;
	int ** _distToC;
	int	 heightl;
	int  widthl;

public:
	Labyrinthe (char*);
	void setHeight(int h){heightl=h;}
	void setWidth(int w){widthl=w;}
	void setData(int x, int y, int z){_data[x][y] = z;}
	int width () { return widthl;}	// retourne la largeur du labyrinthe.
	int height () { return heightl;}	// retourne la longueur du labyrinthe.
	int dist (int i, int j)
	{
		return _dist [i][j];
	}
	int distToC (int i, int j)
	{
		return _distToC [i][j];
	}
	char data (int i, int j)
	{
		return _data [i][j];
	}	// retourne la case (i, j).
};

#endif
