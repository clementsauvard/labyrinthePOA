#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <stack>

#include <limits.h>
#include <malloc.h>

using namespace std;

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
  //Variables
  string line;
  int widthLab = 0;
  int heightLab = 0;
  bool firstLigne = false;
  bool boolCompteur2 = false;
  int startCompteur2 = 0;
  int startLaby = 0;

  int x2Mur;
  int y2Mur;
  bool waitFinMur = false;

  static Wall walls[100]; //murs
  static Box caisses[20]; //caisses
  static Wall affiches[20];

  _guards = new Mover* [100];

  int nbWalls = 0;
  int nbAffiches = 0;
  int nbCaisses = 0;
  int nbGuards = 1;


  // Ouverture du fichier
  ifstream myfile (filename);
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


//On sauvegarde la hauteur et la largeur du labyrinthe
setHeight(heightLab);
setWidth(widthLab);

// Initialisation du tableau 2D data
_data = (char**)malloc(sizeof(char*) * widthLab);
for (int i = 0; i < widthLab; i++)
_data[i] = (char*)malloc(sizeof(char) * heightLab);

//Initialisation d'un tableau 2D
char labyTab[heightLab][widthLab];

//Parcours du fichier et copie du labrinthe dans le tableau 2D
ifstream myfile2 (filename);
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
        _data [j][i] = 0;        
        char c = labyTab[i][j];
  		switch ( c )  
        {  
          //Début de mur
          case '+':
            if (waitFinMur){
              walls[nbWalls] = {j,i,x2Mur,y2Mur,0};
              nbWalls++;
            }
            x2Mur = j;
            y2Mur = i;
            waitFinMur = true;
          	break;
             //commentaire  
          case '#':  
                getline(myfile,line);  
	            break;
          case '-':
              break;
          case ' ':
              waitFinMur = false;
              break;
           //Affiche a
	     	   case 'a':
                if (waitFinMur){
                    affiches[nbAffiches] = {j, i, j+2,i,0};
                    nbAffiches++;
                }
                break;
           case 'b':
                if (waitFinMur){
                    affiches[nbAffiches] = {j, i, j+2,i,0};
                    nbAffiches++;
                }
                break;
           //Une caisse
	     	   case 'x':
                _data [j][i] = 2;
                caisses[nbCaisses] = {j, i,0};
                nbCaisses++;
                break; 
            //Le chasseur
	     	   case 'C':
                //_data [j][i] = 5;
                _guards[0] = new Chasseur (this);
                _guards [0] -> _x = (float)j*scale; 
                _guards [0] -> _y = (float)i*scale;
                break;
            //Gardiens
	      	  case 'G':
                _data [j][i] = 4;
                _guards [nbGuards] = new Gardien (this, "Potator");
                _guards [nbGuards] -> _x = (float)j*scale;
                _guards [nbGuards] -> _y = (float)i*scale;
                nbGuards++;
                break;
            // le tresor
            case 'T':
                _data [j][i] = 3;
                _treasor._x =j;
                _treasor._y =i;
                break;
	    }  
        if (waitFinMur)
        {_data [j][i] = 1;}
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
          case 'b':
            if (waitFinMur){
              affiches[nbAffiches] = {j, i, j,i+2,0};
              nbAffiches++;
            }
            break;
    	}
        
        if (waitFinMur)
        {_data [j][i] = 1;}
          
	}
}

//Initialisation du tableau 2D _dist qui contient le tableau résultant de l'algorithme de Dikjstra
_dist = (int**)malloc(sizeof(int*) * widthLab);
for (int i = 0; i < widthLab; i++)
_dist[i] = (int*)malloc(sizeof(int) * heightLab);

//On initialise ce tableau a -1 partout
for(int j = 0; j < widthLab; j++)
{
    for (int i = 0; i < heightLab; i++){
        _dist[j][i]=-1;
    }
}

//----------------------------- Dikjstra -----------------------------
bool done=false;
int cpt=0;
stack< pair <int,int> > i;
i.push(make_pair (_treasor._x,_treasor._y));
    pair <int,int> x;
while(!done)
{


    x=i.top();
    cpt=INT_MAX;
    if(x.second + 1 <= heightLab && _dist[x.first][x.second+1] >-1 )
      {cpt= min(cpt,_dist[x.first][x.second+1]+1);}
    if(x.second - 1 <= heightLab && _dist[x.first][x.second-1] >-1 )
      {cpt= min(cpt,_dist[x.first][x.second-1]+1);}
    if(x.first + 1 <= widthLab && _dist[x.first+1][x.second] >-1 )
      {cpt= min(cpt,_dist[x.first+1][x.second]+1);}
    if(x.first - 1 <= widthLab && _dist[x.first-1][x.second] >-1 )
      {cpt= min(cpt,_dist[x.first-1][x.second]+1);}
    if (cpt==INT_MAX)
      {cpt=0;}
    i.pop();
    
    
    _dist[x.first][x.second]=cpt;  

    if((int)_data [x.first][x.second+1] == 0 || (int)_data [x.first][x.second+1] >= 4 ) {
        if(_dist[x.first][x.second+1] == -1 || cpt+1 < _dist[x.first][x.second+1]  )
        {
            if(x.second+1 <= heightLab)
            {
                i.push(make_pair (x.first,x.second+1));
            }
        }
    }

    if((int)_data [x.first+1][x.second] == 0 || (int)_data [x.first+1][x.second] >= 4 ) 
    {
        if(_dist[x.first+1][x.second] == -1 || cpt+1 < _dist[x.first+1][x.second]  )
        {
            if(x.first+1 <= widthLab)
            {
                i.push(make_pair (x.first+1,x.second));
            }
        }
    }


    if((int)_data [x.first-1][x.second] == 0 || (int)_data [x.first-1][x.second] >= 4 ) 
    {
        if(_dist[x.first-1][x.second] == -1 || cpt+1 < _dist[x.first-1][x.second]  )
        {
            if(x.first-1 >= 0)
            {
               i.push(make_pair (x.first-1,x.second));
            }
        }
    }
    
    if((int)_data [x.first][x.second-1] == 0 || (int)_data [x.first][x.second-1] >= 4 ) {
        if(_dist[x.first][x.second-1] == -1 || cpt+1 < _dist[x.first][x.second-1]  )
        { 
            if(x.second-1 >= 0)
            {
              i.push(make_pair (x.first,x.second-1));
            }
        }
    }
    
    
    
    cpt++;
    if(i.empty()){
        done=true;
    }
    
}
//--------------------------------------------------------------//




	 _nwall = nbWalls;
    _walls = walls;

    _nboxes = nbCaisses;
    _boxes = caisses;

    _npicts = nbAffiches;
    _picts = affiches;

    _nguards = nbGuards++;
    
}
