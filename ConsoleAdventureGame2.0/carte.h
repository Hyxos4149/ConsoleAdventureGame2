#ifndef CARTE_H
#define CARTE_H

#include <string>
#include "jeu.h"

// Charge une grille de 20 colonnes × 10 lignes. Retourne false et renseigne
// erreur si le fichier est absent ou mal formé.
bool chargerNiveau(const std::string& fichier, std::string& erreur);
void afficherCarte();

#endif
