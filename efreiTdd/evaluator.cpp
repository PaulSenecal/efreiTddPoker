#include "evaluator.h"
#include <algorithm>
#include <QMap>
/*to do changer la logique sur les carte haute car gaggne sur la pair actuellement*/
/* Quinte basse (12345) vs Quinte haute ( 10 11 12 13 14 ) - nest pas bonne*/
bool Evaluator::HandScore::operator<(const HandScore& other) const
{
    // Comparer d'abord les types de mains
    if (type != other.type) {
        // Cast en int pour comparer les valeurs d'enum (HighCard = 0, RoyalFlush = 9)
        return static_cast<int>(type) < static_cast<int>(other.type);
    }

    // Si même type, comparer les tiebreakers
    for (int i = 0; i < qMin(tiebreakers.size(), other.tiebreakers.size()); ++i) {
        if (tiebreakers[i] != other.tiebreakers[i]) {
            return tiebreakers[i] < other.tiebreakers[i];
        }
    }

    return false; // Égalité parfaite
}


bool Evaluator::HandScore::operator>(const HandScore& other) const
{
    return other < *this;
}

bool Evaluator::HandScore::operator==(const HandScore& other) const
{
    if (type != other.type) {
        return false;
    }

    if (tiebreakers.size() != other.tiebreakers.size()) {
        return false;
    }

    for (int i = 0; i < tiebreakers.size(); ++i) {
        if (tiebreakers[i] != other.tiebreakers[i]) {
            return false;
        }
    }

    return true;
}

QVector<Card> Evaluator::sortByRank(const QVector<Card>& cards)
{
    QVector<Card> sorted = cards;
    std::sort(sorted.begin(), sorted.end(), [](const Card& a, const Card& b) {
        return static_cast<int>(a.getRank()) > static_cast<int>(b.getRank());
    });
    return sorted;
}

bool Evaluator::allSameSuit(const QVector<Card>& cards)
{
    if (cards.isEmpty()) {
        return false;
    }

    Card::Suit suit = cards[0].getSuit();
    for (const Card& card : cards) {
        if (card.getSuit() != suit) {
            return false;
        }
    }

    return true;
}

bool Evaluator::isSequential(const QVector<Card>& cards)
{
    if (cards.size() < 2) {
        return true;
    }

    QVector<Card> sorted = sortByRank(cards);

    // Vérifier si c'est une quinte basse (A,2,3,4,5)
    if (isLowStraight(sorted)) {
        return true;
    }

    // Vérification standard
    for (int i = 0; i < sorted.size() - 1; ++i) {
        int currentRank = static_cast<int>(sorted[i].getRank());
        int nextRank = static_cast<int>(sorted[i+1].getRank());

        if (currentRank != nextRank + 1) {
            return false;
        }
    }

    return true;
}

bool Evaluator::isLowStraight(const QVector<Card>& sortedCards)
{
    if (sortedCards.size() != 5) {
        return false;
    }

    // Pour une quinte basse (A,2,3,4,5), on vérifie:
    return static_cast<int>(sortedCards[0].getRank()) == static_cast<int>(Card::Rank::Ace) &&
           static_cast<int>(sortedCards[1].getRank()) == static_cast<int>(Card::Rank::Five) &&
           static_cast<int>(sortedCards[2].getRank()) == static_cast<int>(Card::Rank::Four) &&
           static_cast<int>(sortedCards[3].getRank()) == static_cast<int>(Card::Rank::Three) &&
           static_cast<int>(sortedCards[4].getRank()) == static_cast<int>(Card::Rank::Two);
}


