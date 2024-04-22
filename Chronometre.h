#pragma once

#include <chrono>
#include <stdexcept>

class Chronometre
{
public:

	Chronometre()
		: actif(false)
	{}

	void demarrer()
	{
		this->actif = true;

		this->tempsDebut = std::chrono::high_resolution_clock::now();
	}

	double arreter()
	{
		if (!this->actif)
		{
			throw std::runtime_error("Chronometre inactif");
		}

		std::chrono::time_point<std::chrono::high_resolution_clock> tempsFin = std::chrono::high_resolution_clock::now();

		this->actif = false;

		return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(tempsFin - this->tempsDebut).count();
	}

	double ecouleNs() const
	{
		if (!this->actif)
		{
			throw std::runtime_error("Chronometre inactif");
		}

		std::chrono::time_point<std::chrono::high_resolution_clock> tempsFin = std::chrono::high_resolution_clock::now();

		return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(tempsFin - this->tempsDebut).count();
	}

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> tempsDebut;

	bool actif;
};
