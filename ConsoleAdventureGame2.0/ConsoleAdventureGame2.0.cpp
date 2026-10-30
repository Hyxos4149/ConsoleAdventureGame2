#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime> 
#include <curses.h>

using namespace std;

// ========================
// STRUCTURES
// ========================

struct Hero {
    char nom;
    int position_x;
    int position_y;
    int vies;
    char direction;
};

struct Enemy {
    char nom;
    int position_x;
    int position_y;
    bool vivant;
};

// ========================
// VARIABLES GLOBALES
// ========================

const int map_size_x = 20;
const int map_size_y = 10;
const int enemy_count = 5;

const int SOL = 0;
const int MONTAGNE = 1;
const int EAU = 2;

bool game = true;
bool victoire = false;

int niveau = 1;
bool niveauTermine = false;

Hero H = { 'H', 0, 5, 3, 'd' };

// Position de la sortie
int sortie_x = 15;
int sortie_y = 0;

// Carte
int map[map_size_x * map_size_y] = {};

// Ennemis
Enemy enemies[enemy_count] = {
    { 'X', 2, 2, true },
    { 'X', 13, 2, true },
    { 'X', 11, 7, true },
    { 'X', 8, 8, true },
    { 'X', 16, 8, true }
};

// ========================
// INITIALISER LA CARTE
// ========================

