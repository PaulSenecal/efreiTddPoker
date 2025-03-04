#ifndef POKER_TEST_H
#define POKER_TEST_H

#include "../hand.h"
#include "../evaluator.h"
#include <QString>

class PokerTest {
public:
    static bool runTests();

private:
    static bool testWinningHands();
    static bool testLosingHands();
    static void displayTestResult(const QString& testName, bool success);
    static QString getHandDescription(const Hand& hand);
};

#endif // POKER_TEST_H 