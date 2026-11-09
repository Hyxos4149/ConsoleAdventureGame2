#include "jeu.h"
#include "carte.h"
#include "LancerJeu.h"

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

void lancerJeu() {
    const std::vector<std::string> niveaux = { "niveau1.txt", "niveau2.txt" };
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    choisirClasse();

    for (std::size_t niveau = 0; niveau < niveaux.size(); ++niveau) {
        std::string erreur;
        if (!chargerNiveau(niveaux[niveau], erreur)) {
            std::cerr << erreur << '\n';
            _getch();
            return;
        }
        game = true;

        while (game && !(hero.position_x == sortie_x && hero.position_y == sortie_y)) {
            system("cls");
            afficherCarte();
            afficherInformations();
            const int touche = lireTouche();
            if (!game) break;
            if (touche == ' ') {
                attaquerEnnemis();
            }
            else if (hero.deplacer(touche, map)) {
                verifierCollisions();
            }
            if (game && !(hero.position_x == sortie_x && hero.position_y == sortie_y))
                tourEnnemis();
        }

        if (!game) break;

        afficherVictoireNiveau();
        if (niveau + 1 < niveaux.size()) {
            system("cls");
            std::cout << "========================\n";
            std::cout << "  CHANGEMENT DE NIVEAU  \n";
            std::cout << "  Niveau " << (niveau + 2) << " ...\n";
            std::cout << "========================\n";
            std::cout << "\nAppuyez sur une touche pour continuer...";
            _getch();
        }
    }

    if (hero.vies <= 0) afficherFinJeu();
    else if (game) std::cout << "\nVictoire finale ! Tous les niveaux sont termines.\n";

    delete joueur;
    joueur = nullptr;
}