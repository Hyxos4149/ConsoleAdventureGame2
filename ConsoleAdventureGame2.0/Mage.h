// Role : declare la classe Mage et ses capacites liees au mana.
#pragma once
#include "Player.h"

// Classe Mage : ajoute une reserve de mana et le lancement de sort.
class Mage : public virtual Player {
private:
    int mana = 100;

public:
    // Cree un mage a la position indiquee.
    Mage(int startX, int startY);
    // Retourne le mana disponible.
    int GetMana() const;
    // Met a jour le mana sans valeur negative.
    void SetMana(int value);
    // Lance un sort si le mana est suffisant.
    void CastSpell();
    // Retourne le symbole du mage sur la carte.
    char GetSymbole() const override;
};
