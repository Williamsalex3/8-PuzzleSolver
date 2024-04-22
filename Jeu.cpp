#include "Jeu.h"

Jeu::Jeu(sf::RenderWindow& window, sf::Vector2u tailleFenetre, const sf::Color& bgColor)
    : window(window), tailleFenetre(tailleFenetre), bgColor(bgColor)
{
}

void Jeu::update(Etat* etatPrecedent, Etat* etatCourant, float delta)
{
    this->update(etatCourant);

    this->animate(etatPrecedent, etatCourant, delta);
}

void Jeu::draw(Etat* etatPrecedent, Etat* etatCourant)
{
    this->draw();
}

sf::Vector2f Jeu::interpolation(sf::Vector2f depart, sf::Vector2f arrivee, float delta)
{
    return {
        depart.x + (arrivee.x - depart.x) * delta,
        depart.y + (arrivee.y - depart.y) * delta
    };
}
