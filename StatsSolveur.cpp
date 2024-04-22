#include "StatsSolveur.h"

#include <sstream>
#include <iomanip>

StatsSolveur::StatsSolveur(sf::RenderWindow& window, Solveur& solveur, float x, float y)
    : window(window), solveur(solveur)
{
    this->font.loadFromFile("fonts/OCRAEXT.TTF");

    this->generesText.setFont(font);
    this->generesText.setCharacterSize(20);
    this->generesText.setPosition(x, y);

    this->choisisText.setFont(font);
    this->choisisText.setCharacterSize(20);
    this->choisisText.setPosition(x, y + 30);

    this->tempsSolutionMsText.setFont(font);
    this->tempsSolutionMsText.setCharacterSize(20);
    this->tempsSolutionMsText.setPosition(x, y + 60);

    this->generesText.setFillColor(sf::Color::Yellow);
    this->generesText.setOutlineColor(sf::Color::Black);
    this->generesText.setOutlineThickness(1.0f);

    this->choisisText.setFillColor(sf::Color::Yellow);
    this->choisisText.setOutlineColor(sf::Color::Black);
    this->choisisText.setOutlineThickness(1.0f);

    this->tempsSolutionMsText.setFillColor(sf::Color::Yellow);
    this->tempsSolutionMsText.setOutlineColor(sf::Color::Black);
    this->tempsSolutionMsText.setOutlineThickness(1.0f);
}

void StatsSolveur::update()
{
    this->generesText.setString("États générés:  " + std::to_string(this->solveur.etatsGeneres));

    this->choisisText.setString("États choisis:  " + std::to_string(this->solveur.etatsChoisis));

    unsigned long long tempsSolutionMs = this->solveur.tempsSolutionMs;

    std::stringstream out;

    out << "Temps solution: "
        << std::fixed << std::setprecision(tempsSolutionMs >= 1000 ? 3 : 0)
        << (tempsSolutionMs / (tempsSolutionMs >= 1000 ? 1000.0 : 1.0))
        << (tempsSolutionMs >= 1000 ? " s" : " ms")
        ;

    this->tempsSolutionMsText.setString(out.str());
}

void StatsSolveur::draw()
{
    this->window.draw(this->generesText);

    this->window.draw(this->choisisText);

    this->window.draw(this->tempsSolutionMsText);
}
