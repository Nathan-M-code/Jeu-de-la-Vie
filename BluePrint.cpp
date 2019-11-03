#include "BluePrint.h"

using namespace std;

BluePrint::BluePrint(std::string path, float tailleX, float tailleY){
    m_cellule.setSize(sf::Vector2f(tailleX,tailleY));
    m_cellule.setOutlineThickness(1);
    m_cellule.setOutlineColor(sf::Color(50,50,255,120));
    m_saved = true;
    initByTxt(path);
}
BluePrint::BluePrint(std::vector<std::vector<bool>> &grille, float tailleX, float tailleY){
    m_grille = grille;
    m_cellule.setSize(sf::Vector2f(tailleX,tailleY));
    m_cellule.setOutlineThickness(1);
    m_cellule.setOutlineColor(sf::Color(50,50,255,120));
    m_saved = false;
}
BluePrint::~BluePrint(){}

void BluePrint::updateSize(float tailleX, float tailleY){
    m_cellule.setSize(sf::Vector2f(tailleX,tailleY));
}

std::vector< std::vector<bool> >& BluePrint::getGrille(){
    return m_grille;
}
void BluePrint::initByTxt(std::string path){
    ifstream fichier("BluePrints/"+path);  //Ouverture d'un fichier en lecture +intToString(x)+"_"+intToString(y)
    if(fichier){
        //Tout est prêt pour la lecture.
        int nbligne = 0;
        string ligne; //Une variable pour stocker les lignes lues

        while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            //cout << ligne << endl;
            int chiffre;
            m_grille.push_back({});
            for (unsigned int i = 0;i<ligne.length();i++){
                chiffre = (int)ligne.at(i) - 48;
                //cout << chiffre << endl;
                if(chiffre){
                    m_grille[nbligne].push_back(true);
                }else{
                    m_grille[nbligne].push_back(false);
                }
            }
            nbligne++;
        }
    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier: "<< path << endl;
    }
}
void BluePrint::sauvegarder(int nom){
    cout << "sauvegarde d'un BluePrint" << endl;
    ofstream fichier("BluePrints/"+std::to_string(nom)+".txt");
    if(fichier){
        for(unsigned int lig=0;lig<m_grille.size();lig++){
            for(unsigned int col=0;col<m_grille[lig].size();col++){
                if(m_grille[lig][col] == true){
                    fichier << 1;
                }else{
                    fichier << 0;
                }
                //avec ou sans espace:
                //fichier << " ";
            }
            fichier << endl;
        }
    }else{
        cout << "erreur lors de la creation du fichier de sauvegarde" << endl;
    }
    m_saved = true;
}
void BluePrint::draw(sf::RenderWindow &window, int ligne, int colonne){
    for(unsigned int lig=0;lig<m_grille.size();lig++){
        for(unsigned int col=0;col<m_grille[lig].size();col++){
            m_cellule.setPosition((colonne+col)*m_cellule.getSize().x,(ligne+lig)*m_cellule.getSize().y);
            if(m_grille[lig][col] == true){
                if(m_saved){
                    m_cellule.setFillColor(sf::Color(50,50,255,120));
                }else{
                    m_cellule.setFillColor(sf::Color(100,100,100,120));
                }
            }else{
                if(m_saved){
                    m_cellule.setFillColor(sf::Color(50,50,255,50));
                }else{
                    m_cellule.setFillColor(sf::Color(150,150,150,50));
                }
            }
            window.draw(m_cellule);
        }
    }
}
