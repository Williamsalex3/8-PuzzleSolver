#include "Puzzle8.h"

Puzzle8::Puzzle8() :Etat()
{
}

Puzzle8::Puzzle8(Puzzle8* pere) :Etat(pere)
{
	//Copie de la matrice du père
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			this->mat[i][j] = pere->mat[i][j];
		}
	}
}

const std::vector<std::vector<int>>& Puzzle8::getMat() const
{
	return this->mat;
}

std::vector<Etat*> Puzzle8::coupsPossibles() const
{
	std::vector<Etat*> coups;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (this->mat[i][j] == 0)
			{
				if (i > 0)//on peut échanger la case vide avec la case au dessus
				{
					Puzzle8* p = new Puzzle8((Puzzle8*)this);
					//Nouveau coup pour la liste des coups possibles avec l'état actuel comme parent
					p->mat[i][j] = p->mat[i - 1][j];//remplacer la case vide par la valeur de la case au dessus

					p->setCaseBouger(p->mat[i - 1][j]);//Donner le numero de la case bougée

					p->mat[i - 1][j] = 0;//mettre la case au dessus à 0
					coups.push_back(p);//ajouter le coup à la liste des coups possibles

				}
				if (i < this->size - 1)//on peut échanger la case vide avec la case en dessous
				{
					Puzzle8* p = new Puzzle8((Puzzle8*)this);
					p->mat[i][j] = p->mat[i + 1][j];

					p->setCaseBouger(p->mat[i + 1][j]);
					
					p->mat[i + 1][j] = 0;
					coups.push_back(p);

				}
				if (j > 0)//on peut échanger la case vide avec la case à gauche
				{
					Puzzle8* p = new Puzzle8((Puzzle8*)this);
					p->mat[i][j] = p->mat[i][j - 1];
					p->setCaseBouger(p->mat[i][j - 1]);
					p->mat[i][j - 1] = 0;
					coups.push_back(p);
				}
				if (j < this->size - 1)//on peut échanger la case vide avec la case à droite
				{
					Puzzle8* p = new Puzzle8((Puzzle8*)this);
					p->mat[i][j] = p->mat[i][j + 1];
					p->setCaseBouger(p->mat[i][j + 1]);
					p->mat[i][j + 1] = 0;
					coups.push_back(p);
				}
			}
		}
	}
	return coups;
}

void Puzzle8::setCaseBouger(int indice)
{
		this->CaseBouger = indice;
}

int Puzzle8::getCaseBouger()
{
	 return this->CaseBouger;
}
void Puzzle8::afficher()//Pas utilisé avec SFML
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << this->mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
std::string Puzzle8::doObtenirCle() const
{
	//On prend chaque valeur de la matrice et on les concatène pour obtenir une clé unique
	std::string cle = "";
	std::stringstream s;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			s << this->mat[i][j];
		}
	}
	cle = s.str();

	return cle;
}
bool Puzzle8::doEstFinal() const
{
	int val = 1;
	for (int i = 0; i < this->size; i++)//parcourir toutes les indices de la matrice et vérifier si les valeurs sont dans l'ordre
	{
		for (int j = 0; j < this->size; j++)
		{
			if (i == this->size - 1 && j == this->size - 1)//Si on est à la dernière case, on vérifie si elle est vide
			{
				if (this->mat[i][j] != 0)
				{
					return false;
				}
			}
			else if (this->mat[i][j] != val)//Si la valeur n'est pas celle attendue, on retourne faux
			{
				return false;
			}
			val++;
		}
	}
	return true;
}
double Puzzle8::doObtenirF_h() const
{
	//Calcul de la distance de Manhattan
	double distance = 0.0;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)//Parcourir toutes les indices de la matrice
		{
			int valeur = this->mat[i][j];
			if (valeur != 0)//Si la case n'est pas vide
			{
				int ligneVoulue = (valeur - 1) / this->size;//indice de la en état final
				int colonneVoulue = (valeur - 1) % this->size;//indice de la colonne en état final
				distance += abs(ligneVoulue - i) + abs(colonneVoulue - j);
			}
		}
	}
	return distance;
}
