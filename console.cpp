#include <iostream>

#include "EtatDevoir.h"

#include "Solveur.h"

int main()
{
	Etat* etatInitial = ::EtatInitial(3);

	Solveur solveur;

	solveur.resoudre(etatInitial, 300);

	for (Etat* etat : solveur.solution)
	{
		etat->afficher();
	}

	return 0;
}
