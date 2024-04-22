#include "JeuPuzzle8.h"
#include "Puzzle8.h"
JeuPuzzle8::JeuPuzzle8(sf::RenderWindow& window, sf::Vector2u tailleFenetre, const sf::Color& bgColor)
    :Jeu(window,  tailleFenetre, bgColor)//Fonctionne bien avec sf::Vector2u tailleFenetre(756, 756);
{
    if (!texture.loadFromFile("image.jpg"))//Charger l'image
    {
		throw std::runtime_error("Impossible de charger l'image");
	}
    sf::Vector2u imageSize = texture.getSize();//Obtenir la taille de l'image
    sf::Vector2u tileSize(imageSize.x / 3, imageSize.y / 3);//Obtenir la taille de chaque pi�ce du puzzle
    for (unsigned int i = 0; i < 3; ++i) 
    {
        for (unsigned int j = 0; j < 3; ++j)//pour chaque pi�ce du puzzle on assigne une portion de la texture au sprite
        {
            sf::IntRect textureRect(i * tileSize.x, j * tileSize.y, tileSize.x, tileSize.y);
            sf::Sprite sprite(texture, textureRect);
            sprite.setPosition(i * tileSize.x, j * tileSize.y );
            sprite.setTexture(texture);
            sprites.push_back(sprite);
        }
    }
}
void JeuPuzzle8::update(Etat* _etat)
{
    Puzzle8* etat = dynamic_cast<Puzzle8*>(_etat);

    // R�cup�rer la taille de l'image et des pi�ces
    sf::Vector2u imageSize = texture.getSize();
    sf::Vector2u tileSize(imageSize.x / 3, imageSize.y / 3);
    const auto& mat = etat->getMat();//r�cup�rer la matrice de l'�tat

    for (int i = 0; i < 3; i++)//pour chaque pi�ce du puzzle on assigne une position dans l'image
    {
        for (int j = 0; j < 3; j++)
        {
            int spriteIndex = mat[i][j];
            if (mat[i][j] == 0)//Cas sp�cial puisque la case vide est le dernier sprite (l'indice de la case vide ne correspond pas � l'incr�mentation de spriteIndex)
            {
                sprites[sprites.size()-1].setPosition(i * tileSize.x, j * tileSize.y);
            }
            else
            {
                sprites[spriteIndex - 1].setPosition(i * tileSize.x, j * tileSize.y);
            }
        }
    }
}

void JeuPuzzle8::draw()
{
    //afficher les sprites
    for (const auto& sprite : sprites) 
    {
        this->window.draw(sprite);
    }
    
}

void JeuPuzzle8::draw(Etat* _etatPrecedent, Etat* _etatCourant)
{
    Puzzle8* etatPrecedent = dynamic_cast<Puzzle8*>(_etatPrecedent);

    Puzzle8* etatCourant = dynamic_cast<Puzzle8*>(_etatCourant);
    for (const auto& sprite : sprites) 
    {
		this->window.draw(sprite);
	}  
}

Etat* JeuPuzzle8::obtenirEtatInitial()
{
   Puzzle8* p = new Puzzle8();//mat est � l'�tat final par d�faut alors on va le m�langer dans Solveur::resoudre
    return p;
}

std::string JeuPuzzle8::obtenirTitre()
{
    return "8 Puzzle Par Alexandre et Alseny";
}
void JeuPuzzle8::animate(Etat* _etatPrecedent, Etat* _etatCourant, float delta)
{
    Puzzle8* etatPrecedent = dynamic_cast<Puzzle8*>(_etatPrecedent);
    Puzzle8* etatCourant = dynamic_cast<Puzzle8*>(_etatCourant);

    int case1 = etatCourant->getCaseBouger();//Obtenir le num�ro de la case boug�e
    sf::Vector2f depart = this->sprites[case1 - 1].getPosition();//Position de la case boug�e
    sf::Vector2f arrivee = this->sprites[this->sprites.size()-1].getPosition();//Position de la case vide

    // Interpolation entre la position de d�part et d'arriv�e
    sf::Vector2f interpolCase1 = interpolation(depart, arrivee, delta);
    sf::Vector2f interpolCaseVide = interpolation(arrivee, depart, delta);
    // Mettre � jour les positions
    this->sprites[case1 - 1].setPosition(interpolCaseVide);
    this->sprites[this->sprites.size() - 1].setPosition(interpolCase1);
}
