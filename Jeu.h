#pragma once

#include <SFML/Graphics.hpp>

#include "Etat.h"

class Jeu
{
public:

    Jeu(sf::RenderWindow& window, sf::Vector2u tailleFenetre, const sf::Color& bgColor = sf::Color::Black);

    /// <summary>
    /// Positionne les �l�ments de l'interface aux bons endroits, afin de repr�senter l'�tat fourni.
    /// </summary>
    /// <param name="etat">L'�tat qui doit �tre repr�sent� dans l'interface graphique.</param>
    virtual void update(Etat* etat) = 0;

    void update(Etat* etatPrecedent, Etat* etatCourant, float delta);

    /// <summary>
    /// Dessine les �l�ments de l'interface.
    /// </summary>
    virtual void draw() = 0;

    /// <summary>
    /// Dessine les �l�ments de l'interface de l'�tat courant, en consid�rant l'�tat pr�c�dent.
    /// </summary>
    /// <param name="etatPrecedent">L'�tat pr�c�dent.</param>
    /// <param name="etatCourant">L'�tat courant, qui doit �tre dessin�.</param>
    /// <remarks>
    /// Il n'est pas n�cessaire d'impl�menter cette m�thode.
    /// Elle peut �tre utilis�e au besoin pour ordonner visuellement (selon "l'axe des z") 
    /// les �l�ments de l'interface.
    /// </remarks>
    virtual void draw(Etat* etatPrecedent, Etat* etatCourant);

    /// <summary>
    /// Retourne l'�tat initial du jeu.
    /// </summary>
    /// <returns>L'�tat initial du jeu.</returns>
    /// <remarks>
    /// L'�tat initial n'a pas de parent.
    /// </remarks>
    virtual Etat* obtenirEtatInitial() = 0;

    /// <summary>
    /// Retourne une cha�ne qui repr�sente le titre (ou le nom) du jeu.
    /// </summary>
    /// <returns>Une cha�ne qui repr�sente le titre du jeu.</returns>
    virtual std::string obtenirTitre() = 0;

    const sf::Vector2u tailleFenetre;

    const sf::Color bgColor;

protected:

    /// <summary>
    /// Anime la diff�rence entre l'�tat pr�c�dent et l'�tat courant (i.e. le coup qui a �t� jou�).
    /// </summary>
    /// <param name="etatPrecedent">L'�tat pr�c�dent.</param>
    /// <param name="etatCourant">L'�tat courant, ayant �t� engendr� par un coup � partir de l'�tat pr�c�dent.</param>
    /// <param name="delta">
    /// Le pourcentage (dans l'intervalle [0,1]) qui varie automatiquement selon le temps.
    /// Une valeur de z�ro correspond � l'�tat pr�c�dent, et une valeur de un
    /// correspond � l'�tat courant ; toutes les valeurs interm�diaires repr�sentent
    /// l'interpolation entre les deux �tats.
    /// </param>
    /// <remarks>
    /// L'animation est facultative. Dans ce cas, laissez le bloc de code de la m�thode vide.
    /// </remarks>
    virtual void animate(Etat* etatPrecedent, Etat* etatCourant, float delta) = 0;

    /// <summary>
    /// Retourne une coordonn�e en (x,y) interm�diaire entre les coordonn�es de d�part et d'arriv�e fournies.
    /// </summary>
    /// <param name="depart">La coordonn�e de d�part.</param>
    /// <param name="arrivee">La coordonn�e d'arriv�e.</param>
    /// <param name="delta">Le pourcentage (dans l'intervalle [0,1]) qui varie automatiquement selon le temps.</param>
    /// <returns>Une coordonn�e en (x,y) interm�diaire correspondant au delta fourni.</returns>
    /// <remarks>
    /// Cette m�thode peut �tre utilis�e pour faciliter l'animation.
    /// </remarks>
    sf::Vector2f interpolation(sf::Vector2f depart, sf::Vector2f arrivee, float delta);

    sf::RenderWindow& window;
};
