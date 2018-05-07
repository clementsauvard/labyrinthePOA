#include "Chasseur.h"
#include "Gardien.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

/*
 *  Constructeur.
 */
Chasseur::Chasseur (Labyrinthe* l) : Mover (100, 80, l, 0)
{
    life=20;
    _hunter_fire = new Sound ("sons/hunter_fire.wav");
    _hunter_hit = new Sound ("sons/hunter_hit.wav");
    if (_wall_hit == 0)
        _wall_hit = new Sound ("sons/hit_wall.wav");
}

/*
 *  Tente un deplacement.
 */
bool Chasseur::move_aux (double dx, double dy)
{
    if (EMPTY == _l -> data ((int)((_x + dx) / Environnement::scale),
                            (int)((_y + dy) / Environnement::scale)))
    {
        _x += dx;
        _y += dy;
        return true;
    }
    return false;
}

/*
 *  Fait bouger la boule de feu (ceci est une exemple, � vous de traiter les collisions sp�cifiques...)
 */
bool Chasseur::process_fireball (float dx, float dy)
{
    // calculer la distance entre le chasseur et le lieu de l'explosion.
    float   x = (_x - _fb -> get_x ()) / Environnement::scale;
    float   y = (_y - _fb -> get_y ()) / Environnement::scale;
    float   dist2 = x*x + y*y;
    float   dmax2;
    // on bouge que dans le vide!
    auto xPos = (int)((_fb -> get_x () + dx) / Environnement::scale);
    auto yPos = (int)((_fb -> get_y () + dy) / Environnement::scale);

    //On regarde la case o� est la boule
    switch ( _l -> data ((int)((_fb -> get_x () + dx) / Environnement::scale),(int)((_fb -> get_y () + dy) / Environnement::scale)) )  
    {
        case EMPTY: 
            message("LE VIDE");
            return true;  
            break;  
        case 1:
            message("UN MUR");  
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());  
            _wall_hit -> play (1. - dist2/dmax2);
            return false;
            break;
        case 2:
            message("UNE CAISSE");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            _wall_hit -> play (1. - dist2/dmax2);
            return false;
            break;
        case 3:  
            message("UN TRESOR");
            // exit(0) vous avez gagnez
            exit(0);
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            _wall_hit -> play (1. - dist2/dmax2);
            //_l -> partie_terminee(true);
            return false;
            break;
        case 4:  
            message("UN GARDIEN");
            //On regarde quel gardien on a touch� et on d�cr�mente sa vie de 1, et on check si il est mort
            for (int i = 1; i < _l ->_nguards ; i++){
                if (ceil(_l -> _guards[i] -> _x/Environnement::scale) == xPos && ceil(_l -> _guards[i] -> _y/Environnement::scale) == yPos){
                     reinterpret_cast<Gardien*> (_l -> _guards[i]) -> glife = reinterpret_cast<Gardien*> (_l -> _guards[i]) -> glife - 1;
                     reinterpret_cast<Gardien*> (_l -> _guards[i]) -> isDead();
                }
            }
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());  
            _wall_hit -> play (1. - dist2/dmax2);
            return false;
            break;
         default:  
            message("");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            _wall_hit -> play (1. - dist2/dmax2);
            return false;
    }
    // collision...
    // calculer la distance maximum en ligne droite.
    
    // faire exploser la boule de feu avec un bruit fonction de la distance.
    
//    life--;
    
    //message ("Booom...");

}
/*
 *  Tire sur un ennemi.
 */
void Chasseur::fire (int angle_vertical)
{
    // Calcul permettant de d�finir la pr�cision du tir selon la vie du gardien
    int p1 = ( ((rand() % 10) - 5)*((20-life))/20 );
    int p2 = ( ((rand() % 10) - 5)*((20-life))/20 );
    message ("I AM THE WHOOSH...  %d , %d",p1,life);
    _hunter_fire -> play ();
    _fb -> init (/* position initiale de la boule */ _x, _y, 10.,
                /* angles de vis�e */ angle_vertical+p1, _angle+p2);
}
