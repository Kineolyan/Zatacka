#include "reglecollision.h"

using namespace std;

RegleCollision::RegleCollision():
	m_matriceCollision(matriceCollisionsStandard())
{

}

RegleCollision::RegleCollision(vector< vector<bool> > matriceCollision):
	m_matriceCollision(matriceCollision)
{

}

RegleCollision::RegleCollision(vector<RegleCollision> regles):
	m_matriceCollision(matriceCollisionsStandard())
{
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

vector< vector<bool> > RegleCollision::matriceCollisionsStandard()
{
	vector<bool> ligne(6,true);
	vector< vector<bool> > matrice(6,ligne);
	return matrice;
}

bool RegleCollision::valeurCase(int i,int j) const
{
	return m_matriceCollision[i][j];
}

bool RegleCollision::collision(Couleur serpent,
		const vector<Couleur>& joueursRencontres) const {
	for (int i =0, end =joueursRencontres.size(); i<end; ++i)
	{
		switch(joueursRencontres[i]) {
		case NOIR:
			break;

		case GRIS:
		case BLANC:
			return true;

		default:
			if (m_matriceCollision[serpent][joueursRencontres[i]]) {
				return true;
			}
		}
	}

	return false;
}
















