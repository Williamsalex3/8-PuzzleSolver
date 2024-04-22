#pragma once

#include <SFML/Graphics.hpp>

#include "Etat.h"
#include "Jeu.h"
#include "Solveur.h"

constexpr float TempsSolutionMs = 15000.0f;

enum class EtatSolution
{
	ANIMATION,
	DELAI,
};

class Solution
{
public:

	Solution(Solveur& solveur, Jeu* jeu);

	void update();

	void draw();

	int obtenirNombreCourant() const;

	int obtenirNombreTotal() const;

private:

	Solveur& solveur;

	int indiceEtatCourant;

	Jeu* jeu;

	sf::Clock clock;

	EtatSolution etatSolution;

	const int tempsAnimationMs;

	const int tempsDelaiMs;
};
