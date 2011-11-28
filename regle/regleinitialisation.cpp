#include "regleinitialisation.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "../util/keywords.h"

using namespace std;

vector< vector<int> > positionsExcluesStandard()
{	
	vector<int> ligne(13,0);
	vector< vector<int> > matrice(9,ligne);
	for (int i(0); i<9; i++)
	{
		for (int j(0); j<13; ++j)
		{
			if (j<3||j>9||i<2||i>7)
			{
				matrice[i][j]=1;
			}
		}
	}
	return matrice;
}

RegleInitialisation::RegleInitialisation(Zatacka& jeu):m_distanceMin(1),m_positionsFixes(false),m_dimJ(13),m_dimI(9),m_jeu(jeu),m_positionsExclues(positionsExcluesStandard())
{
}

RegleInitialisation::RegleInitialisation(vector<double> directionsPossibles, vector< pair<int,int> > positionsPossibles, Zatacka& jeu):m_positionsFixes(true),m_directionsPossibles(directionsPossibles),m_positionsPossibles(positionsPossibles),m_jeu(jeu)
{

}

RegleInitialisation::RegleInitialisation(double distanceMin,vector< vector<int> > positionsExclues,int dimJ, int dimI, Zatacka& jeu):m_distanceMin(distanceMin),m_positionsFixes(false),m_dimJ(dimJ),m_dimI(dimI),m_positionsExclues(positionsExclues),m_jeu(jeu)
{

}

RegleInitialisation::RegleInitialisation(vector<RegleInitialisation> regles, Zatacka& jeu):m_jeu(jeu)
{		
		m_distanceMin = 1;
		m_positionsFixes = false;
		m_dimJ = 0;
		m_dimI = 0;
		vector<double> dirpos(6,0);
		vector< pair<int,int> > pospos(6);
		for (int i(0); i<regles.size(); ++i)
		{	
			m_positionsFixes |= regles[i].positionsFixes();
			if (regles[i].positionsFixes())
			{
				for (int j(0); j<6; ++j)
				{
					dirpos[j] = regles[i].direction(i);
					pospos[j] = regles[i].position(i);
				}
			}
			else
			{
				if (regles[i].distanceMin()>m_distanceMin)
				{
					m_distanceMin = regles[i].distanceMin();
				}
				if (regles[i].dimJ()>m_dimJ)
				{
					m_dimJ = regles[i].dimJ();
				}
				if (regles[i].dimI()>m_dimI)
				{
					m_dimI = regles[i].dimI();
				}
			}
			
		}
		vector<int> ligneex(m_dimJ);
		vector< vector<int> > posex(m_dimI, ligneex);
		for (int i(0); i<m_dimI; ++i)
		{
			for (int j(0); j<m_dimJ; ++j)
			{
				for (int k(0); k<regles.size(); ++k)
				{
					if (regles[k].positionsFixes() == false)
					{
						posex[i][j] = regles[k].positionExclue((i*regles[k].dimI())/m_dimI, (j*regles[k].dimJ())/m_dimJ);
					}
				}
			}
		}
		m_directionsPossibles = dirpos;
		m_positionsPossibles = pospos;
		m_positionsExclues = posex;
}

double RegleInitialisation::distanceMin() const
{
	return m_distanceMin;
}

bool RegleInitialisation::positionsFixes() const
{
	return m_positionsFixes;
}

int RegleInitialisation::positionExclue(int i, int j) const
{
	return m_positionsExclues[i][j];
}

int RegleInitialisation::dimI() const
{
	return m_dimI;
}

int RegleInitialisation::dimJ() const
{
	return m_dimJ;
}

double RegleInitialisation::direction(int i) const
{
	return m_directionsPossibles[i];
}

pair<int , int> RegleInitialisation::position(int i) const
{
	return m_positionsPossibles[i];
}


vector< pair<int,int> > RegleInitialisation::positionsDepart() const
{
	vector< pair<int,int> > positionsSerpents(0);
	if (m_positionsFixes)
	{
		for (int i(0); i<6; ++i)
		{
			positionsSerpents.push_back(m_positionsPossibles[i]);
		}
	}
	else
	{
		bool positionValide;
		pair<int,int> positionTemporaire;
		float x;
		float y;
		int dimEcranJeuX(m_jeu.largeurJeu());
		int dimEcranJeuY(m_jeu.hauteurJeu());
		for (int i; i<6; ++i)
		{
			positionValide = false;
			while (positionValide = false)
			{
				positionTemporaire.first = 1+ rand() % (dimEcranJeuX-2); //on exclut automatiquement les premiere et dernieres lignes de pixel
				positionTemporaire.second = 1+ rand() % (dimEcranJeuY-2);
				if (m_positionsExclues[(positionTemporaire.first*m_dimJ)/dimEcranJeuX][(positionTemporaire.second*m_dimI)/dimEcranJeuY]==1)
				{
					positionValide = true;
					x=positionTemporaire.first;
					y=positionTemporaire.second;
					for (int j(0); j<positionsSerpents.size(); ++j)
					{
						if (sqrt(pow(x-positionsSerpents[j].first,2)-pow(y-positionsSerpents[j].second,2))<m_distanceMin)
						{
							positionValide=false;
							break;
						}
					}
				}
			}
			positionsSerpents.push_back(positionTemporaire);
		}
	}
	return positionsSerpents;
}

vector<double> RegleInitialisation::directionsDepart() const
{
	vector<double> directionsSerpents(0);
	if (m_positionsFixes)
	{
		for (int i(0); i<6; ++i)
		{
			directionsSerpents.push_back(m_directionsPossibles[i]);
		}
	}
	else
	{
		for (int i; i<6; ++i)
		{
			directionsSerpents.push_back(M_PI*0.001*(rand()%2000));
		}
	}
	return directionsSerpents;
}






