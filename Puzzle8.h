/*
	NOMS DES MEMBRES DE L'�QUIPE:
	Alexandre Williams Alseny Diallo

	BR�VE DESCRIPTION DU DEVOIR
	Ce devoir vise � impl�menter un programme complet qui applique les strat�gies de recherche
	vues en classe, afin de trouver la solution � un jeu d�terministe � un seul joueur.
*/

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "Etat.h"

class Puzzle8 : public Etat
{
public:
	Puzzle8();
	Puzzle8(Puzzle8* pere);
	const std::vector<std::vector<int>>& getMat() const;
	std::vector<Etat*> coupsPossibles() const override;
	
	int getCaseBouger();
	void afficher() override;

protected:

	std::string doObtenirCle() const override;

	bool doEstFinal() const override;

	double doObtenirF_h() const override;

private:
	const int size = 3;
	std::vector<std::vector<int>> mat = { {1,2,3},{4,5,6},{7,8,0} };//0 repr�sente la case vide
	int CaseBouger = -1;//numero de la case qui a remplac� la case vide
	void setCaseBouger(int indice);
};
