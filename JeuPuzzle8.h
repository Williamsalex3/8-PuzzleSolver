#pragma once

#include <SFML/Graphics.hpp>

#include "Jeu.h"

class JeuPuzzle8 : public Jeu
{
public:
    JeuPuzzle8(sf::RenderWindow& window, sf::Vector2u tailleFenetre, const sf::Color& bgColor = sf::Color::Black);;
    virtual void update(Etat* etat) override;

    virtual void draw() override;
   
    virtual void draw(Etat* etatPrecedent, Etat* etatCourant) override;
    
    virtual Etat* obtenirEtatInitial() override;
   
    virtual std::string obtenirTitre() override;

protected:
    
    virtual void animate(Etat* etatPrecedent, Etat* etatCourant, float delta) override;

private:
    sf::Texture texture;
    std::vector<sf::Sprite> sprites;//Pour entretenir les pièces du puzzle
};
