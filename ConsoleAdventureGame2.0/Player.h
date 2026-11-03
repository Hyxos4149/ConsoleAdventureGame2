// Role : declare la classe de base des personnages jouables.
#pragma once

// Classe de base : stocke les caracteristiques et gere les actions communes.
class Player {
protected:
    int life = 3;
    int maxLife = 3;
    int attack = 10;
    int defense = 0; // Reduction de degats conservee, initialisee a zero.
    int x = 0;
    int y = 0;

public:
    // Cree le joueur a la position de depart.
    Player(int startX, int startY);
    virtual ~Player() = default;

    // Affiche les statistiques de vie.
    void DisplayStats() const;
    // Applique des degats en tenant compte de la defense.
    virtual void TakeDamage(int value);
    // Rend des points de vie sans depasser le maximum.
    void Heal(int value);
    // Indique si le joueur a encore des points de vie.
    bool IsAlive() const;
    // Indique si le joueur peut encore agir.
    bool CanPlay() const;
    // Deplace le joueur sur une case de sol valide.
    void Move(int dx, int dy);

    // Accede aux points de vie.
    int GetLife() const;
    // Met a jour les points de vie dans leurs limites.
    void SetLife(int value);
    // Accede a la coordonnee horizontale.
    int GetX() const;
    // Accede a la coordonnee verticale.
    int GetY() const;
    // Place le joueur aux coordonnees indiquees.
    void SetPosition(int newX, int newY);
    // Retourne le caractere qui represente le joueur sur la carte.
    virtual char GetSymbole() const;
    // Retourne la valeur d attaque du joueur.
    virtual int GetAttack() const;
};
