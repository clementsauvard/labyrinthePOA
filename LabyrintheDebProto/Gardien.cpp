#include "Chasseur.h"
#include "Gardien.h"
#include "Labyrinthe.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stack>

using namespace std;

Gardien::Gardien (Labyrinthe* l,const char* modele) : Mover (100, 80, l, modele)
{
	glife=5;
	mort = false;
	alloc=false;
	attaque = false;
	rangeDown = rand() % 20 + 10;
	rangeUp = rand() %  30 + 30;
}
bool pute = true;
void Gardien::update (void) {
		
	int haut;
	int gauche;
	int droite;
	int bas;

	if (reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) < 20){

		attaque = true;

		_distToC = (int**)malloc(sizeof(int*) * (_l -> width()));
		 
		for (int i = 0; i < _l -> width(); i++)
		_distToC[i] = (int*)malloc(sizeof(int) * (_l -> height()));
		alloc=true;
		for(int j = 0; j < _l -> width(); j++)
		{
		    for (int i = 0; i < _l -> height(); i++){
		        _distToC[j][i]=-1;
		    }
		}
		bool done=false;
        bool fini=false;
		int cpt=0;
        int x1;
        int y1;
		stack< pair <int,int> > i2;
		while(!fini){
            x1 = rand() % _l -> width();
            y1 = rand() % _l -> height();
            if (reinterpret_cast<Labyrinthe*>(_l) -> dist(x1,y1) > 0){
                fini = true;
            }
        }
        //cout << x1 << endl;
        //cout << y1 << endl;

		i2.push(make_pair (x1,y1));
		pair <int,int> x2;
		while(!done)
		{
		    x2=i2.top();
		    cpt=INT_MAX;
		    if(x2.second + 1 <= _l -> height() && _distToC[x2.first][x2.second+1] >-1 )
		      {cpt= min(cpt,_distToC[x2.first][x2.second+1]+1);}
		    if(x2.second - 1 <= _l -> height() && _distToC[x2.first][x2.second-1] >-1 )
		      {cpt= min(cpt,_distToC[x2.first][x2.second-1]+1);}
		    if(x2.first + 1 <= _l -> width() && _distToC[x2.first+1][x2.second] >-1 )
		      {cpt= min(cpt,_distToC[x2.first+1][x2.second]+1);}
		    if(x2.first - 1 <= _l -> width() && _distToC[x2.first-1][x2.second] >-1 )
		      {cpt= min(cpt,_distToC[x2.first-1][x2.second]+1);}
		    //cout  << "X : " << x.second << " Y : " << x.first  << " tab : " << _dist[x.first][x.second] << " data : " << (int)_data [x.first][x.second] << "cpt : "<< cpt <<endl;
		    if (cpt==INT_MAX)
		      {cpt=0;}
		    i2.pop();
		    
		    _distToC[x2.first][x2.second]=cpt;
		    //cout  << "tab2 : " << _dist[x.first][x.second] << " data : " << (int)_data [x.first][x.second] <<endl;

		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second+1) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second+1) >= 4 ) {
		        if(_distToC[x2.first][x2.second+1] == -1 || cpt+1 < _distToC[x2.first][x2.second+1]  )
		        {
		            if(x2.second+1 <= _l -> height())
		            {
		                i2.push(make_pair (x2.first,x2.second+1));
		            }
		        }
		    }

		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first+1,x2.second) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first+1,x2.second) >= 4 ) 
		    {
		        if(_distToC[x2.first+1][x2.second] == -1 || cpt+1 < _distToC[x2.first+1][x2.second]  )
		        {
		            if(x2.first+1 <= _l -> width())
		            {
		                i2.push(make_pair (x2.first+1,x2.second));
		            }
		        }
		    }


		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first-1,x2.second) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first-1,x2.second) >= 4 ) 
		    {
		        if(_distToC[x2.first-1][x2.second] == -1 || cpt+1 < _distToC[x2.first-1][x2.second]  )
		        {
		            if(x2.first-1 >= 0)
		            {
		               i2.push(make_pair (x2.first-1,x2.second));
		            }
		        }
		    }
		    
		    if((int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second-1) == 0 || (int) reinterpret_cast<Labyrinthe*>(_l) -> data (x2.first,x2.second-1) >= 4 ) {
		        if(_distToC[x2.first][x2.second-1] == -1 || cpt+1 < _distToC[x2.first][x2.second-1]  )
		        { 
		            if(x2.second-1 >= 0)
		            {
		              i2.push(make_pair (x2.first,x2.second-1));
		            }
		        }
		    }

		    //cout << "Le nombre d'éléments de la pile est : " << i.size() << endl;
		    
		    
		    
		    cpt++;
		    if(i2.empty()  
		       //|| i.size()>600
		      ){
		        done=true;
		    }
		    
		}

	}
	else if (reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) > 140 || (alloc && distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) < 2))
	{
		attaque = false;
	}

	//cout << "case dikstra : " << reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)) <<endl;
	//cout << "x : " << ceil(_x/_l -> scale) << " y : " << ceil(_y/_l -> scale) << endl;
	
	if (!attaque){
		haut = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
		gauche = reinterpret_cast<Labyrinthe*>(_l) -> dist(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
		droite = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale)+1,floor(_y/_l -> scale));
		bas = reinterpret_cast<Labyrinthe*>(_l) -> dist(floor(_x/_l -> scale),floor(_y/_l -> scale)+1);
	}
	else {
		haut = distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)-1);
		gauche = distToC(ceil(_x/_l -> scale)-1,ceil(_y/_l -> scale));
		droite = distToC(ceil(_x/_l -> scale)+1,ceil(_y/_l -> scale));
		bas = distToC(ceil(_x/_l -> scale),ceil(_y/_l -> scale)+1);
	}

	if (haut == -1){
		haut = INT_MAX;
	}
	if (bas == -1){
		bas = INT_MAX;
	}
	if (droite == -1){
		droite = INT_MAX;
	}
	if (gauche == -1){
		gauche = INT_MAX;
	}

	vector<pair<int,int> > tempDir;
	
	int temp = min(min(min(haut,gauche),droite),bas);
	
	//cout << " temp : " << temp << endl;

	if (temp == haut && temp != 0 ){
		tempDir.push_back(make_pair(0,-1));
	}
	if (temp == bas && temp != 0 ){
		tempDir.push_back(make_pair(0,1));
	}
	if (temp == droite && temp != 0 ){
		tempDir.push_back(make_pair(1,0));
	}
	if (temp == gauche && temp != 0 ){
		tempDir.push_back(make_pair(-1,0));
	}
