#include "regles.h"

#include <iostream>

using namespace std;

/**
* regles du jeu original
*/


Regle cestLeGameplay()
{
	Regle cestlegameplay;
	return cestlegameplay;
}

Regle sansDepartsProches(double distanceMin)
{
    vector<int> ligne(13,0);
	vector< vector<int> > matrice(9,ligne);
	for (int i(0); i<9; i++)
	{
		for (int j(0); j<13; ++j)
		{
			if (j<2||j>10||i<1||i>7)
			{
				matrice[i][j]=1;
			}
		}
	}
    RegleCollision regleCollision;
    ReglePoints reglePoints;
	RegleInitialisation regleInitialisation(distanceMin, matrice,13,9);
	Regle regle(regleCollision, regleInitialisation, reglePoints);
	return regle;
}

/**
* 3 joueurs de chaque coté dirigés vers l'autre coté
*/
Regle batailleRangee(int largeurJeu, int hauteurJeu)
{
    vector<pair<int,int> > positions(6);
    vector<double> directions(6);
    for (int i(0); i<3 ; ++i)
    {
        positions[i].first = largeurJeu/6;
        positions[i].second = (i+1) * hauteurJeu/4;
        positions[i+3].first = 5*largeurJeu/6;
        positions[i+3].second = (i+1) * hauteurJeu/4;
        directions[i] = 0;
        directions[i+3] = 90;
    }
    RegleCollision regleCollision;
    ReglePoints reglePoints;
	RegleInitialisation regleInitialisation(directions , positions);
	Regle regle(regleCollision, regleInitialisation, reglePoints);
	return regle;
}

Regle departAuCentre(int largeurJeu, int hauteurJeu)
{
    vector<pair<int,int> > positions(6);
    vector<double> directions(6);
    for (int i(0); i<6; ++i)
    {
        positions[i].first = largeurJeu/2+floor(40*cos(i*3.14/3));
        positions[i].second = hauteurJeu/2+floor(40*sin(i*3.14/3));
        directions[i] = i * 30;
    }
    RegleCollision regleCollision;
    ReglePoints reglePoints;
	RegleInitialisation regleInitialisation(directions , positions);
	Regle regle(regleCollision, regleInitialisation, reglePoints);
	return regle;
}

Regle departAuxCoins(int largeurJeu, int hauteurJeu)
{
    vector<pair<int,int> > positions(6);
    vector<double> directions(6);
    for (int i(0); i<3; ++i)
    {
        positions[2*i].first = i*(largeurJeu-3)/2+1;
        positions[2*i].second = 1;
        positions[2*i+1].first = i*(largeurJeu-3)/2+1;
        positions[2*i+1].second = hauteurJeu-2;
        directions[2*i] = 22.5*(i+1);
        directions[2*i+1] = -22.5*(i+1);
    }
    RegleCollision regleCollision;
    ReglePoints reglePoints;
	RegleInitialisation regleInitialisation(directions , positions);
	Regle regle(regleCollision, regleInitialisation, reglePoints);
	return regle;
}

/**
* fait des equipes de nbrJoueurs joueurs :
* option=0 les coequipiers peuvent se passer au travers
* option=1 les coequipiers ne peuvent pas se passer au travers
*/
Regle parEquipe(int option, int nbrEquipes) {
   	vector<bool> ligneColli(6,true);
   	vector< vector<bool> > matriceColli(6,ligneColli);
	vector<int> lignepts(6,1);
	vector< vector<int> > matricePts(6,lignepts);
    for (int i = 0; i<nbrEquipes;++i)
    		for (int j(0); j<6/nbrEquipes; ++j)
    		{
    			for (int k(j); k<6/nbrEquipes; ++k)
    			{
                    {
                        if (j!=k && option == 0)
                        {
                            matriceColli[6/nbrEquipes*i+k][6/nbrEquipes*i+j] = false;
                            matriceColli[6/nbrEquipes*i+j][6/nbrEquipes*i+k] = false;
                        }
                        matricePts[6/nbrEquipes*i+k][6/nbrEquipes*i+j] = 0;
                        matricePts[6/nbrEquipes*i+j][6/nbrEquipes*i+k] = 0;
    			    }
    			}


    		}

    for (int i(0); i<6;++i)
    	{
    		for (int j(0); j<6; ++j)
    			{
                        cout << matriceColli[i][j] << "\t";
                }
            cout << endl;

        }
        cout << endl << endl ;

    for (int i(0); i<6;++i)
    	{
    		for (int j(0); j<6; ++j)
    			{
                        cout << matricePts[i][j] << "\t";
                }
            cout << endl;

        }
    RegleCollision regleCollision(matriceColli);
   	ReglePoints reglePoints(matricePts);
	RegleInitialisation regleInitialisation;
	Regle regle(regleCollision, regleInitialisation, reglePoints);
	return regle;

}


