#include "Etat.h"

std::string Etat::obtenirCle()
{
	if (this->_cle.empty())
	{
		this->_cle = this->doObtenirCle();

		assert(!this->_cle.empty());
	}

	return this->_cle;
}

bool Etat::estFinal()
{
	if (this->_estFinal != 0 && this->_estFinal != 1)
	{
		this->_estFinal = this->doEstFinal() ? 1 : 0;
	}

	return this->_estFinal;
}

double Etat::obtenirF_n()
{
	static constexpr bool utiliserNiveau = false;

	static constexpr bool utiliserF_h = true;

	return
		(utiliserNiveau ? this->niveau : 0)
		+
		(utiliserF_h ? this->obtenirF_h() : 0)
		;
}

double Etat::obtenirF_h()
{
	if (this->_f_h == std::numeric_limits<double>::min())
	{
		this->_f_h = this->doObtenirF_h();
	}

	return this->_f_h;
}

Etat::Etat()
	: Etat(nullptr)
{
}

Etat::Etat(Etat* parent)
	: _estFinal(-1),
	_f_h(std::numeric_limits<double>::min()),
	niveau(parent == nullptr ? 0 : parent->niveau + 1),
	parent(parent)
{
}
