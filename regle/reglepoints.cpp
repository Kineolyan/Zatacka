#include "reglepoints.h"

using namespace std;

vector< vector<int> > matriceGainsStandard()
{
	vector<int> ligne(6,1);
	vector< vector<int> > matrice(6,ligne);
	for (int i(0); i<6; i++)
	{
		for (int j(0); j<6;j++)
		{
			if (i == j)
			{
				matrice[i][j]=0;
			}
		}
	}
	return matrice;
}

ReglePoints::ReglePoints():m_matriceGains(matriceGainsStandard())
{
}

ReglePoints::ReglePoints(vector< vector<int> > matriceGains):m_matriceGains(matriceGains)
{
}

ReglePoints::ReglePoints(vector<ReglePoints> regles)
{
	m_matriceGains = matriceGainsStandard();
	for (int i(0); i<6; i++)
	{
		for (int j(0); j<6;j++)
		{
			for (double k(0); k<regles.size();k++)
			{
				m_matriceGains[i][j]*=regles[k].valeurCase(i,j);
			}
		}
	}
}

int ReglePoints::valeurCase(int i,int j) const
{
	return m_matriceGains[i][j];
}

vector<int> ReglePoints::attribuePointsA(int numSerpentMourrant) const
{
	return m_matriceGains[numSerpentMourrant];
}

