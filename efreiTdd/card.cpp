#include "card.h"
#include <QMap>

Card::Card(Rank rank, Suit suit)
    : m_rank(rank), m_suit(suit)
{
}

Card::Rank Card::getRank() const
{
    return m_rank;
}

Card::Suit Card::getSuit() const
{
    return m_suit;
}

bool Card::operator==(const Card& other) const
{
    return m_rank == other.m_rank && m_suit == other.m_suit;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}

bool Card::operator<(const Card& other) const
{
    return static_cast<int>(m_rank) < static_cast<int>(other.m_rank);
}

bool Card::operator>(const Card& other) const
{
    return static_cast<int>(m_rank) > static_cast<int>(other.m_rank);
}

QString Card::toString() const
{
    QString result;

    // Gestion du rang
    switch (m_rank) {
    case Rank::Two: result = "2"; break;
    case Rank::Three: result = "3"; break;
    case Rank::Four: result = "4"; break;
    case Rank::Five: result = "5"; break;
    case Rank::Six: result = "6"; break;
    case Rank::Seven: result = "7"; break;
    case Rank::Eight: result = "8"; break;
    case Rank::Nine: result = "9"; break;
    case Rank::Ten: result = "10"; break;
    case Rank::Jack: result = "J"; break;
    case Rank::Queen: result = "Q"; break;
    case Rank::King: result = "K"; break;
    case Rank::Ace: result = "A"; break;
    }

    // Gestion de la couleur
    switch (m_suit) {
    case Suit::Hearts: result += "♥"; break;
    case Suit::Diamonds: result += "♦"; break;
    case Suit::Clubs: result += "♣"; break;
    case Suit::Spades: result += "♠"; break;
    }

    return result;
}

Card Card::fromString(const QString& str)
{
    // Mappages pour la conversion
    static const QMap<QChar, Rank> rankMap = {
        {'2', Rank::Two},
        {'3', Rank::Three},
        {'4', Rank::Four},
        {'5', Rank::Five},
        {'6', Rank::Six},
        {'7', Rank::Seven},
        {'8', Rank::Eight},
        {'9', Rank::Nine},
        {'1', Rank::Ten},     // On suppose que "10" est représenté par le premier chiffre
        {'J', Rank::Jack},
        {'Q', Rank::Queen},
        {'K', Rank::King},
        {'A', Rank::Ace}
    };

    static const QMap<QChar, Suit> suitMap = {
        {QChar(u"♥"[0]), Suit::Hearts},
        {QChar(u"♦"[0]), Suit::Diamonds},
        {QChar(u"♣"[0]), Suit::Clubs},
        {QChar(u"♠"[0]), Suit::Spades},
        {'H', Suit::Hearts},    // Alternatives en ASCII
        {'D', Suit::Diamonds},
        {'C', Suit::Clubs},
        {'S', Suit::Spades}
    };

    // Cas spécial pour le 10
    if (str.startsWith("10")) {
        QChar suitChar = str.at(2);
        if (!suitMap.contains(suitChar)) {
            throw std::invalid_argument("Invalid suit symbol");
        }
        return Card(Rank::Ten, suitMap[suitChar]);
    }

    // Cas normal (une lettre ou un chiffre suivi du symbole de la couleur)
    if (str.length() < 2) {
        throw std::invalid_argument("Card string too short");
    }

    QChar rankChar = str.at(0);
    QChar suitChar = str.at(1);

    if (!rankMap.contains(rankChar) || !suitMap.contains(suitChar)) {
        throw std::invalid_argument("Invalid card format");
    }

    return Card(rankMap[rankChar], suitMap[suitChar]);
}
