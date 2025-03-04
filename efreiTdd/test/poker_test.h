#ifndef POKER_TEST_H
#define POKER_TEST_H

#include "../hand.h"
#include "../evaluator.h"
#include <QtTest>
#include "card.h"
#include "game.h"

class PokerTest : public QObject
{
    Q_OBJECT

public:
    PokerTest(QObject *parent = nullptr);

    // Méthode pour exécuter tous les tests et retourner le résultat
    bool runAllTests();

private slots:
    // Tests automatiques (exécutés par QTest)
    void testWinningHands();
    void testLosingHands();
    void testTieHands();
    void testEdgeCases();

private:
    // Méthode d'affichage
    void displayTestResult(const QString& testName, bool success);

    // Variables pour le suivi des tests
    int m_totalTests;
    int m_passedTests;
};

#endif // POKER_TEST_H 
