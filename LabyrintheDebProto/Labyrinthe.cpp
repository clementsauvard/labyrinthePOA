#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

Sound*	Chasseur::_hunter_fire;	// bruit de l'arme du chasseur.
Sound*	Chasseur::_hunter_hit;	// cri du chasseur touché.
Sound*	Chasseur::_wall_hit;	// on a tapé un mur. 

Environnement* Environnement::init (char* filename)
{
	return new Labyrinthe (filename);
}


Labyrinthe::Labyrinthe (char* filename)
{
	//vector< vector<char> > vec;
	//std::ifstream fichier(filename);
	//std::vector<char> laby(
    //std::istream_iterator<char>(fichier),
    //std::istream_iterator<char>{});

  //Variables
  string line;
  int widthLab = 0;
  int heightLab = 0;
  bool firstLigne = false;
  bool boolCompteur = false;
  bool boolCompteur2 = false;
  int startCompteur = 0;
  int startCompteur2 = 0;
  int startLaby = 0;
  int lel = 0;

  int x2Mur;
  int y2Mur;
  bool waitFinMur = false;

  static Wall walls[100]; //murs
  static Box caisses[20]; //caisses
  static Wall affiches[20];

  _guards = new Mover* [100];

  char labyrinthe2D[100][100];

  int nbWalls = 0;
  int nbAffiches = 0;
  int nbCaisses = 0;
  int nbGuards = 0;

  // Ouverture du fichier
  ifstream myfile ("labyrinthe.txt");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      heightLab++;

      // Recuperation de la largeur du labyrinthe
      if (line.length() > widthLab){
      	widthLab = line.length();
      }
	  
	  // Recuperation de la hauteur du labyrinthe
	  if (firstLigne != true){
	      for(std::string::size_type i = 0; i < line.length(); ++i)
		   {
			  char c = line[i];
			  if (c == '+' && firstLigne != true){
			  	startLaby = heightLab;
			  	heightLab = heightLab - heightLab;
			  	firstLigne = true;
			  }
		 	}
	   }
    }
    myfile.close();
  }

//Initialisation d'un tableau 2D
char labyTab[heightLab][widthLab];

//Parcours du fichier et copie du labrinthe dans le tableau 2D
ifstream myfile2 ("labyrinthe.txt");
  if (myfile2.is_open())
  {
    while ( myfile2.good() )
    {
    	getline (myfile2,line);
    	startCompteur2++;

    	if (boolCompteur2 != true){
	      if (startCompteur2 == startLaby){
	      	  startCompteur2 = 0;
	      	  boolCompteur2 = true;
	      }
	   }
	   if (boolCompteur2){
    	for(std::string::size_type i = 0; i < line.length(); ++i)
		   {
		   	 labyTab[startCompteur2][i] = line[i];
		   }
		}
    }
    myfile2.close();
}



// 1ere boucle pour la création des murs horizontaux, du chasseur, des gardiens, des affiches
for(int i = 0; i < heightLab; i++)
{
	for (int j = 0; j < widthLab; j++){
  		char c = labyTab[i][j];

  		switch ( c )  
    	{  
        	case '+':
	    		if (waitFinMur){
	    	    walls[nbWalls] = {j,i,x2Mur,y2Mur,0};
	    	    nbWalls++;
	     	}
	     	x2Mur = j;
	     	y2Mur = i;
	     	waitFinMur = true;
            break;  
	         case '#':  
	            getline(myfile,line);  
	            break;
	         case '-':
	         	break;
	         case ' ':
	         	waitFinMur = false;
	         	break;
	     	case 'a':
	     		if (waitFinMur){
		     		affiches[nbAffiches] = {j, i, j+2,i,0};
		     		nbAffiches++;
	     		}
	     		break;
	     	case 'x':
	     		caisses[nbCaisses] = {j, i,0};
	     		nbCaisses++;
	     		break; 
	     	case 'C':
	     		_guards[0] = new Chasseur (this);
	     		_guards [0] -> _x = (float)j*10.; 
	     		_guards [0] -> _y = (float)i*10.;
	     		break;
	      	case 'G':
	     		_guards [nbGuards] = new Gardien (this, "Marvin");
	     		_guards [nbGuards] -> _x = (float)j*10.;
	     		_guards [nbGuards] -> _y = (float)i*10.;
	     		nbGuards++;
	     		break;		
	    }  
	}
	waitFinMur=false;
}

