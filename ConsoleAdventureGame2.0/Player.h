// Role : declare la classe de base des personnages jouables.
#pragma once

// Classe de base : stocke les caracteristiques et gere les actions communes.
class Player {
protected:
    int life = 3; // a partager avec zombie
    int maxLife = 3; // a partager avec zombie
    int attack = 10; 
    int defense = 0; // Reduction de degats conservee, initialisee a zero.
    int x = 0; // a partager avec zombie
    int y = 0; // a partager avec zombie 

public:
    // Cree le joueur a la position de depart.
    Player(int startX, int startY);
    virtual ~Player() = default;

    // Affiche les statistiques de vie.
    void DisplayStats() const;
    // Applique des degats en tenant compte de la defense.
    virtual void TakeDamage(int value);                     // a partager avec zombie
    // Rend des points de vie sans depasser le maximum.
    void Heal(int value);
    // Indique si le joueur a encore des points de vie.
    bool IsAlive() const;                                    // a partager avec zombie
    // Indique si le joueur peut encore agir.
    bool CanPlay() const;                                    // a partager avec zombie
    // Deplace le joueur sur une case de sol valide.
    void Move(int dx, int dy);                               // a partager avec zombie

    // Accede aux points de vie.
    int GetLife() const;                                     // a partager avec zombie
    // Met a jour les points de vie dans leurs limites.
    void SetLife(int value);                                 // a partager avec zombie
    // Accede a la coordonnee horizontale.
    int GetX() const;                                        // a partager avec zombie
    // Accede a la coordonnee verticale.
    int GetY() const;                                        // a partager avec zombie   
    // Place le joueur aux coordonnees indiquees.
    void SetPosition(int newX, int newY);
    // Retourne le caractere qui represente le joueur sur la carte.
    virtual char GetSymbole() const;                        // a partager avec zombie
    // Retourne la valeur d attaque du joueur.
    virtual int GetAttack() const;
};
