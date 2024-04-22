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
	/// Retourne les coups possibles à partir de l'état courant.
	/// </summary>
	/// <returns>Les coups qu'il est possible de jouer à partir de l'état courant.</returns>
	/// <remarks>
	/// Le constructeur Etat(Etat* parent) doit être utilisé pour créer les nouveaux états.
	/// </remarks>
	virtual std::vector<Etat*> coupsPossibles() const = 0;

	std::string obtenirCle();

	bool estFinal();

	double obtenirF_n();

	/// <summary>
	/// Affiche l'état courant dans la console.
	/// </summary>
	/// <remarks>
	/// Vous n'avez pas besoin d'implémenter cette méthode si vous utilisez SFML.
	/// Dans ce cas, laissez le bloc de code de la méthode vide.
	/// </remarks>
	virtual void afficher() = 0;

protected:

	/// <summary>
	/// Votre constructeur qui ne prend pas de paramètres doit appeler celui-ci.
	/// </summary>
	Etat();

	/// <summary>
	/// Votre constructeur qui prend un pointeur parent doit appeler celui-ci.
	/// </summary>
	Etat(Etat* parent);

	/// <summary>
	/// Retourne une représentation textuelle de l'état.
	/// </summary>
	/// <returns>Une représentation textuelle de l'état.</returns>
	/// <remarks>
	/// Vous devez utiliser un std::stringstream pour la générer.
	/// </remarks>
	virtual std::string doObtenirCle() const = 0;

	/// <summary>
	/// Retourne true ssi l'état est un état final.
	/// </summary>
	/// <returns>Retourne true si l'état est un état final, false sinon.</returns>
	virtual bool doEstFinal() const = 0;

	/// <summary>
	/// Retourne la valeur de la fonction heuristique pour cet état.
	/// </summary>
	/// <returns>La valeur de la fonction heuristique pour cet état.</returns>
	/// <remarks>
	/// Votre valeur sera probablement une valeur entière (e.g. int)
	/// et non une valeur réelle (double).
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
