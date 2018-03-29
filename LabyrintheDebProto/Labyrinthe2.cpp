#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Sound*	Chasseur::_hunter_fire;	// bruit de l'arme du chasseur.
Sound*	Chasseur::_hunter_hit;	// cri du chasseur touché.
Sound*	Chasseur::_wall_hit;	// on a tapé un mur.

Environnement* Environnement::init (char* filename)
{
	return new Labyrinthe (filename);
}

int estDansTabChar(char* tab, int nb, char c)
{
    for(int i =0; i< nb; i++)
        if(tab[i] == c)
             return i;

    return -1;
}

Labyrinthe::Labyrinthe (char* filename)
{
    ifstream fichier(filename, ios::in);

    if(fichier)
    {
        // creation des variables necessaires
        static Wall walls[10]; //murs
        static Box caisses[10]; //caisses

        int i=0, j=0;
        int nbWall=0, nbCaisses=0;

        //initialisation du labyrinthe
        int nbLigne = 10;
        int nbColonne = 10;
        char laby[nbLigne][nbColonne];

        //Obtenir les affiches
        int nbAffiche=0, nbAfficheDispo=0;
        char afficheDispo[10]; // lettre pour une affiche
        const char* textAffiche[10]; // lettre pour une affiche
        static Wall affiche[10]; //affiche

        // Test du premier parcours et initalisation d'un tableau char
        string ligne;
        while(getline(fichier, ligne))
        {
            if(ligne[0] != '+' && ligne[0] != '|' && estDansTabChar(afficheDispo, nbAfficheDispo, ligne[0]) == -1)
            {
                // faire des trucs
                if(ligne[0] != ' ')
                {
                    afficheDispo[nbAfficheDispo] = ligne[0];
                    j=1;
                    while(ligne[j] == ' ') j++; // ici on passe tous les espaces
                    if(ligne.length() > j)
                    {
                        textAffiche[nbAfficheDispo] = (ligne.substr(j, ligne.length())).c_str();
                        nbAfficheDispo++;
                    }
                }

            }
            else
            {
                for(j = 0; j < ligne.length(); j++)
                {
                    laby[i][j] = ligne[j];
                }
                i++;
            }
        }

        // Wall horizontaux
        for(i = 0; i < nbLigne; i++)
        {
            int wall[4];
            wall[1]=-1;
            wall[4]=-1;
            wall[0] = i;
            wall[2] = i;

            for(j = 0; j < nbColonne; j++)
            {
                if(wall[1] != -1 && laby[i][j] == '+')
                {
                    wall[3] = j;
                    walls[nbWall] = {wall[0], wall[1], wall[2], wall[3], 0};
                    nbWall = nbWall + 1;
                }

                if(laby[i][j] == '+' && laby[i][j+1] == '-')
                {
                    wall[1] = j;
                }

                //Initialisation des caisses
                if(laby[i][j] == 'X')
                {
                    caisses[nbCaisses] = {i,j, 0};
                    _data [i][j] = 1;
                    nbCaisses++;
                }

                // Initialisation du tresor
                if(laby[i][j] == 'T')
                {
                    _treasor._x = i;
                    _treasor._y = j;
                    _data [_treasor._x][_treasor._y] = 1;
                }

                //initialisation des affiches horizontaux
                if(estDansTabChar(afficheDispo, nbAfficheDispo, laby[i][j]) != -1 && laby[i][j+1] == '-'
                        && laby[i][j-1] == '-')
                {
                    int texture = estDansTabChar(afficheDispo, nbAfficheDispo, laby[i][j]);
                    char tmp [128];
                    sprintf (tmp, "%s/%s", texture_dir, textAffiche[texture]);
                    affiche[nbAffiche] = {wall[0], j-1, wall[2], j+1, 0};
                    affiche[nbAffiche]._ntex = wall_texture(tmp);
                    nbAffiche++;
                }
            }
        }

        // Wall verticaux
        for(i = 0; i < nbColonne; i++)
        {
            int wall[4];
            wall[1]=-1;
            wall[4]=-1;
            wall[0] = i;
            wall[2] = i;

            for(j = 0; j < nbLigne; j++)
            {
                if(wall[1] != -1 && laby[j][i] == '+')
                {
                    wall[3] = j;
                    walls[nbWall] = {wall[1], wall[0], wall[3], wall[2], 0};
                    nbWall = nbWall + 1;
                }
                if(laby[j][i] == '+' && laby[j+1][i] == '|')
                {
                    wall[1] = j;
                }
/*
                //initialisation des affiches verticaux
                 if(estDansTabChar(afficheDispo, nbAfficheDispo, laby[i][j]) && laby[j+1][i] == '|'
                    && laby[j-1][i] == '|'){
                    int texture = estDansTabChar(afficheDispo, nbAfficheDispo, laby[i][j]);
                    char tmp [128];
                    sprintf (tmp, "%s/%s", texture_dir, textAffiche[texture]);
                    affiche[nbAffiche] = {wall[1], j-1, wall[3], j+1, 0};
                    affiche[nbAffiche]._ntex = wall_texture(tmp);
                    nbAffiche++;
                 }*/
            }
        }

        _nwall = nbWall;
        _walls = walls;

        _nboxes = nbCaisses;
        _boxes = caisses;


        _npicts = nbAffiche;
        _picts = affiche;
        //temporaire pour tester
        _nguards = 1;
        _guards = new Mover* [_nguards];
        _guards [0] = new Chasseur (this);

        fichier.close();
    }
    else cerr << "Fichier : " << filename << " inexistant !" << endl;
}
