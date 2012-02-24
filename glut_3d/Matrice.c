#include <math.h>
#include <stdlib.h>
#include "Matrice.h"

Matrice* newMatrice(int ligne, int col)
{
	Matrice * m;
	int i,j;
	m = (Matrice*)malloc(sizeof(Matrice));
	m->lgn = ligne;
	m->col = col;
	m->mat = (double**)malloc(sizeof(double*) * ligne);
	for(i = 0; i < ligne; i++)
		m->mat[i] = (double*)malloc(sizeof(double)*col);

	for(i = 0; i < ligne; i++)
		for(j = 0; j < col; j++)
			m->mat[i][j] = i == j ? 0.0f : 0.0f;

	return m;
}

void deleteMatrice(Matrice* m)
{
	int i;
	if(!m)
		return;

	for(i = 0; i < m->lgn; i++)
		free(m->mat[i]);
	free(m->mat);
	free(m);
}

Matrice* ToMatrice(double * tab)
{
	//Only for Matrix 4x4
	int i, j;
	Matrice * mat = newMatrice(4,4);

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			mat->mat[i][j] = tab[i*4+j];
		}
	}
	return mat;
}

Matrice* matProduit(Matrice* m1, Matrice* m2)
{

	Matrice * m;
	int i,j,k;
	if(m1->col != m2->lgn)
		return NULL;

	m = newMatrice(m1->lgn,m2->col);

	for(i = 0; i < m->lgn; i++)
		for(j = 0; j < m->col; j++)
			for(k = 0; k < m1->col; k++)
				m->mat[i][j] += m1->mat[i][k]*m2->mat[k][j];

	return m;
}

Matrice* matProduitScalaire(double a,Matrice* m1)
{

	Matrice * m;
	int i,j;

	if(!m1)
		return NULL;

	m = newMatrice(m1->lgn,m1->col);

	for(i = 0; i < m1->lgn; i++)
		for(j = 0; j < m1->col; j++)
			m->mat[i][j] = a*m1->mat[i][j];

	return m;
}

Matrice* matSomme(Matrice* m1,Matrice* m2)
{
	Matrice * m;
	int i,j;

	if(!m1 || !m2)
		return NULL;

	if(m1->col != m2->col || m1->lgn != m2->col)
		return NULL;

	m = newMatrice(m1->lgn,m1->col);

	for(i = 0; i < m1->lgn; i++)
		for(j = 0; j < m1->col; j++)
			m->mat[i][j] = m1->mat[i][j] + m2->mat[i][j];

	return m;
}

double matTrace(Matrice* m)
{
	double somme = 0.0f;
	int i,j;
	if(m->col != m->lgn)
		return somme;

	for(i = 0; i < m->lgn; i++)
		somme += m->mat[i][i];

	return somme;
}

void showMatrice(Matrice* m)
{
	int i,j;
	for(i = 0; i < m->lgn; i++)
	{
		printf("|");
		for(j = 0; j < m->col; j++)
		{
			printf(" %f", m->mat[i][j]);
		}
		printf(" |\n");
	}
	printf("\n");
}
