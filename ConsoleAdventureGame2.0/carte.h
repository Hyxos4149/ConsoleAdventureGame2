#ifndef CARTE_H
#define CARTE_H

#include <string>
#include "jeu.h"

bool chargerNiveau(const std::string& fichier, std::string& erreur);
void afficherCarte();

#endif // CARTE_H
