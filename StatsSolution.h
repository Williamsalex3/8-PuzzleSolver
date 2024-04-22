#pragma once

#include <SFML/Graphics.hpp>

#include "Solution.h"

class StatsSolution
{

public:

    StatsSolution(sf::RenderWindow& window, Solution* solution, float x, float y);

    void update();

    void draw();

private:

    sf::RenderWindow& window;

    Solution* solution;

    sf::Font font;

    sf::Text solutionText;
};