QVector<int> Evaluator::getRankCounts(const QVector<Card>& cards)
{
    QMap<int, int> rankCountMap;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        rankCountMap[rank]++;
    }

    // Convertir la map en vector et trier par nombre d'occurrences puis par rang
    QVector<QPair<int, int>> rankCounts;
    for (auto it = rankCountMap.begin(); it != rankCountMap.end(); ++it) {
        rankCounts.append(qMakePair(it.value(), it.key()));
    }

    // Trier par nombre d'occurrences (descendant) puis par rang (descendant)
    std::sort(rankCounts.begin(), rankCounts.end(), [](const QPair<int, int>& a, const QPair<int, int>& b) {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second > b.second;
    });

    // Extraire les rangs dans l'ordre
    QVector<int> result;
    for (const auto& pair : rankCounts) {
        result.append(pair.second);
    }

    return result;
}

// Vérification des types de mains

bool Evaluator::isRoyalFlush(const QVector<Card>& cards)
{
    if (!allSameSuit(cards)) {
        return false;
    }

    QVector<Card> sorted = sortByRank(cards);

    return static_cast<int>(sorted[0].getRank()) == static_cast<int>(Card::Rank::Ace) &&
           static_cast<int>(sorted[1].getRank()) == static_cast<int>(Card::Rank::King) &&
           static_cast<int>(sorted[2].getRank()) == static_cast<int>(Card::Rank::Queen) &&
           static_cast<int>(sorted[3].getRank()) == static_cast<int>(Card::Rank::Jack) &&
           static_cast<int>(sorted[4].getRank()) == static_cast<int>(Card::Rank::Ten);
}

bool Evaluator::isStraightFlush(const QVector<Card>& cards)
{
    // Une quinte flush est une main qui forme à la fois une quinte et une couleur,
    // mais qui n'est pas une quinte flush royale
    return allSameSuit(cards) && isSequential(cards) && !isRoyalFlush(cards);
}
bool Evaluator::isFourOfAKind(const QVector<Card>& cards)
{
    QVector<int> rankCounts = getRankCounts(cards);

    // Vérifier le nombre d'occurrences du premier rang
    QMap<int, int> countMap;
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 4) {
            return true;
        }
    }

    return false;
}

bool Evaluator::isFullHouse(const QVector<Card>& cards)
{
    QMap<int, int> countMap;
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    bool hasThree = false;
    bool hasTwo = false;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 3) {
            hasThree = true;
        } else if (it.value() == 2) {
            hasTwo = true;
        }
    }

    return hasThree && hasTwo;
}

bool Evaluator::isFlush(const QVector<Card>& cards)
{
    return allSameSuit(cards);
}

bool Evaluator::isStraight(const QVector<Card>& cards)
{
    return isSequential(cards);
}

bool Evaluator::isThreeOfAKind(const QVector<Card>& cards)
{
    QMap<int, int> countMap;
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 3) {
            return true;
        }
    }

    return false;
}

bool Evaluator::isTwoPair(const QVector<Card>& cards)
{
    QMap<int, int> countMap;
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    int pairCount = 0;
    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 2) {
            pairCount++;
        }
    }

    return pairCount == 2;
}

bool Evaluator::isOnePair(const QVector<Card>& cards)
{
    // Comptage des occurrences des rangs
    QMap<int, int> countMap;
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    // Compter exactement une paire et pas plus
    int pairCount = 0;
    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 2) {
            pairCount++;
        } else if (it.value() > 2) {
            // Si une carte apparaît plus de 2 fois, ce n'est pas une seule paire
            return false;
        }
    }

    return pairCount == 1;
}

// Calcul des tiebreakers

QVector<int> Evaluator::getRoyalFlushTiebreakers(const QVector<Card>& cards)
{
    // Toutes les quintes flush royales sont égales
    return QVector<int>();
}

QVector<int> Evaluator::getStraightFlushTiebreakers(const QVector<Card>& cards)
{
    QVector<Card> sorted = sortByRank(cards);
    QVector<int> tiebreakers;

    // Si c'est une quinte basse (A,2,3,4,5)
    if (isLowStraight(sorted)) {
        tiebreakers.append(static_cast<int>(Card::Rank::Five)); // La carte haute est le 5
    } else {
        tiebreakers.append(static_cast<int>(sorted[0].getRank())); // La carte la plus haute
    }

    return tiebreakers;
}