void initialiserCarte1() {

    // Remplir la carte avec du sol
    for (int i = 0; i < map_size_x * map_size_y; i++) {
        map[i] = SOL;
    }

    // Montagnes
    for (int x = 7; x < 12; x++) {
        for (int y = 0; y < 2; y++) {
            map[y * map_size_x + x] = MONTAGNE;
        }
    }

    for (int x = 10; x < 12; x++) {
        for (int y = 2; y < 5; y++) {
            map[y * map_size_x + x] = MONTAGNE;
        }
    }

    for (int x = 16; x < 19; x++) {
        for (int y = 0; y < 2; y++) {
            map[y * map_size_x + x] = MONTAGNE;
        }
    }

    // Eau
    for (int x = 2; x < 5; x++) {
        for (int y = 6; y < 9; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    for (int x = 15; x < 18; x++) {
        for (int y = 1; y < 4; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    for (int x = 7; x < 10; x++) {
        for (int y = 2; y < 5; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    // Montagne supplementaire
    map[7 * map_size_x + 3] = MONTAGNE;
}

void initialiserCarte2() {

    // Remplir la carte avec du sol
    for (int i = 0; i < map_size_x * map_size_y; i++) {
        map[i] = SOL;
    }

    // Montagnes
    for (int x = 7; x < 12; x++) {
        for (int y = 0; y < 2; y++) {
            map[y * map_size_x + x] = MONTAGNE;
        }
    }

    // Eau
    for (int x = 2; x < 5; x++) {
        for (int y = 6; y < 9; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    for (int x = 15; x < 18; x++) {
        for (int y = 1; y < 4; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    for (int x = 7; x < 10; x++) {
        for (int y = 2; y < 5; y++) {
            map[y * map_size_x + x] = EAU;
        }
    }

    // Montagne supplementaire
    map[7 * map_size_x + 3] = MONTAGNE;
}

// ========================
// AFFICHER LA CARTE
// ========================

void afficherCarte1() {

    system("cls");

    for (int y = 0; y < map_size_y; y++) {

        for (int x = 0; x < map_size_x; x++) {

            // Afficher le heros
            if (x == H.position_x && y == H.position_y) {
                cout << H.nom << ' ';
            }
            else {

                bool ennemiTrouve = false;

                // Rechercher un ennemi
                for (int i = 0; i < enemy_count; i++) {

                    if (enemies[i].vivant &&
                        x == enemies[i].position_x &&
                        y == enemies[i].position_y) {

                        cout << enemies[i].nom << ' ';
                        ennemiTrouve = true;
                        break;
                    }
                }

                // Afficher la sortie ou le terrain
                if (!ennemiTrouve) {

                    if (x == sortie_x && y == sortie_y) {
                        cout << "E ";
                    }
                    else {

                        int terrain = map[y * map_size_x + x];

                        if (terrain == SOL) {
                            cout << ". ";
                        }
                        else if (terrain == MONTAGNE) {
                            cout << "A ";
                        }
                        else if (terrain == EAU) {
                            cout << "~ ";
                        }
                    }
                }
            }
        }

        cout << endl;
    }
}

// ========================
// AFFICHER LES INFORMATIONS
// ========================

void afficherInformations() {

    int ennemisRestants = 0;

    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].vivant) {
            ennemisRestants++;
        }
    }

    cout << "\nNiveau : " << niveau << endl;   // NOUVEAU
    cout << "Vies : " << H.vies << endl;
    cout << "Ennemis restants : " << ennemisRestants << endl;

    cout << "\nZ = Haut | S = Bas" << endl;
    cout << "Q = Gauche | D = Droite" << endl;
    cout << "E = Sortie" << endl;
    cout << "Echap = Quitter" << endl;
}

// ========================
// VERIFIER LES COLLISIONS
// ========================

void verifierCollisions() {

    for (int i = 0; i < enemy_count; i++) {

        if (enemies[i].vivant &&
            H.position_x == enemies[i].position_x &&
            H.position_y == enemies[i].position_y) {

            H.vies--;

            enemies[i].vivant = false;

            if (H.vies < 0) {
                H.vies = 0;
            }

            if (H.vies == 0) {
                game = false;
            }

            // Une seule collision par verification
            break;
        }
    }
}
// ========================
// DEPLACER LE HEROS
// ========================

void deplacerHero(char touche) {

    int next_x = H.position_x;
    int next_y = H.position_y;

    // Choisir la direction
    if (touche == 'z') {
        next_y--;
    }
    else if (touche == 's') {
        next_y++;
    }
    else if (touche == 'q') {
        next_x--;
    }
    else if (touche == 'd') {
        next_x++;
    }
    else {
        return;
    }

    // Verifier les limites
    if (next_x < 0 || next_x >= map_size_x ||
        next_y < 0 || next_y >= map_size_y) {
        return;
    }

    // Verifier le terrain
    int index = next_y * map_size_x + next_x;

    if (map[index] == MONTAGNE || map[index] == EAU) {
        return;
    }

    // Deplacer le heros
    H.position_x = next_x;
    H.position_y = next_y;
}

// ========================
// DEPLACER LES ENNEMIS
// ========================

void deplacerEnnemis() {

    for (int i = 0; i < enemy_count; i++) {

        // Ignorer les ennemis morts
        if (!enemies[i].vivant) {
            continue;
        }

        // Position possible
        int next_x = enemies[i].position_x;
        int next_y = enemies[i].position_y;

        // Choisir une direction au hasard
        int direction = rand() % 4;

        if (direction == 0) {
            next_y--; // Haut
        }
        else if (direction == 1) {
            next_y++; // Bas
        }
        else if (direction == 2) {
            next_x--; // Gauche
        }
        else {
            next_x++; // Droite
        }

        // Verifier les limites de la carte
        if (next_x < 0 || next_x >= map_size_x ||
            next_y < 0 || next_y >= map_size_y) {
            continue;
        }

        // Verifier les obstacles
        int index = next_y * map_size_x + next_x;

        if (map[index] == MONTAGNE || map[index] == EAU) {
            continue;
        }

        // Les ennemis ne peuvent pas aller sur la sortie
        if (next_x == sortie_x && next_y == sortie_y) {
            continue;
        }

        // Verifier si un autre ennemi occupe la case
        bool caseOccupee = false;

        for (int j = 0; j < enemy_count; j++) {

            if (i != j &&
                enemies[j].vivant &&
                next_x == enemies[j].position_x &&
                next_y == enemies[j].position_y) {

                caseOccupee = true;
                break;
            }
        }

        // Si la case est occupee, ne pas bouger
        if (caseOccupee) {
            continue;
        }

        // Appliquer le deplacement
        enemies[i].position_x = next_x;
        enemies[i].position_y = next_y;
    }
}

// ========================
// LIRE LES TOUCHES
// ========================

void lireTouche() {

    char touche = _getch();

    // Quitter avec Echap
    if (touche == 27) {
        game = false;
        return;
    }

    // Convertir les majuscules en minuscules
    if (touche >= 'A' && touche <= 'Z') {
        touche = touche + ('a' - 'A');
    }

    // Seules les touches Z, Q, S et D sont autorisees
    if (touche != 'z' && touche != 'q' &&
        touche != 's' && touche != 'd') {
        return;
    }

    // Tour du heros
    deplacerHero(touche);

    // Verifier les collisions apres le mouvement du heros
    verifierCollisions();

    if (!game) {
        return;
    }

    // Verifier si le heros atteint la sortie
    if (H.position_x == sortie_x &&
        H.position_y == sortie_y) {

        niveauTermine = true;   // MODIFIE : on ne touche plus a game
        return;
    }

    // Tour des ennemis
    deplacerEnnemis();

    // Verifier les collisions apres le mouvement des ennemis
    verifierCollisions();

    // Verifier si le heros est sur la sortie
    if (game &&
        H.position_x == sortie_x &&
        H.position_y == sortie_y) {

        niveauTermine = true;   // MODIFIE
    }
}

// ========================
// AFFICHER LA FIN DU JEU
// ========================

void afficherFinJeu() {

    system("cls");

    if (victoire) {

        cout << "========================" << endl;
        cout << "       VICTOIRE !       " << endl;
        cout << "========================" << endl;

        cout << "\nTu as termine le jeu !" << endl;
    }
    else if (H.vies <= 0) {

        cout << "========================" << endl;
        cout << "       GAME OVER        " << endl;
        cout << "========================" << endl;

        cout << "\nLe heros a perdu toutes ses vies !" << endl;
        cout << "Vies restantes : " << H.vies << endl;
    }
    else {

        cout << "Tu as quitte la partie." << endl;
    }

    cout << "\nAppuie sur une touche pour fermer...";
    _getch();
}

// ========================
// CHANGER DE NIVEAU
// ========================

// NOUVEAU : ecran de victoire entre les niveaux
void afficherVictoireNiveau() {

    system("cls");

    cout << "========================" << endl;
    cout << "       VICTOIRE !       " << endl;
    cout << "========================" << endl;

    cout << "\nNiveau " << niveau << " termine !" << endl;
    cout << "\nAppuie sur une touche pour continuer...";

    _getch();
}

// MODIFIE : prepare le niveau 2
void changeurDelevel() {

    afficherVictoireNiveau();

    niveau = 2;
    niveauTermine = false;

    // Charger la carte 2
    initialiserCarte2();

    // Replacer le heros
    H.position_x = 0;
    H.position_y = 5;

    // Replacer les ennemis
    enemies[0] = { 'X', 3, 2, true };
    enemies[1] = { 'X', 14, 2, true };
    enemies[2] = { 'X', 12, 7, true };
    enemies[3] = { 'X', 9, 8, true };
    enemies[4] = { 'X', 17, 8, true };
}

// ========================
// LANCER LE JEU
// ========================

void lancerJeu() {

    // Initialiser le hasard
    srand((unsigned int)time(0));

    // Initialiser la carte
    initialiserCarte1();

    // Boucle principale
    while (game) {

        // MODIFIE : afficher la bonne carte selon le niveau
        if (niveau == 1) {
            afficherCarte1();
        }
        else {
            afficherCarte1();
        }

        afficherInformations();

        lireTouche();

        // NOUVEAU : si le heros a touche la sortie
        if (niveauTermine) {

            if (niveau == 1) {
                changeurDelevel();   // passer au niveau 2
            }
            else {
                victoire = true;     // fin du jeu
                game = false;
            }
        }
    }

    afficherFinJeu();
}

// ========================
// MAIN
// ========================

int main() {

    lancerJeu();

    return 0;
}
