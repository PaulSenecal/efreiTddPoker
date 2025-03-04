#include "game.h"

Game::Game()
{
}

void Game::setHand1(const Hand& hand)
{
    m_hand1 = hand;
}

void Game::setHand2(const Hand& hand)
{
    m_hand2 = hand;
}

Hand Game::getHand1() const
{
    return m_hand1;
}

Hand Game::getHand2() const
{
    return m_hand2;
}

Game::Result Game::determineWinner() const
{
    Result result;

    // Vérifier si les mains sont complètes
    if (!m_hand1.isComplete() || !m_hand2.isComplete()) {
        result.winner = 0;
        result.description = "Les deux mains doivent être complètes (5 cartes chacune).";
        return result;
    }

    // Évaluer les deux mains
    Evaluator::HandScore score1 = Evaluator::evaluate(m_hand1);
    Evaluator::HandScore score2 = Evaluator::evaluate(m_hand2);

    result.hand1Type = score1.type;
    result.hand2Type = score2.type;

    // Comparer les scores
    int comparison = Evaluator::compareHands(m_hand1, m_hand2);
    result.winner = (comparison > 0) ? 1 : ((comparison < 0) ? 2 : 0);

    // Préparer la description
    QString hand1TypeStr = Evaluator::handTypeToString(score1.type);
    QString hand2TypeStr = Evaluator::handTypeToString(score2.type);

    if (result.winner == 1) {
        result.description = QString("Le joueur 1 gagne avec %1 contre %2 du joueur 2.")
        .arg(hand1TypeStr)
            .arg(hand2TypeStr);
    } else if (result.winner == 2) {
        result.description = QString("Le joueur 2 gagne avec %1 contre %2 du joueur 1.")
        .arg(hand2TypeStr)
            .arg(hand1TypeStr);
    } else {
        result.description = QString("Égalité. Les deux joueurs ont %1.")
                                 .arg(hand1TypeStr);
    }

    return result;
}

Game Game::fromString(const QString& str)
{
    Game game;
    QStringList parts = str.split('|');

    if (parts.size() >= 1) {
        Hand hand1 = Hand::fromString(parts[0].trimmed());
        game.setHand1(hand1);
    }

    if (parts.size() >= 2) {
        Hand hand2 = Hand::fromString(parts[1].trimmed());
        game.setHand2(hand2);
    }

    return game;
}

QString Game::toString() const
{
    return QString("%1 | %2").arg(m_hand1.toString()).arg(m_hand2.toString());
}
