#include "Solveur.h"

#include <random>
#include <cassert>
#include <queue>
#include <unordered_map>

void Solveur::resoudre(Etat* etatInitial, int nombreIterations, int seed)
{
	this->termine = false;

	this->etatsGeneres = 0;

	this->etatsChoisis = 0;

	this->tempsSolutionMs = 0;

	this->solution.clear();

	if (etatInitial->estFinal())
	{
		etatInitial = Melanger(etatInitial, nombreIterations, seed);
	}

	etatInitial->parent = nullptr;

	std::priority_queue<Etat*, std::vector<Etat*>, ComparaisonF_n> OPEN;

	std::unordered_map<std::string, Etat*> OPEN_map;

	std::unordered_map<std::string, Etat*> CLOSED;
	
	this->chronometre.demarrer();

	OPEN.push(etatInitial);

	OPEN_map[etatInitial->obtenirCle()] = etatInitial;

	while (!OPEN.empty())
	{
		Etat* courant = OPEN.top();
		OPEN.pop();

		OPEN_map.erase(courant->obtenirCle());

		this->etatsChoisis++;

		double tempsNs = this->chronometre.ecouleNs();

		this->tempsSolutionMs = (unsigned long long)(tempsNs / 1000.0 / 1000.0);

		if (courant->estFinal())
		{
			this->solution = ObtenirCoups(courant);

			this->chronometre.arreter();

			break;
		}

		if (CLOSED.find(courant->obtenirCle()) == CLOSED.end())
		{
			CLOSED[courant->obtenirCle()] = courant;
		}

		for (Etat* coupPossible : courant->coupsPossibles())
		{
			if (
				OPEN_map.find(coupPossible->obtenirCle()) == OPEN_map.end()
				&& CLOSED.find(coupPossible->obtenirCle()) == CLOSED.end()
				)
			{
				OPEN.push(coupPossible);
				
				OPEN_map[coupPossible->obtenirCle()] = coupPossible;

				this->etatsGeneres++;
			}
		}
	}

	assert(!this->solution.empty());

	this->termine = true;
}

Solveur::Solveur()
{
	this->termine = false;

	this->etatsGeneres = 0;

	this->etatsChoisis = 0;

	this->tempsSolutionMs = 0;
}

Etat* Solveur::Melanger(Etat* etatInitial, int nombreIterations, int _seed)
{
	unsigned int seed = (unsigned int)(
		_seed > -1 
		? _seed 
		: std::chrono::system_clock::now().time_since_epoch().count()
	);

	std::minstd_rand0 rand(seed);

	Etat* courant = etatInitial;

	for (int i = 0; i < nombreIterations; i++)
	{
		std::vector<Etat*> coupsPossibles = courant->coupsPossibles();

		assert(coupsPossibles.size() > 0);

		int r = rand() % coupsPossibles.size();

		courant = coupsPossibles[r];
	}

	return courant;
}

std::vector<Etat*> Solveur::ObtenirCoups(Etat* etatFinal)
{
	std::vector<Etat*> resultat;

	Etat* curseur = etatFinal;

	while (curseur != nullptr)
	{
		resultat.push_back(curseur);

		curseur = curseur->parent;
	}

	std::reverse(resultat.begin(), resultat.end());

	return resultat;
}
