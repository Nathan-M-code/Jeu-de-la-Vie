#ifndef BLUE_H
#define BLUE_H

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class BluePrint{
private:
    std::vector< std::vector<bool> > m_grille;
    sf::RectangleShape m_cellule;
    bool m_saved;
public:
    BluePrint(std::string path, float tailleX, float tailleY);
    BluePrint(std::vector< std::vector< bool > > &grille, float tailleX, float tailleY);
    ~BluePrint();

    void updateSize(float tailleX, float tailleY);
    std::vector< std::vector<bool> >& getGrille();
    void initByTxt(std::string path);
    void draw(sf::RenderWindow &window, int ligne, int colonne);
    void sauvegarder(int nom);
};


#endif // BLUE_H
