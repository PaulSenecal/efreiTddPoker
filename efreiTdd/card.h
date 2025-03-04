#ifndef CARD_H
#define CARD_H
#include <QString>

class Card {
public:
    enum class Suit {
        Hearts,      // Cœurs
        Diamonds,    // Carreaux
        Clubs,       // Trèfles
        Spades       // Piques
    };

    enum class Rank {
        Two = 2,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,       // Valet
        Queen,
        King,
        Ace         // As
    };

    // Constructeur
    Card(Rank rank, Suit suit);

    // Getters
    Rank getRank() const;
    Suit getSuit() const;

    // Pour comparer deux cartes
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;

    // Pour afficher la carte
    QString toString() const;

    // Méthodes statiques pour parser les entrées
    static Card fromString(const QString& str);

private:
    Rank m_rank;
    Suit m_suit;
};

#endif // CARD_H