/*
	for (int i = 0; i < tempDir.size(); i++){
		cout << "x : " << tempDir[i].first << endl;
		cout << "y : " << tempDir[i].second << endl;
	}
	*/
	//cout << tempDir.size() << endl;
	/*
	if (tempDir.size() > 1){

		int v2 = rand() % tempDir.size();
		if (tempDir[v2].first == 1){
			_angle = 270;
		}
		if (tempDir[v2].first == -1){
			_angle = 90;
		}
		if (tempDir[v2].second == 1){
			_angle = 0;
		}
		if (tempDir[v2].second == -1){
			_angle = 180;
		}
		move(tempDir[v2].first,tempDir[v2].second);
		
	}*/
	//cout << tempDir.size() << endl;
	if (tempDir.size() >= 1){
		
		if (!mort){
			if (tempDir[0].first == 1){
				_angle = 270;
			}
			if (tempDir[0].first == -1){
				_angle = 90;
			}
			if (tempDir[0].second == 1){
				_angle = 0;
			}
			if (tempDir[0].second == -1){
				_angle = 180;
			}
			move(tempDir[0].first,tempDir[0].second);	
		}
		else {
			reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0);
		}
	}

	
	bool wallMet = false;
	int xChasseur = ((int)_l -> _guards[0] -> _x/Environnement::scale);
	int yChasseur = ((int)_l -> _guards[0] -> _y/Environnement::scale);
	int xGarde = ceil( _x/Environnement::scale );
	int yGarde = ceil( _y/Environnement::scale );

	if ( (xChasseur - xGarde) == 0){
		if ((yChasseur - yGarde) > 0){
			for (int i = 0; i < (yChasseur - yGarde) ; i++){
				if ( reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde,yGarde+i) == 1 ){
					wallMet = true;
				}
			}
		}
		else {
			for (int i = 0; i > (yChasseur - yGarde); i--){
				if (reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde,yGarde+i) == 1){
					wallMet = true;
				}
			}
		}
	}
	else
	{	
		if ( (yChasseur - yGarde) == 0){
			if ((xChasseur - xGarde) > 0){
				for (int i = 0; i < (xChasseur - xGarde) ; i++){
					if ( reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde+i,yGarde) == 1 ){
						wallMet = true;
					}
				}
			}
			else {
				for (int i = 0; i > (xChasseur - xGarde); i--){
					if (reinterpret_cast<Labyrinthe*>(_l) -> data (xGarde+i,yGarde) == 1 ){
						wallMet = true;
					}
				}
			}
		}
		else
		{
			wallMet=true;
		}
	}


	if (!wallMet  ){
		fire(0);
	}
		
}

