#include "reglecollision.h"

using namespace std;

vector< vector<bool> > matriceCollisionsStandard()
{
	vector<bool> ligne(6,true);
	vector< vector<bool> > matrice(6,ligne);
	return matrice;
}


RegleCollision::RegleCollision()
{
	matriceCollisionsStandard(m_matriceCollision);
}

RegleCollision::RegleCollision(vector< vector<bool> > matriceCollision):m_matriceCollision(matriceCollision)
{

}

RegleCollision::RegleCollision(vector<RegleCollision> regles)
{
	m_matriceCollision = matriceCollisionsStandard;
	for (int i(0); i<6; i++)
	{
		for (int j(0); i<6;j++)
		{
			for (int k(0); k<regles.size();k++)
			{
				m_matriceCollision[i][j]&=regles[k].valeurCase(i,j);
			}
		}
	}
}

bool RegleCollision::collision(int numSerpent,vector<int> couleursRencontrees) const
{
	bool meurt(false);
	for (int i(0); i<couleursRencontrees.size(); i++)
	{
		if (valeurCase(numSerpent,i))
		{
			meurt = true;
			break;
		}
	}
	return meurt;
}

bool RegleCollision::valeurCase(int i,int j) const
{
	return m_matriceCollision[i][j];
}

bool RegleCollision::collision(int numSerpent, vector<int> couleurs Rencontrees) const
{
	bool reponse(false);
	for (int i(0); i<couleursRencontrees.size(); ++i)
	{
		if (m_matriceCollision[numSerpent][couleursRencontrees[i]])
		{
			reponse = true;
			break;
		}
	}
	return reponse;
}
















