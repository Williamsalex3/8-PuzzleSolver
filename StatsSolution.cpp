#include "StatsSolution.h"

StatsSolution::StatsSolution(sf::RenderWindow& window, Solution* solution, float x, float y)
    : window(window), solution(solution)
{
    this->font.loadFromFile("fonts/OCRAEXT.TTF");

    this->solutionText.setFont(font);
    this->solutionText.setCharacterSize(20);
    this->solutionText.setPosition(x, y);

    this->solutionText.setFillColor(sf::Color::Yellow);
    this->solutionText.setOutlineColor(sf::Color::Black);
    this->solutionText.setOutlineThickness(1.0f);
}

void StatsSolution::update()
{
    this->solutionText.setString(
        "Solution: " 
        + std::to_string(this->solution->obtenirNombreCourant()) 
        + " / "
        + std::to_string(this->solution->obtenirNombreTotal())
    );
}

void StatsSolution::draw()
{
    this->window.draw(this->solutionText);
}
