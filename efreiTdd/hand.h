#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <QVector>
#include <QString>

class Hand {
public:
    static constexpr int HAND_SIZE = 5;  // Définition unique ici

    // Constructeur par défaut
    Hand();

    // Constructeur à partir d'une liste de cartes
    Hand(const QVector<Card>& cards);

    // Ajouter une carte à la main
    bool addCard(const Card& card);

    // Obtenir les cartes de la main
    QVector<Card> getCards() const;

    // Vérifier si la main est complète (5 cartes)
    bool isComplete() const;

    // Vérifier si la main est valide (pas de doublons)
    bool isValid() const;

    // Convertir la main en chaîne de caractères
    QString toString() const;

    // Création d'une main à partir d'une chaîne de caractères
    static Hand fromString(const QString& str);

private:
    QVector<Card> m_cards;
};

#endif // HAND_H
