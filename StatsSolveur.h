#pragma once

#include <SFML/Graphics.hpp>

#include "Solveur.h"

class StatsSolveur
{

public:

    StatsSolveur(sf::RenderWindow& window, Solveur& solveur, float x, float y);

    void update();

    void draw();

private:

    sf::RenderWindow& window;

    Solveur& solveur;

    sf::Font font;

    sf::Text generesText;

    sf::Text choisisText;

    sf::Text tempsSolutionMsText;
};
