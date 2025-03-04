#include "hand.h"
#include <QSet>
#include <QStringList>

Hand::Hand()
{
    m_cards.reserve(HAND_SIZE);
}

Hand::Hand(const QVector<Card>& cards)
{
    // Ne prendre que les 5 premières cartes
    for (int i = 0; i < qMin(HAND_SIZE, cards.size()); ++i) {
        m_cards.append(cards[i]);
    }
}

bool Hand::addCard(const Card& card)
{
    // Vérifier si la main est déjà complète
    if (m_cards.size() >= HAND_SIZE) {
        return false;
    }

    // Vérifier si la carte existe déjà dans la main
    for (const Card& existingCard : m_cards) {
        if (existingCard == card) {
            return false;
        }
    }

    m_cards.append(card);
    return true;
}

QVector<Card> Hand::getCards() const
{
    return m_cards;
}

bool Hand::isComplete() const
{
    return m_cards.size() == HAND_SIZE;
}

bool Hand::isValid() const
{
    // Vérifier qu'il n'y a pas de doublons
    QSet<QString> uniqueCards;

    for (const Card& card : m_cards) {
        QString cardStr = card.toString();
        if (uniqueCards.contains(cardStr)) {
            return false;
        }
        uniqueCards.insert(cardStr);
    }

    return true;
}

QString Hand::toString() const
{
    QStringList cardStrings;

    for (const Card& card : m_cards) {
        cardStrings.append(card.toString());
    }

    return cardStrings.join(" ");
}

Hand Hand::fromString(const QString& str)
{
    Hand hand;
    QStringList cardStrings = str.split(" ", Qt::SkipEmptyParts);

    for (const QString& cardStr : cardStrings) {
        try {
            Card card = Card::fromString(cardStr);
            hand.addCard(card);
        } catch (const std::invalid_argument&) {
            // Ignorer les cartes invalides
        }
    }

    return hand;
}
