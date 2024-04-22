#pragma once

#include <vector>
#include "Etat.h"
#include "Chronometre.h"

class ComparaisonF_n
{
public:
	bool operator() (Etat* a, Etat* b) const
	{
		return (b->obtenirF_n() < a->obtenirF_n()); // DESC
	}
};

class Solveur
{
public:

	Solveur();

	void resoudre(Etat* etatInitial, int nombreIterations = 1000, int seed = -1);

	bool termine;

	unsigned long long etatsGeneres;

	unsigned long long etatsChoisis;

	unsigned long long tempsSolutionMs;

	std::vector<Etat*> solution;

private:

	Chronometre chronometre;

	static Etat* Melanger(Etat* etatInitial, int nombreIterations, int seed);

	static std::vector<Etat*> ObtenirCoups(Etat* etatFinal);
};
