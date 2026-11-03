// Role : declare le chargement des niveaux et l affichage de la carte.
#ifndef CARTE_H
#define CARTE_H

#include <string>
#include "jeu.h"

// Charge et valide un niveau depuis un fichier texte.
bool chargerNiveau(const std::string& fichier, std::string& erreur);
// Affiche les terrains, les ennemis, la sortie et le joueur.
void afficherCarte();

#endif // CARTE_H
