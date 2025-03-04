#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "hand.h"
#include <QVector>

class Evaluator {
public:
    // Types de mains de poker (du plus faible au plus fort)
    enum class HandType {
        HighCard,       // Carte haute
        OnePair,        // Paire
        TwoPair,        // Deux paires
        ThreeOfAKind,   // Brelan
        Straight,       // Quinte (Suite)
        Flush,          // Couleur
        FullHouse,      // Full
        FourOfAKind,    // Carré
        StraightFlush,  // Quinte Flush
        RoyalFlush      // Quinte Flush Royale
    };

    // Structure pour stocker le score d'une main
    struct HandScore {
        HandType type;
        QVector<int> tiebreakers;  // Pour départager en cas d'égalité

        bool operator<(const HandScore& other) const;
        bool operator>(const HandScore& other) const;
        bool operator==(const HandScore& other) const;
    };

    // Évaluer une main et retourner son score
    static HandScore evaluate(const Hand& hand);

    // Comparer deux mains et déterminer la gagnante
    // Retourne 1 si la première main gagne, -1 si la deuxième main gagne, 0 en cas d'égalité
    static int compareHands(const Hand& hand1, const Hand& hand2);

    // Convertir un type de main en chaîne de caractères
    static QString handTypeToString(HandType type);

private:
    // Méthodes auxiliaires pour vérifier les différents types de mains
    static bool isRoyalFlush(const QVector<Card>& cards);
    static bool isStraightFlush(const QVector<Card>& cards);
    static bool isFourOfAKind(const QVector<Card>& cards);
    static bool isFullHouse(const QVector<Card>& cards);
    static bool isFlush(const QVector<Card>& cards);
    static bool isStraight(const QVector<Card>& cards);
    static bool isThreeOfAKind(const QVector<Card>& cards);
    static bool isTwoPair(const QVector<Card>& cards);
    static bool isOnePair(const QVector<Card>& cards);

    // Méthodes pour obtenir les tiebreakers selon le type de main
    static QVector<int> getRoyalFlushTiebreakers(const QVector<Card>& cards);
    static QVector<int> getStraightFlushTiebreakers(const QVector<Card>& cards);
    static QVector<int> getFourOfAKindTiebreakers(const QVector<Card>& cards);
    static QVector<int> getFullHouseTiebreakers(const QVector<Card>& cards);
    static QVector<int> getFlushTiebreakers(const QVector<Card>& cards);
    static QVector<int> getStraightTiebreakers(const QVector<Card>& cards);
    static QVector<int> getThreeOfAKindTiebreakers(const QVector<Card>& cards);
    static QVector<int> getTwoPairTiebreakers(const QVector<Card>& cards);
    static QVector<int> getOnePairTiebreakers(const QVector<Card>& cards);
    static QVector<int> getHighCardTiebreakers(const QVector<Card>& cards);

    // Méthodes utilitaires
    static QVector<int> getRankCounts(const QVector<Card>& cards);
    static QVector<Card> sortByRank(const QVector<Card>& cards);
    static bool allSameSuit(const QVector<Card>& cards);
    static bool isSequential(const QVector<Card>& cards);
    static bool isLowStraight(const QVector<Card>& cards);  // A,2,3,4,5
};

#endif // EVALUATOR_H
