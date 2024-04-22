#pragma once

#include <SFML/Graphics.hpp>

#include "Etat.h"

class Jeu
{
public:

    Jeu(sf::RenderWindow& window, sf::Vector2u tailleFenetre, const sf::Color& bgColor = sf::Color::Black);

    /// <summary>
    /// Positionne les éléments de l'interface aux bons endroits, afin de représenter l'état fourni.
    /// </summary>
    /// <param name="etat">L'état qui doit être représenté dans l'interface graphique.</param>
    virtual void update(Etat* etat) = 0;

    void update(Etat* etatPrecedent, Etat* etatCourant, float delta);

    /// <summary>
    /// Dessine les éléments de l'interface.
    /// </summary>
    virtual void draw() = 0;

    /// <summary>
    /// Dessine les éléments de l'interface de l'état courant, en considérant l'état précédent.
    /// </summary>
    /// <param name="etatPrecedent">L'état précédent.</param>
    /// <param name="etatCourant">L'état courant, qui doit être dessiné.</param>
    /// <remarks>
    /// Il n'est pas nécessaire d'implémenter cette méthode.
    /// Elle peut être utilisée au besoin pour ordonner visuellement (selon "l'axe des z") 
    /// les éléments de l'interface.
    /// </remarks>
    virtual void draw(Etat* etatPrecedent, Etat* etatCourant);

    /// <summary>
    /// Retourne l'état initial du jeu.
    /// </summary>
    /// <returns>L'état initial du jeu.</returns>
    /// <remarks>
    /// L'état initial n'a pas de parent.
    /// </remarks>
    virtual Etat* obtenirEtatInitial() = 0;

    /// <summary>
    /// Retourne une chaîne qui représente le titre (ou le nom) du jeu.
    /// </summary>
    /// <returns>Une chaîne qui représente le titre du jeu.</returns>
    virtual std::string obtenirTitre() = 0;

    const sf::Vector2u tailleFenetre;

    const sf::Color bgColor;

protected:

    /// <summary>
    /// Anime la différence entre l'état précédent et l'état courant (i.e. le coup qui a été joué).
    /// </summary>
    /// <param name="etatPrecedent">L'état précédent.</param>
    /// <param name="etatCourant">L'état courant, ayant été engendré par un coup à partir de l'état précédent.</param>
    /// <param name="delta">
    /// Le pourcentage (dans l'intervalle [0,1]) qui varie automatiquement selon le temps.
    /// Une valeur de zéro correspond à l'état précédent, et une valeur de un
    /// correspond à l'état courant ; toutes les valeurs intermédiaires représentent
    /// l'interpolation entre les deux états.
    /// </param>
    /// <remarks>
    /// L'animation est facultative. Dans ce cas, laissez le bloc de code de la méthode vide.
    /// </remarks>
    virtual void animate(Etat* etatPrecedent, Etat* etatCourant, float delta) = 0;

    /// <summary>
    /// Retourne une coordonnée en (x,y) intermédiaire entre les coordonnées de départ et d'arrivée fournies.
    /// </summary>
    /// <param name="depart">La coordonnée de départ.</param>
    /// <param name="arrivee">La coordonnée d'arrivée.</param>
    /// <param name="delta">Le pourcentage (dans l'intervalle [0,1]) qui varie automatiquement selon le temps.</param>
    /// <returns>Une coordonnée en (x,y) intermédiaire correspondant au delta fourni.</returns>
    /// <remarks>
    /// Cette méthode peut être utilisée pour faciliter l'animation.
    /// </remarks>
    sf::Vector2f interpolation(sf::Vector2f depart, sf::Vector2f arrivee, float delta);

    sf::RenderWindow& window;
};
