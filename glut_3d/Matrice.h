//#define


#ifndef MATRICE_H
#define MATRICE_H
typedef struct Matrice Matrice;

struct Matrice
{
	int lgn,col;
	double ** mat;
};

Matrice* newMatrice(int ligne, int col);
void deleteMatrice(Matrice*);

Matrice* ToMatrice(double * tab);

void showMatrice(Matrice*);

Matrice* matProduit(Matrice*,Matrice*);
Matrice* matProduitScalaire(double a,Matrice* m1);
Matrice* matSomme(Matrice*,Matrice*);
Matrice* matInv(Matrice*);
double matTrace(Matrice*);

#endif