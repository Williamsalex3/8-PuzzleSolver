#include <SFML/Graphics.hpp>

#include <vector>
#include <thread>

#include "JeuPuzzle8.h"

#include "Solveur.h"
#include "StatsSolveur.h"

#include "Solution.h"
#include "StatsSolution.h"

int main()
{
    sf::RenderWindow window;

    /*window.setFramerateLimit(60);*/
    window.setFramerateLimit(5);
    sf::Vector2u tailleFenetre(756,756);
    const sf::Color& bgColor = sf::Color::Black;
    Jeu* jeu = new JeuPuzzle8(window,tailleFenetre, bgColor);

    window.create(
        sf::VideoMode(jeu->tailleFenetre.x, jeu->tailleFenetre.y), 
        "INFO3212 - Devoir 3 - " + jeu->obtenirTitre()
    );

    sf::View view(window.getDefaultView());

    view.setCenter(sf::Vector2f(jeu->tailleFenetre / 2u));

    Solveur solveur;

    std::thread t(&Solveur::resoudre, &solveur, jeu->obtenirEtatInitial(), 300, -1);

    t.detach();

    StatsSolveur statsSolveur(window, solveur, 10, 10);

    Solution* solution = nullptr;

    StatsSolution* statsSolution = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (solveur.termine && solution == nullptr)
        {
            solution = new Solution(solveur, jeu);

            statsSolution = new StatsSolution(window, solution, 10, 100);
        }

        statsSolveur.update();

        if (solution != nullptr)
        {
            solution->update();

            statsSolution->update();
        }
    
        window.clear(jeu->bgColor);

        if (solution != nullptr)
        {
            solution->draw();

            statsSolution->draw();
        }
        
        statsSolveur.draw();

        window.display();
    }

    return 0;
}