// 2eme boucle pour la création des murs verticaux et affiches
for(int j = 0; j < widthLab; j++)
{
	for (int i = 0; i < heightLab; i++){
  		char c = labyTab[i][j];
    
  		switch ( c )  
    	{  
        	case '+':
	    		if (waitFinMur){
	    	    walls[nbWalls] = {j,i,x2Mur,y2Mur,0};
	    	    nbWalls++;
	     	}
		     	x2Mur = j;
		     	y2Mur = i;
		     	waitFinMur = true;
	            break;  
	        case '#':  
	            //getline(myfile,line);  
	            break;
	        case ' ':
	         	waitFinMur = false;
	         	break;
	     	case 'a':
	     	if (waitFinMur){
	     		affiches[nbAffiches] = {j, i, j,i+2,0};
	     		nbAffiches++;
	     	}
	     		break;
    	}  
	}
}

	_nwall = nbWalls;
    _walls = walls;

    _nboxes = nbCaisses;
    _boxes = caisses;

    _npicts = nbAffiches;
    _picts = affiches;

    _nguards = nbGuards++;
    



/*
// les 4 murs.
	static Wall walls [] = {
		{ 0, 0, LAB_WIDTH-1, 0, 0 },
		{ LAB_WIDTH-1, 0, LAB_WIDTH-1, LAB_HEIGHT-1, 0 },
		{ LAB_WIDTH-1, LAB_HEIGHT-1, 0, LAB_HEIGHT-1, 0 },
		{ 0, LAB_HEIGHT-1, 0, 0, 0 },
	};
	// une affiche.
	//  (attention: pour des raisons de rapport d'aspect, les affiches doivent faire 2 de long)
	static Wall affiche [] = {
		{ 4, 0, 6, 0, 0 },		// première affiche.
		{ 8, 0, 10, 0, 0 },		// autre affiche.
	};
	// 3 caisses.
	static Box	caisses [] = {
		{ 70, 12, 0 },
		{ 10, 5, 0 },
		{ 65, 22, 0 },
	};
	// juste un mur autour et les 3 caisses et le trésor dedans.
	for (int i = 0; i < LAB_WIDTH; ++i)
		for (int j = 0; j < LAB_HEIGHT; ++j) {
			if (i == 0 || i == LAB_WIDTH-1 || j == 0 || j == LAB_HEIGHT-1)
				_data [i][j] = 1;
			else
				_data [i][j] = EMPTY;
		}
	// indiquer qu'on ne marche pas sur une caisse.
	_data [caisses [0]._x][caisses [0]._y] = 1;
	_data [caisses [1]._x][caisses [1]._y] = 1;
	_data [caisses [2]._x][caisses [2]._y] = 1;
	// les 4 murs.
	_nwall = 5;
	_walls = walls;
	// deux affiches.
	_npicts = 2;
	_picts = affiche;
	// la deuxième à une texture différente.
	char	tmp [128];
	sprintf (tmp, "%s/%s", texture_dir, "voiture.jpg");
	_picts [1]._ntex = wall_texture (tmp);
	// 3 caisses.
	_nboxes = 3;
	_boxes = caisses;
	// le trésor.
	_treasor._x = 10;
	_treasor._y = 10;
	_data [_treasor._x][_treasor._y] = 1;	// indiquer qu'on ne marche pas sur le trésor.
	// le chasseur et les 4 gardiens.
	_nguards = 5;
	_guards = new Mover* [_nguards];
	_guards [0] = new Chasseur (this);
	_guards [1] = new Gardien (this, "drfreak");
	_guards [2] = new Gardien (this, "Marvin"); _guards [2] -> _x = 90.; _guards [2] -> _y = 70.;
	_guards [3] = new Gardien (this, "Potator"); _guards [3] -> _x = 60.; _guards [3] -> _y = 10.;
	_guards [4] = new Gardien (this, "garde"); _guards [4] -> _x = 130.; _guards [4] -> _y = 100.;
	// indiquer qu'on ne marche pas sur les gardiens.
	_data [(int)(_guards [1] -> _x / scale)][(int)(_guards [1] -> _y / scale)] = 1;
	_data [(int)(_guards [2] -> _x / scale)][(int)(_guards [2] -> _y / scale)] = 1;
	_data [(int)(_guards [3] -> _x / scale)][(int)(_guards [3] -> _y / scale)] = 1;
	_data [(int)(_guards [4] -> _x / scale)][(int)(_guards [4] -> _y / scale)] = 1;
*/
}
