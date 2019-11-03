#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "BluePrint.h"
#include <dirent.h>
#include "TextBox.h"

using namespace std;


int compterFichier(){
    DIR* rep;
    rep = opendir("BluePrints"); /* Ouverture d'un dossier */
    if (rep == 0){/* Si le dossier n'a pas pu être ouvert */
        cout << "impossible d'ouvir le dossier" << endl;
    }
    int nbr = 0;
    struct dirent* ent = NULL;
    while ((ent = readdir(rep)) != NULL){
        //cout << ent->d_name << endl;
        nbr++; /* Alors on incrémente le compteur */
    }
    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
        cout << "impossible de fermer le dossier"<< endl;
    }
    return nbr-2;
}

void modifTailleGrille(vector<vector<bool>> &grille,vector<vector<int>> &grilleVoisin, int nvLigne, int nvColonne, sf::RectangleShape &cellule){
    while(nvLigne<grille.size()){
        grille.pop_back();
        grilleVoisin.pop_back();
    }
    while(nvLigne>grille.size()){
        grille.push_back({});
        grilleVoisin.push_back({});
        for(unsigned int colonne=0;colonne<grille[0].size();colonne++){
            grille[grille.size()-1].push_back(false);
            grilleVoisin[grilleVoisin.size()-1].push_back(0);
        }
    }
    while(nvColonne<grille[0].size()){
        for(unsigned int ligne=0;ligne<grille.size();ligne++){
            grille[ligne].pop_back();
            grilleVoisin[ligne].pop_back();
        }
    }
    while(nvColonne>grille[0].size()){
        for(unsigned int ligne=0;ligne<grille.size();ligne++){
            grille[ligne].push_back(false);
            grilleVoisin[ligne].push_back(0);
        }
    }
    cellule.setSize(sf::Vector2f(1920.0/grille[0].size(),1080.0/grille.size()));
}

string boolToString(bool bo){
    if(bo){
        return "true";
    }else{
        return "false";
    }
}

void ajouterUnsignedInt(sf::Vector2u val, vector<unsigned int> &listeLigne, vector<unsigned int> &listeColonne){
    bool dejaDansListe = false;
    for(unsigned int i=0;i<listeLigne.size();i++){
        if(listeLigne[i] == val.x && listeColonne[i] == val.y){
            dejaDansListe = true;
            break;
        }
    }
    if(!dejaDansListe){
        listeLigne.push_back(val.x);
        listeColonne.push_back(val.y);
    }
}

void retirerUnsignedInt(sf::Vector2u val, vector<unsigned int> &listeLigne, vector<unsigned int> &listeColonne){
    for(unsigned int i=0;i<listeLigne.size();i++){
        if(listeLigne[i] == val.x && listeColonne[i] == val.y){
            listeLigne.erase(listeLigne.begin()+i);
            listeColonne.erase(listeColonne.begin()+i);
            break;
        }
    }
}

void ajouterCalculable(unsigned int ligne, unsigned int colonne, vector<vector<bool>> &grille, bool bordPrisEnCompte, vector<unsigned int> &listeCalculableLigne, vector<unsigned int> &listeCalculableColonne){
    if(!bordPrisEnCompte){
        if(ligne==0 && colonne !=0 && colonne != grille[ligne].size()-1){//en haut
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }else if(colonne == grille[ligne].size()-1 && ligne !=0 && ligne != grille.size()-1){//a droite
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,0),listeCalculableLigne,listeCalculableColonne);
        }else if(ligne == grille.size()-1 && colonne != 0 && colonne != grille[ligne].size()-1){//en bas
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }else if(colonne == 0 && ligne != 0 && ligne != grille.size()-1){//a gauche
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }else if(ligne==0 && colonne ==0){//a coin en haut a gauche
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }else if(ligne==0 && colonne == grille[ligne].size()-1){//coin en haut a droite
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(grille.size()-1,0),listeCalculableLigne,listeCalculableColonne);
        }else if(ligne==grille.size()-1 && colonne == grille[ligne].size()-1){//coin en bas a droite
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,0),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,0),listeCalculableLigne,listeCalculableColonne);
        }else if(ligne==grille.size()-1 && colonne ==0){//coin en bas a gauche
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(0,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,grille[ligne].size()-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }else{ //au centre
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }
    }else{
        ajouterUnsignedInt(sf::Vector2u(ligne,colonne),listeCalculableLigne,listeCalculableColonne);
        if(ligne+1<grille.size()){
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne),listeCalculableLigne,listeCalculableColonne);
        }
        if(ligne+1<grille.size() && colonne+1<grille[0].size()){
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }
        if(ligne+1<grille.size() && colonne-1>=0){
            ajouterUnsignedInt(sf::Vector2u(ligne+1,colonne-1),listeCalculableLigne,listeCalculableColonne);
        }
        if(colonne-1>=0){
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne-1),listeCalculableLigne,listeCalculableColonne);
        }
        if(colonne+1<grille[0].size()){
            ajouterUnsignedInt(sf::Vector2u(ligne,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }
        if(ligne-1>=0 && colonne-1>=0){
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne-1),listeCalculableLigne,listeCalculableColonne);
        }
        if(ligne-1>=0){
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne),listeCalculableLigne,listeCalculableColonne);
        }
        if(ligne-1>=0 && colonne+1<grille[0].size()){
            ajouterUnsignedInt(sf::Vector2u(ligne-1,colonne+1),listeCalculableLigne,listeCalculableColonne);
        }
    }
}

