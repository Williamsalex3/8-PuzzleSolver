#include "Solution.h"

#include <cassert>
#include <stdexcept>

Solution::Solution(Solveur& solveur, Jeu* jeu)
	: solveur(solveur),
	jeu(jeu),
	etatSolution(EtatSolution::ANIMATION),
	tempsAnimationMs((int)(TempsSolutionMs / solveur.solution.size() / 6 * 5)),
	tempsDelaiMs((int)(TempsSolutionMs / solveur.solution.size() / 6))
{
	assert(!solveur.solution.empty());

	if (solveur.solution.size() > 1)
	{
		this->indiceEtatCourant = 1;
	}
	else
	{
		this->indiceEtatCourant = 0;
	}	
}

void Solution::update()
{
	if (this->solveur.solution.size() == 1)
	{
		this->jeu->update(this->solveur.solution[this->indiceEtatCourant]);

		return;
	}

	sf::Int32 elapsedMs = this->clock.getElapsedTime().asMilliseconds();

	if (this->etatSolution == EtatSolution::DELAI)
	{
		this->jeu->update(
			this->solveur.solution[this->indiceEtatCourant - 1],
			this->solveur.solution[this->indiceEtatCourant],
			1.0f
		);

		if (elapsedMs > this->tempsDelaiMs)
		{
			if (this->indiceEtatCourant + 1 < this->solveur.solution.size())
			{
				this->indiceEtatCourant++;

				this->etatSolution = EtatSolution::ANIMATION;
				this->clock.restart();
			}
		}
	}
	else if (this->etatSolution == EtatSolution::ANIMATION)
	{
		if (elapsedMs > this->tempsAnimationMs)
		{
			this->etatSolution = EtatSolution::DELAI;
			this->clock.restart();
		}
		else
		{
			this->jeu->update(
				this->solveur.solution[this->indiceEtatCourant - 1],
				this->solveur.solution[this->indiceEtatCourant],
				(float)elapsedMs / this->tempsAnimationMs
			);
		}
	}
	else
	{
		throw std::runtime_error("Etat inconnu");
	}
}

void Solution::draw()
{
	if (this->solveur.solution.size() == 1)
	{
		this->jeu->draw();
	}
	else
	{
		this->jeu->draw(
			this->solveur.solution[this->indiceEtatCourant - 1],
			this->solveur.solution[this->indiceEtatCourant]
		);
	}
}

int Solution::obtenirNombreCourant() const
{
	return this->indiceEtatCourant;
}

int Solution::obtenirNombreTotal() const
{
	return (int)this->solveur.solution.size() - 1;
}