QVector<int> Evaluator::getFourOfAKindTiebreakers(const QVector<Card>& cards)
{
    QVector<int> tiebreakers;
    QMap<int, int> countMap;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    int fourOfAKindRank = -1;
    int             kicker = -1;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 4) {
            fourOfAKindRank = it.key();
        } else {
            kicker = it.key();
        }
    }

    tiebreakers.append(fourOfAKindRank);
    tiebreakers.append(kicker);

    return tiebreakers;
}

QVector<int> Evaluator::getFullHouseTiebreakers(const QVector<Card>& cards)
{
    QVector<int> tiebreakers;
    QMap<int, int> countMap;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    int threeOfAKindRank = -1;
    int pairRank = -1;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 3) {
            threeOfAKindRank = it.key();
        } else if (it.value() == 2) {
            pairRank = it.key();
        }
    }

    tiebreakers.append(threeOfAKindRank);
    tiebreakers.append(pairRank);

    return tiebreakers;
}

QVector<int> Evaluator::getFlushTiebreakers(const QVector<Card>& cards)
{
    QVector<Card> sorted = sortByRank(cards);
    QVector<int> tiebreakers;

    // Les 5 cartes dans l'ordre pour départager
    for (const Card& card : sorted) {
        tiebreakers.append(static_cast<int>(card.getRank()));
    }

    return tiebreakers;
}

QVector<int> Evaluator::getStraightTiebreakers(const QVector<Card>& cards)
{
    QVector<Card> sorted = sortByRank(cards);
    QVector<int> tiebreakers;

    // Si c'est une quinte basse (A,2,3,4,5), la carte haute est le 5, pas l'As
    if (isLowStraight(sorted)) {
        // Valeur 5 comme carte haute (considérant que l'As est utilisé comme carte basse)
        tiebreakers.append(static_cast<int>(Card::Rank::Five));
    } else {
        // Sinon la carte haute est la première carte triée
        tiebreakers.append(static_cast<int>(sorted[0].getRank()));
    }

    return tiebreakers;
}

QVector<int> Evaluator::getThreeOfAKindTiebreakers(const QVector<Card>& cards)
{
    QVector<int> tiebreakers;
    QMap<int, int> countMap;
    QVector<int> kickers;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    int threeOfAKindRank = -1;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 3) {
            threeOfAKindRank = it.key();
        } else {
            kickers.append(it.key());
        }
    }

    // Trier les kickers par rang décroissant
    std::sort(kickers.begin(), kickers.end(), std::greater<int>());

    tiebreakers.append(threeOfAKindRank);
    // Ajouter chaque kicker individuellement
    for (int kicker : kickers) {
        tiebreakers.append(kicker);
    }

    return tiebreakers;
}

QVector<int> Evaluator::getTwoPairTiebreakers(const QVector<Card>& cards)
{
    QVector<int> tiebreakers;
    QMap<int, int> countMap;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    QVector<int> pairs;
    int kicker = -1;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 2) {
            pairs.append(it.key());
        } else {
            kicker = it.key();
        }
    }

    // Trier les paires par rang décroissant
    std::sort(pairs.begin(), pairs.end(), std::greater<int>());

    for (int pair : pairs) {
        tiebreakers.append(pair);
    }
    tiebreakers.append(kicker);

    return tiebreakers;
}