bool Gardien::move (double dx, double dy) {
		
		if(reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale),ceil(_y/_l -> scale)) == 4 )
		{
			reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),0); 
		}
		//cout << (int) reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale)+dx,ceil(_y/_l -> scale)+dy) << endl;

		_x += dx;
		_y += dy;
		if(reinterpret_cast<Labyrinthe*>(_l) -> data (ceil(_x/_l -> scale),ceil(_y/_l -> scale)) == 0 )
		{
			reinterpret_cast<Labyrinthe*>(_l) -> setData (ceil(_x/_l -> scale),ceil(_y/_l -> scale),4);
		}

		return true;
}


bool Gardien::process_fireball (float dx, float dy) { 
	float   x = (_x - _fb -> get_x ()) / Environnement::scale;
    float   y = (_y - _fb -> get_y ()) / Environnement::scale;
    float   dist2 = x*x + y*y;
    float   dmax2;

    switch ( _l -> data ((int)((_fb -> get_x () + dx) / Environnement::scale),(int)((_fb -> get_y () + dy) / Environnement::scale)) )  
    {
        case EMPTY: 
            message("LE VIDE");
            return true;  
            break;  
        case 1:
        	//cout << _x << endl;
        	//cout << _fb -> get_x () << endl;
            message("UN MUR");  
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());  
            return false;
            break;
        case 2:
            message("UNE CAISSE");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
        case 3:  
            message("UN TRESOR");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
        case 5:  
            message("UN Gardien");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
            break;
         default:  
            message("wtfdidujustdidulilshit");
            dmax2 = (_l -> width ())*(_l -> width ()) + (_l -> height ())*(_l -> height ());
            return false;
    }
}
void Gardien::fire (int angle_vertical) {
	int p1 = ( ((rand() % 10) - 5)*((20-glife))/20 );
    int p2 = ( ((rand() % 10) - 5)*((20-glife))/20 );

	auto posxC = (_l -> _guards[0] -> _x)/ Environnement::scale;
	auto posyC = (_l -> _guards[0] -> _y)/ Environnement::scale;

	//cout << posxC << endl;
	//cout << _x/Environnement::scale << endl;

	auto angleTir = ceil(atan2(( posxC-_x/Environnement::scale ),(posyC-_y/Environnement::scale ) ) * 180 / M_PI);

	//cout << angleTir << "fdp"<< endl;
    _fb -> init (/* position initiale de la boule */ _x, _y, 10.,
                /* angles de visée */ 0, angleTir);
}

void Gardien::isDead () {
	cout << glife << endl;
	if (glife <= 0) {
		cout << "t'es mort lel" << endl;
		mort = true;
		rester_au_sol();
	}

}