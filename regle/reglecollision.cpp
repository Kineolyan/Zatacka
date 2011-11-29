#include "reglecollision.h"
#include <iostream>
using namespace std;

vector< vector<bool> > matriceCollisionsStandard()
{
	vector<bool> ligne(6,true);
	vector< vector<bool> > matrice(6,ligne);
	return matrice;
}


RegleCollision::RegleCollision():m_matriceCollision(matriceCollisionsStandard())
{

}

RegleCollision::RegleCollision(vector< vector<bool> > matriceCollision):m_matriceCollision(matriceCollision)
{

}

RegleCollision::RegleCollision(vector<RegleCollision> regles)
{
	m_matriceCollision = matriceCollisionsStandard();
	for (int i(0); i<6; i++)
	{
		for (int j(0); j<6;j++)
		{
			for (double k(0); k<regles.size();k++)
			{
				m_matriceCollision[i][j] = regles[k].valeurCase(i,j) && m_matriceCollision[i][j];
			}
		}
	}
}



bool RegleCollision::valeurCase(int i,int j) const
{
	return m_matriceCollision[i][j];
}

bool RegleCollision::collision(int numSerpent, vector<int> joueursRencontres) const
{
	bool reponse(false);
	for (double i(0); i<joueursRencontres.size(); ++i)
	{
		if (m_matriceCollision[numSerpent][joueursRencontres[i]])
		{
			reponse = true;
			break;
		}
	}
	return reponse;
}
















