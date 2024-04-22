#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <limits>
#include <iostream>
#include <iomanip>

class Etat
{
	friend class Solveur;

public:

	/// <summary>
	/// Retourne les coups possibles � partir de l'�tat courant.
	/// </summary>
	/// <returns>Les coups qu'il est possible de jouer � partir de l'�tat courant.</returns>
	/// <remarks>
	/// Le constructeur Etat(Etat* parent) doit �tre utilis� pour cr�er les nouveaux �tats.
	/// </remarks>
	virtual std::vector<Etat*> coupsPossibles() const = 0;

	std::string obtenirCle();

	bool estFinal();

	double obtenirF_n();

	/// <summary>
	/// Affiche l'�tat courant dans la console.
	/// </summary>
	/// <remarks>
	/// Vous n'avez pas besoin d'impl�menter cette m�thode si vous utilisez SFML.
	/// Dans ce cas, laissez le bloc de code de la m�thode vide.
	/// </remarks>
	virtual void afficher() = 0;

protected:

	/// <summary>
	/// Votre constructeur qui ne prend pas de param�tres doit appeler celui-ci.
	/// </summary>
	Etat();

	/// <summary>
	/// Votre constructeur qui prend un pointeur parent doit appeler celui-ci.
	/// </summary>
	Etat(Etat* parent);

	/// <summary>
	/// Retourne une repr�sentation textuelle de l'�tat.
	/// </summary>
	/// <returns>Une repr�sentation textuelle de l'�tat.</returns>
	/// <remarks>
	/// Vous devez utiliser un std::stringstream pour la g�n�rer.
	/// </remarks>
	virtual std::string doObtenirCle() const = 0;

	/// <summary>
	/// Retourne true ssi l'�tat est un �tat final.
	/// </summary>
	/// <returns>Retourne true si l'�tat est un �tat final, false sinon.</returns>
	virtual bool doEstFinal() const = 0;

	/// <summary>
	/// Retourne la valeur de la fonction heuristique pour cet �tat.
	/// </summary>
	/// <returns>La valeur de la fonction heuristique pour cet �tat.</returns>
	/// <remarks>
	/// Votre valeur sera probablement une valeur enti�re (e.g. int)
	/// et non une valeur r�elle (double).
	/// </remarks>
	virtual double doObtenirF_h() const = 0;

private:

	double obtenirF_h();

	std::string _cle;

	int _estFinal;

	double _f_h;

	const int niveau;

	Etat* parent;

};