int main(){
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920,1080), "Jeu de la vie", sf::Style::Fullscreen);
    window.setFramerateLimit(120);

    sf::Vector2i mousePos;
    sf::Vector2i mousePosCase;

    sf::Clock clockFPS;
    double fps;
    int ups = 20; //en nombre de fois
    int nbThread = 1;

    vector<sf::Thread*> listeThread;

    sf::Clock clockJeu;

    sf::Font font;
    font.loadFromFile("KeepCalm-Medium.ttf");
    sf::Text textCamera;
    textCamera.setFont(font);
    textCamera.setPosition(0,250);
    textCamera.setFillColor(sf::Color(0,0,0));
    textCamera.setCharacterSize(16);

    bool interface = false;
    sf::RectangleShape fondInterface;
    fondInterface.setSize(sf::Vector2f(1700,900));
    fondInterface.setFillColor(sf::Color(150,150,150));
    fondInterface.setOutlineThickness(5);
    fondInterface.setOutlineColor(sf::Color(200,200,200));
    fondInterface.setPosition(110,90);

    sf::Uint32 key;
    TextBox *tbFocus=0;
    vector<TextBox*> listeTextBox;
    TextBox *tb0 = new TextBox(400,110);
    tb0->setString(to_string(27));
    listeTextBox.push_back(tb0);
    TextBox *tb1 = new TextBox(400,140);
    tb1->setString(to_string(48));
    listeTextBox.push_back(tb1);
    TextBox *tb2 = new TextBox(400,170);
    listeTextBox.push_back(tb2);
    tb2->setString(to_string(20));
    TextBox *tb3 = new TextBox(400,200);
    listeTextBox.push_back(tb3);
    tb3->setString(to_string(nbThread));

    sf::RectangleShape boutonAppliquer;
    boutonAppliquer.setSize(sf::Vector2f(400,100));
    boutonAppliquer.setFillColor(sf::Color(100,100,100));
    boutonAppliquer.setOutlineThickness(3);
    boutonAppliquer.setOutlineColor(sf::Color(50,50,50));
    boutonAppliquer.setPosition(760,840);

    vector<vector<bool>> grille;
    vector<vector<int>> grilleVoisin;
    vector<unsigned int> listeNoirLigne;
    vector<unsigned int> listeNoirColonne;
    vector<unsigned int> listeCalculableLigne;
    vector<unsigned int> listeCalculableColonne;

    bool pause = true;
    bool bordPrisEnCompte = false;

    bool visuBp=false;
    bool clickDroit=false;
    sf::Vector2i origineCarre;
    sf::RectangleShape carreVisu;
    carreVisu.setOutlineThickness(5);
    carreVisu.setOutlineColor(sf::Color(0,0,255));
    carreVisu.setFillColor(sf::Color(0,0,0,0));

    std::vector<BluePrint*> listeBluePrint;
    int indexBp=0;

    for(unsigned int nbligne = 0;nbligne<27;nbligne++){//27
        grille.push_back({});
        grilleVoisin.push_back({});
    }
    for(int ligne=0;ligne<grille.size();ligne++){
        for(int colonne=0;colonne<48;colonne++){//48
            grille[ligne].push_back(false);
            grilleVoisin[ligne].push_back(0);
        }
    }

    sf::RectangleShape cellule;
    cellule.setSize(sf::Vector2f(1920.0/grille[0].size(),1080.0/grille.size()));

    sf::RectangleShape fondBlanc;
    fondBlanc.setSize(sf::Vector2f(1920.0,1080.0));
    fondBlanc.setFillColor(sf::Color::White);

    cout << "lecture des blueprints" << endl;
    for(unsigned int i=0;i<compterFichier();i++){
        BluePrint *bp = new BluePrint(std::to_string(i)+".txt", cellule.getSize().x, cellule.getSize().y);
        cout << "bluePrints initialise!" << endl;
        listeBluePrint.push_back(bp);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    if (event.key.code == sf::Keyboard::Space){
                        pause = !pause;
                    }
                    if (event.key.code == sf::Keyboard::LShift){
                        visuBp=true;
                    }
                    if (event.key.code == sf::Keyboard::B){
                        bordPrisEnCompte=!bordPrisEnCompte;
                    }
                    if (event.key.code == sf::Keyboard::O){
                        if(!interface){
                            interface = true;
                            pause = true;
                        }else{
                            interface = false;
                            pause = false;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Enter && visuBp){
                        //sauvegarderBP
                        if(listeBluePrint.size()!=0){
                            int nbFichier = compterFichier();
                            listeBluePrint[indexBp]->sauvegarder(nbFichier);
                        }
                    }
                    if (event.key.code == sf::Keyboard::C){
                        for(int ligne=0;ligne<grille.size();ligne++){
                            for(int colonne=0;colonne<grille[ligne].size();colonne++){
                                grille[ligne][colonne] = false;
                            }
                        }
                        listeNoirColonne.clear();
                        listeNoirLigne.clear();
                    }
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::LShift){
                        visuBp=false;
                    }
                    break;
                case sf::Event::TextEntered:
                    if(tbFocus!=0){
                        key = event.text.unicode;
                        if(key>=48 && key<=57){//si c'est un chiffre
                            tbFocus->ajouterLettre(key);
                        }else if(key == 8){
                            tbFocus->supprimerLettre();
                        }
                    }
                    break;
                case sf::Event::MouseMoved:
                    mousePos = sf::Mouse::getPosition(window);
                    mousePosCase = sf::Vector2i(mousePos.y/cellule.getSize().y, mousePos.x/cellule.getSize().x);
                    break;
                case sf::Event::MouseButtonPressed:
                    mousePos = sf::Mouse::getPosition(window);
                    mousePosCase = sf::Vector2i(mousePos.y/cellule.getSize().y, mousePos.x/cellule.getSize().x);
                    if(interface){
                        tbFocus=0;
                        for(unsigned int i=0;i<listeTextBox.size();i++){
                            if(listeTextBox[i]->testClick(mousePos.x, mousePos.y)){
                                listeTextBox[i]->setFocus(true);
                                tbFocus = listeTextBox[i];
                            }else{
                                listeTextBox[i]->setFocus(false);
                            }
                        }
                        //test clique appliquer
                        if(mousePos.x >= 760 && mousePos.x <= 760+400 && mousePos.y >= 840 && mousePos.y <= 840+100){
                            //aplliquer les valeurs
                            if(!listeTextBox[0]->isEmpty() && !listeTextBox[1]->isEmpty()){
                                modifTailleGrille(grille, grilleVoisin, stoi(listeTextBox[0]->getString()),stoi(listeTextBox[1]->getString()), cellule);
                                for(unsigned int i=0;i<listeBluePrint.size();i++){
                                    listeBluePrint[i]->updateSize(cellule.getSize().x, cellule.getSize().y);
                                }
                            }
                            if(!listeTextBox[2]->isEmpty()){
                                ups = stoi(listeTextBox[2]->getString());
                            }
                            if(!listeTextBox[3]->isEmpty()){
                                nbThread = stoi(listeTextBox[3]->getString());
                            }
                            interface = false;
                            pause = false;
                        }
                    }else{
                        if (event.mouseButton.button == sf::Mouse::Left){
                            if(visuBp){
                                //print du bp
                                std::vector< std::vector<bool> > bpGrille = listeBluePrint[indexBp]->getGrille();
                                for(int lig=0;lig<bpGrille.size();lig++){
                                    for(int col=0;col<bpGrille[lig].size();col++){
                                        if(mousePosCase.x+lig>=0 && mousePosCase.x+lig<grille.size() && mousePosCase.y+col>=0 && mousePosCase.y+col<grille[mousePosCase.x+lig].size()){
                                            grille[mousePosCase.x+lig][mousePosCase.y+col] = bpGrille[lig][col];
                                            if(grille[mousePosCase.x+lig][mousePosCase.y+col]){
                                                ajouterUnsignedInt(sf::Vector2u(mousePosCase.x+lig, mousePosCase.y+col), listeNoirLigne, listeNoirColonne);
                                                ajouterCalculable(mousePosCase.x+lig, mousePosCase.y+col, grille, bordPrisEnCompte, listeCalculableLigne, listeCalculableColonne);
                                            }
                                        }
                                    }
                                }
                            }else{
                                if(0<=mousePosCase.x && mousePosCase.x<grille.size() && 0<=mousePosCase.y && mousePosCase.y<grille[mousePosCase.x].size()){
                                    if(!grille[mousePosCase.x][mousePosCase.y]){
                                        grille[mousePosCase.x][mousePosCase.y] = true;
                                        ajouterUnsignedInt(sf::Vector2u(mousePosCase.x, mousePosCase.y), listeNoirLigne, listeNoirColonne);
                                        ajouterCalculable(mousePosCase.x, mousePosCase.y, grille, bordPrisEnCompte, listeCalculableLigne, listeCalculableColonne);
                                    }else{
                                        grille[mousePosCase.x][mousePosCase.y] = false;
                                        retirerUnsignedInt(sf::Vector2u(mousePosCase.x, mousePosCase.y), listeNoirLigne, listeNoirColonne);
                                    }
                                }
                            }
                        }
                        if (event.mouseButton.button == sf::Mouse::Right){
                            clickDroit=true;
                            origineCarre = mousePosCase;
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Right){
                        clickDroit=false;
                        //creation blueprint
                        std::vector<std::vector<bool>> bpgrille;
                        for(unsigned int nbligne=0;nbligne<abs(mousePosCase.x-origineCarre.x)+1;nbligne++){
                            bpgrille.push_back({});
                        }
                        for(unsigned int ligne=0;ligne<bpgrille.size();ligne++){
                            for(unsigned int nbcolonne=0;nbcolonne<abs(mousePosCase.y-origineCarre.y)+1;nbcolonne++){
                                bpgrille[ligne].push_back(false);
                            }
                        }
                        //assignation des valeurs
                        int indexLigne;
                        int indexColonne;
                        if(mousePosCase.y >= origineCarre.y && mousePosCase.x >= origineCarre.x){
                            indexLigne = origineCarre.x;
                            indexColonne = origineCarre.y;
                        }else if(mousePosCase.y < origineCarre.y && mousePosCase.x < origineCarre.x){
                            indexLigne = mousePosCase.x;
                            indexColonne = mousePosCase.y;
                        }else if(mousePosCase.y >= origineCarre.y && mousePosCase.x < origineCarre.x){
                            indexLigne = mousePosCase.x;
                            indexColonne = origineCarre.y;
                        }else if(mousePosCase.y < origineCarre.y && mousePosCase.x >= origineCarre.x){
                            indexLigne = origineCarre.x;
                            indexColonne = mousePosCase.y;
                        }
                        for(unsigned int ligne=0;ligne<bpgrille.size();ligne++){
                            for(unsigned int colonne=0;colonne<bpgrille[ligne].size();colonne++){
                                bpgrille[ligne][colonne] = grille[indexLigne+ligne][indexColonne+colonne];
                            }
                        }
                        //on verifie qu'il y a au moin une case rempli
                        bool auMoinsUne=false;
                        for(unsigned int ligne=0;ligne<bpgrille.size();ligne++){
                            for(unsigned int colonne=0;colonne<bpgrille[ligne].size();colonne++){
                                if(bpgrille[ligne][colonne]){
                                    auMoinsUne = true;
                                    break;
                                }
                            }
                        }
                        if(auMoinsUne){
                            BluePrint *bp = new BluePrint(bpgrille, cellule.getSize().x, cellule.getSize().y);
                            cout << "ajout dun blueprint" << endl;
                            listeBluePrint.push_back(bp);
                        }
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    if(indexBp + event.mouseWheel.delta >= 0 && indexBp + event.mouseWheel.delta<listeBluePrint.size()){
                        indexBp += event.mouseWheel.delta;
                    }
                    break;
            }
        }
        //logique
        //affichage fps
        sf::Time elapsed = clockFPS.restart();
        fps = round(1000.0/elapsed.asMilliseconds());

        //on gere la boucle de calcule
        sf::Time tempsEcoule = clockJeu.getElapsedTime();
        if(tempsEcoule.asMilliseconds() >= (1000/ups)){
            clockJeu.restart();
            if(!pause){//si c'est pas en pause
                //calcule voisins
                int nombreVoisin = 0;
                for(unsigned int i=0;i<listeCalculableLigne.size();i++){
                    unsigned int ligne = listeCalculableLigne[i];
                    unsigned int colonne = listeCalculableColonne[i];
                    nombreVoisin = 0;
                    if(!bordPrisEnCompte){
                        if(ligne==0 && colonne !=0 && colonne != grille[ligne].size()-1){//en haut
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }else if(colonne == grille[ligne].size()-1 && ligne !=0 && ligne != grille.size()-1){//a droite
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][0]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][0]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][0]){
                                nombreVoisin++;
                            }
                        }else if(ligne == grille.size()-1 && colonne != 0 && colonne != grille[ligne].size()-1){//en bas
                            if(grille[0][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[0][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[0][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }else if(colonne == 0 && ligne != 0 && ligne != grille.size()-1){//a gauche
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }else if(ligne==0 && colonne ==0){//a coin en haut a gauche
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }else if(ligne==0 && colonne == grille[ligne].size()-1){//coin en haut a droite
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][0]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][0]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[grille.size()-1][0]){
                                nombreVoisin++;
                            }
                        }else if(ligne==grille.size()-1 && colonne == grille[ligne].size()-1){//coin en bas a droite
                            if(grille[0][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[0][0]){
                                nombreVoisin++;
                            }
                            if(grille[0][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][0]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][0]){
                                nombreVoisin++;
                            }
                        }else if(ligne==grille.size()-1 && colonne ==0){//coin en bas a gauche
                            if(grille[0][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[0][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[0][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][grille[ligne].size()-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }else{ //au centre
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne+1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne-1]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                            if(grille[ligne-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }
                    }else{
                        if(ligne+1<grille.size()){
                            if(grille[ligne+1][colonne]){
                                nombreVoisin++;
                            }
                        }
                        if(ligne+1<grille.size() && colonne+1<grille[0].size()){
                            if(grille[ligne+1][colonne+1]){
                                nombreVoisin++;
                            }
                        }
                        if(ligne+1<grille.size() && colonne-1>=0){
                            if(grille[ligne+1][colonne-1]){
                                nombreVoisin++;
                            }
                        }
                        if(colonne-1>=0){
                            if(grille[ligne][colonne-1]){
                                nombreVoisin++;
                            }
                        }
                        if(colonne+1<grille[0].size()){
                            if(grille[ligne][colonne+1]){
                                nombreVoisin++;
                            }
                        }
                        if(ligne-1>=0 && colonne-1>=0){
                            if(grille[ligne-1][colonne-1]){
                                nombreVoisin++;
                            }
                        }
                        if(ligne-1>=0){
                            if(grille[ligne-1][colonne]){
                                nombreVoisin++;
                            }
                        }
                        if(ligne-1>=0 && colonne+1<grille[0].size()){
                            if(grille[ligne-1][colonne+1]){
                                nombreVoisin++;
                            }
                        }
                    }
                    grilleVoisin[ligne][colonne] = nombreVoisin;
                }

                //changement etat:
                for(unsigned int i=0;i<listeCalculableLigne.size();i++){
                    unsigned int ligne = listeCalculableLigne[i];
                    unsigned int colonne = listeCalculableColonne[i];
                    //Une cellule morte possédant exactement trois voisines vivantes devient vivante (elle naît).
                    //Une cellule vivante possédant deux ou trois voisines vivantes le reste, sinon elle meurt.
                    if(grille[ligne][colonne]==false){
                        if(grilleVoisin[ligne][colonne]==3){
                            grille[ligne][colonne]=true;
                            ajouterUnsignedInt(sf::Vector2u(ligne,colonne), listeNoirLigne, listeNoirColonne);
                        }
                    }else{
                        if(grilleVoisin[ligne][colonne]<2 || grilleVoisin[ligne][colonne]>3){
                            grille[ligne][colonne]=false;
                            retirerUnsignedInt(sf::Vector2u(ligne,colonne), listeNoirLigne, listeNoirColonne);
                        }
                    }
                }

                //nouvel listeCalculable en fonction des noires:
                listeCalculableLigne.clear();
                listeCalculableColonne.clear();
                for(unsigned int i=0;i<listeNoirLigne.size();i++){
                    unsigned int ligne = listeNoirLigne[i];
                    unsigned int colonne = listeNoirColonne[i];
                    ajouterCalculable(ligne, colonne, grille, bordPrisEnCompte, listeCalculableLigne, listeCalculableColonne);
                }
            }
        }

        //clear
        window.clear();

        //draw
        //cellules
        if(grille.size() >= 50 || grille[0].size() >= 50){
            cellule.setOutlineThickness(0);
            window.draw(fondBlanc);
            for(unsigned int i=0;i<listeNoirLigne.size();i++){
                cellule.setPosition(listeNoirColonne[i]*cellule.getSize().x,listeNoirLigne[i]*cellule.getSize().y);
                cellule.setFillColor(sf::Color(0,0,0));
                window.draw(cellule);
            }
        }else{
            cellule.setOutlineThickness(1);
            for(int ligne=0;ligne<grille.size();ligne++){
                for(int colonne=0;colonne<grille[ligne].size();colonne++){
                    cellule.setPosition(colonne*cellule.getSize().x,ligne*cellule.getSize().y);
                    if(grille[ligne][colonne] == true){
                        cellule.setFillColor(sf::Color(0,0,0));
                        cellule.setOutlineColor(sf::Color(100,100,100));
                    }else{
                        cellule.setFillColor(sf::Color(255,255,255));
                        cellule.setOutlineColor(sf::Color(100,100,100));
                    }
                    window.draw(cellule);
                }
            }
        }

        if(interface){
            window.draw(fondInterface);
            for(unsigned int i=0;i<listeTextBox.size();i++){
                listeTextBox[i]->draw(window);
            }
            window.draw(boutonAppliquer);
        }else{
            //carreVisuClickDroit
            if(clickDroit){
                //cout << "test: "<<mousePosCase.y*40 << " " << mousePosCase.x*40 << " " <<origineCarre.y*40 << " " << origineCarre.x*40 << endl;
                if(mousePosCase.y >= origineCarre.y && mousePosCase.x >= origineCarre.x){
                    carreVisu.setSize(sf::Vector2f(mousePosCase.y*cellule.getSize().x+cellule.getSize().x-origineCarre.y*cellule.getSize().x, mousePosCase.x*cellule.getSize().y+cellule.getSize().y-origineCarre.x*cellule.getSize().y));
                    carreVisu.setPosition(origineCarre.y*cellule.getSize().x,origineCarre.x*cellule.getSize().y);

                }else if(mousePosCase.y < origineCarre.y && mousePosCase.x < origineCarre.x){
                    carreVisu.setSize(sf::Vector2f(origineCarre.y*cellule.getSize().x-mousePosCase.y*cellule.getSize().x+cellule.getSize().x, origineCarre.x*cellule.getSize().y-mousePosCase.x*cellule.getSize().y+cellule.getSize().y));
                    carreVisu.setPosition(mousePosCase.y*cellule.getSize().x,mousePosCase.x*cellule.getSize().y);

                }else if(mousePosCase.y >= origineCarre.y && mousePosCase.x < origineCarre.x){
                    carreVisu.setSize(sf::Vector2f(mousePosCase.y*cellule.getSize().x-origineCarre.y*cellule.getSize().x+cellule.getSize().x, mousePosCase.x*cellule.getSize().y-origineCarre.x*cellule.getSize().y-cellule.getSize().y));
                    carreVisu.setPosition(origineCarre.y*cellule.getSize().x,origineCarre.x*cellule.getSize().y+cellule.getSize().y);

                }else if(mousePosCase.y < origineCarre.y && mousePosCase.x >= origineCarre.x){
                    carreVisu.setSize(sf::Vector2f(mousePosCase.y*cellule.getSize().x-origineCarre.y*cellule.getSize().x-cellule.getSize().x, mousePosCase.x*cellule.getSize().y+cellule.getSize().y-origineCarre.x*cellule.getSize().y));
                    carreVisu.setPosition(origineCarre.y*cellule.getSize().x+cellule.getSize().x,origineCarre.x*cellule.getSize().y);
                }
                window.draw(carreVisu);
            }
            //bp
            if(visuBp){
                if(listeBluePrint.size()!=0){
                    if(indexBp>=0 && indexBp<listeBluePrint.size()){
                        listeBluePrint[indexBp]->draw(window, mousePosCase.x, mousePosCase.y);
                    }
                }
            }
        }

        //texte
        if(interface){
            textCamera.setPosition(130,110);
            textCamera.setString("Taille de la grille : ligne : ");
            window.draw(textCamera);
            textCamera.setPosition(130,140);
            textCamera.setString("Taille de la grille : colonne : ");
            window.draw(textCamera);
            textCamera.setPosition(130,170);
            textCamera.setString("Update par seconde : ");
            window.draw(textCamera);
            textCamera.setPosition(130,200);
            textCamera.setString("Nombre de Thread : ");
            window.draw(textCamera);
            textCamera.setPosition(1300,110);
            textCamera.setString("Touches :");
            window.draw(textCamera);
            textCamera.setPosition(1300,140);
            textCamera.setString("Option : O");
            window.draw(textCamera);
            textCamera.setPosition(1300,170);
            textCamera.setString("Pause : Barre espace");
            window.draw(textCamera);
            textCamera.setPosition(1300,200);
            textCamera.setString("BluePrint : Shift");
            window.draw(textCamera);
            textCamera.setPosition(1300,230);
            textCamera.setString("Sauvegarder BluePrint : Shift+Enter sur le blueprint");
            window.draw(textCamera);
            textCamera.setPosition(1300,260);
            textCamera.setString("Changer de BluePrint : Molette");
            window.draw(textCamera);
            textCamera.setPosition(1300,290);
            textCamera.setString("Effacer la grille : C");
            window.draw(textCamera);
            textCamera.setPosition(1300,320);
            textCamera.setString("Changer la prise en compte des bords : B");
            window.draw(textCamera);
            textCamera.setPosition(910,882);
            textCamera.setString("Appliquer");
            window.draw(textCamera);
        }else{
            textCamera.setPosition(0,0);
            textCamera.setString("mousePos: x: "+std::to_string(mousePos.x)+" y: "+std::to_string(mousePos.y));
            window.draw(textCamera);
            textCamera.setPosition(0,20);
            textCamera.setString("Pause: "+boolToString(pause));
            window.draw(textCamera);
            textCamera.setPosition(0,40);
            textCamera.setString("FPS: "+std::to_string(fps));
            window.draw(textCamera);
            textCamera.setPosition(0,60);
            textCamera.setString("Grille: ligne: "+std::to_string(grille.size())+" colonne: "+std::to_string(grille[0].size())+" total: "+std::to_string(grille[0].size()*grille.size()));
            window.draw(textCamera);
            textCamera.setPosition(0,80);
            textCamera.setString("Taille cellule: x: "+std::to_string(cellule.getSize().x)+" y: "+std::to_string(cellule.getSize().y));
            window.draw(textCamera);
            textCamera.setPosition(0,100);
            textCamera.setString("Update par seconde: "+to_string(ups));
            window.draw(textCamera);
            textCamera.setPosition(0,120);
            textCamera.setString("Prise en compte des bords: "+boolToString(bordPrisEnCompte));
            window.draw(textCamera);
            textCamera.setPosition(0,140);
            textCamera.setString("nbLigneNoir: "+to_string(listeNoirLigne.size()));
            window.draw(textCamera);
            textCamera.setPosition(0,160);
            textCamera.setString("nbColonneNoir: "+to_string(listeNoirColonne.size()));
            window.draw(textCamera);
            textCamera.setPosition(0,180);
            textCamera.setString("nbLigneCalculable: "+to_string(listeCalculableLigne.size()));
            window.draw(textCamera);
            textCamera.setPosition(0,200);
            textCamera.setString("nbColonneCalculable: "+to_string(listeCalculableColonne.size()));
            window.draw(textCamera);


            textCamera.setPosition(0,500);
            textCamera.setString("listebp: "+std::to_string(indexBp+1)+"(-1) / "+std::to_string(listeBluePrint.size()));
            window.draw(textCamera);
            textCamera.setPosition(0,520);
            textCamera.setString("Option: O");
            window.draw(textCamera);
        }
        window.display();
    }
    return 0;
}
