#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>

class TextBox{
private:
    sf::RectangleShape m_fond;
    sf::Text m_texte;
    std::string m_string;
    sf::Font m_font;
    bool m_focus;
    sf::Vector2f m_pos;
public:
    TextBox(float posX, float posY);
    ~TextBox();

    std::string getString() const;
    bool isEmpty() const;
    bool testClick(int mouseX, int mouseY);
    void setFocus(bool act);
    void ajouterLettre(sf::Uint32 key);
    void setString(std::string str);
    void supprimerLettre();
    void draw(sf::RenderWindow &window);
};


#endif // TEXTBOX_H

