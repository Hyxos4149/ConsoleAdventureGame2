// Menu de choix et injection du personnage dans le singleton du jeu.
#include "LancerJeu.h"
#include "Game.h"
#include "Mage.h"
#include "Player.h"
#include "Warrior.h"
#include "WarriorMage.h"
#include <conio.h>
#include <iostream>
#include <memory>
void LancerJeu::Lancer() {
    std::unique_ptr<Player> joueur;
    while (!joueur) {
        std::cout << "========================\n   CHOIX DE TA CLASSE   \n========================\n1 - Warrior\n2 - Mage\n3 - WarriorMage\nTon choix : " << std::flush;
        const int choix = _getch(); std::cout << '\n';
        if (choix == '1') joueur = std::make_unique<Warrior>(Vector2{0,5});
        else if (choix == '2') joueur = std::make_unique<Mage>(Vector2{0,5});
        else if (choix == '3') joueur = std::make_unique<WarriorMage>(Vector2{0,5});
        else std::cout << "Choix invalide. Reessaie.\n";
    }
    Game::GetInstance()->SetPlayer(std::move(joueur));
    Game::GetInstance()->Run();
}
