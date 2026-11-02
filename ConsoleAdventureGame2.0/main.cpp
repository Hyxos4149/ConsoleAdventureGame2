#include "jeu.h"
#include "carte.h"

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<std::string> niveaux = {"niveau1.txt", "niveau2.txt"};
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (std::size_t niveau = 0; niveau < niveaux.size(); ++niveau) {
        std::string erreur;
        if (!chargerNiveau(niveaux[niveau], erreur)) {
            std::cerr << erreur << '\n';
            return 1;
        }
        game = true;
        while (game && !(hero.position_x == sortie_x && hero.position_y == sortie_y)) {
            system("cls");
            afficherCarte();
            afficherInformations();
            const int touche = lireTouche();
            if (!game) break;
            deplacerHero(touche);
            if (game && !(hero.position_x == sortie_x && hero.position_y == sortie_y))
                tourEnnemis();
        }
        if (!game) break;
        afficherVictoireNiveau();
        if (niveau + 1 < niveaux.size()) {
            std::cout << "Appuyez sur une touche pour le niveau suivant...\n";
            _getch();
        }
    }
    if (hero.vies <= 0) afficherFinJeu();
    else if (game) std::cout << "\nVictoire finale ! Tous les niveaux sont terminés.\n";
    return 0;
}
