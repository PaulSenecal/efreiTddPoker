#ifndef GAME_H
#define GAME_H

#include "hand.h"
#include "evaluator.h"
#include <QString>
#include <QVector>

class Game {
public:
    // Résultat du jeu
    struct Result {
        int winner;  // 1 pour le joueur 1, 2 pour le joueur 2, 0 pour égalité
        Evaluator::HandType hand1Type;
        Evaluator::HandType hand2Type;
        QString description; // Description textuelle du résultat
    };

    // Constructeur par défaut
    Game();

    // Définir les mains des joueurs
    void setHand1(const Hand& hand);
    void setHand2(const Hand& hand);

    // Obtenir les mains des joueurs
    Hand getHand1() const;
    Hand getHand2() const;

    // Déterminer le gagnant
    Result determineWinner() const;

    // Créer un jeu à partir d'une chaîne de caractères (format: "main1 | main2")
    static Game fromString(const QString& str);

    // Convertir le jeu en chaîne de caractères
    QString toString() const;

private:
    Hand m_hand1;
    Hand m_hand2;
};

#endif // GAME_H