QVector<int> Evaluator::getOnePairTiebreakers(const QVector<Card>& cards)
{
    QVector<int> tiebreakers;
    QMap<int, int> countMap;
    QVector<int> kickers;

    // Compter les occurrences de chaque rang
    for (const Card& card : cards) {
        int rank = static_cast<int>(card.getRank());
        countMap[rank]++;
    }

    int pairRank = -1;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (it.value() == 2) {
            pairRank = it.key();
        } else {
            kickers.append(it.key());
        }
    }

    // Trier les kickers par rang décroissant
    std::sort(kickers.begin(), kickers.end(), std::greater<int>());

    tiebreakers.append(pairRank);
    for (int kicker : kickers) {
        tiebreakers.append(kicker);
    }

    return tiebreakers;
}
QVector<int> Evaluator::getHighCardTiebreakers(const QVector<Card>& cards)
{
    QVector<Card> sorted = sortByRank(cards);
    QVector<int> tiebreakers;

    // Les 5 cartes dans l'ordre pour départager
    for (const Card& card : sorted) {
        tiebreakers.append(static_cast<int>(card.getRank()));
    }

    return tiebreakers;
}


Evaluator::HandScore Evaluator::evaluate(const Hand& hand)
{
    HandScore score;
    QVector<Card> cards = hand.getCards();

    // Vérifier que la main est complète
    if (cards.size() != Hand::HAND_SIZE) {
        score.type = HandType::HighCard;
        score.tiebreakers = getHighCardTiebreakers(cards);
        return score;
    }

    // Vérifier les types de mains du plus fort au plus faible
    if (isRoyalFlush(cards)) {
        score.type = HandType::RoyalFlush;
        score.tiebreakers = getRoyalFlushTiebreakers(cards);
    }
    else if (isStraightFlush(cards)) {
        score.type = HandType::StraightFlush;
        score.tiebreakers = getStraightFlushTiebreakers(cards);
    }
    else if (isFourOfAKind(cards)) {
        score.type = HandType::FourOfAKind;
        score.tiebreakers = getFourOfAKindTiebreakers(cards);
    }
    else if (isFullHouse(cards)) {
        score.type = HandType::FullHouse;
        score.tiebreakers = getFullHouseTiebreakers(cards);
    }
    else if (isFlush(cards)) {
        score.type = HandType::Flush;
        score.tiebreakers = getFlushTiebreakers(cards);
    }
    else if (isStraight(cards)) {
        score.type = HandType::Straight;
        score.tiebreakers = getStraightTiebreakers(cards);
    }
    else if (isThreeOfAKind(cards)) {
        score.type = HandType::ThreeOfAKind;
        score.tiebreakers = getThreeOfAKindTiebreakers(cards);
    }
    else if (isTwoPair(cards)) {
        score.type = HandType::TwoPair;
        score.tiebreakers = getTwoPairTiebreakers(cards);
    }
    else if (isOnePair(cards)) {
        score.type = HandType::OnePair;
        score.tiebreakers = getOnePairTiebreakers(cards);
    }
    else {
        score.type = HandType::HighCard;
        score.tiebreakers = getHighCardTiebreakers(cards);
    }

    return score;
}

int Evaluator::compareHands(const Hand& hand1, const Hand& hand2)
{
    // qDebug() << "Hand1: " << static_cast<int>(score1.type) << ", Hand2: " << static_cast<int>(score2.type);
    HandScore score1 = evaluate(hand1);
    HandScore score2 = evaluate(hand2);

    if (score1 > score2) {
        return 1;
    }
    else if (score1 < score2) {
        return -1;
    }
    else {
        return 0;
    }
}

QString Evaluator::handTypeToString(HandType type)
{
    switch (type) {
    case HandType::RoyalFlush:    return "Quinte Flush Royale";
    case HandType::StraightFlush: return "Quinte Flush";
    case HandType::FourOfAKind:   return "Carré";
    case HandType::FullHouse:     return "Full";
    case HandType::Flush:         return "Couleur";
    case HandType::Straight:      return "Quinte";
    case HandType::ThreeOfAKind:  return "Brelan";
    case HandType::TwoPair:       return "Deux Paires";
    case HandType::OnePair:       return "Paire";
    case HandType::HighCard:      return "Carte Haute";
    default:                       return "Inconnu";
    }
}
