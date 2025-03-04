#include "poker_test.h"

PokerTest::PokerTest(QObject *parent) : QObject(parent), m_totalTests(0), m_passedTests(0)
{
}

bool PokerTest::runAllTests()
{
    m_totalTests = 0;
    m_passedTests = 0;

    QTextStream out(stdout);
    out << "\n=== Tests de Poker ===\n";

    // Exécution des tests avec QTest
    QTest::qExec(this, QStringList() << "" << "-silent");

    // Affichage du résultat final
    out << "\nRésumé: " << m_passedTests << "/" << m_totalTests << " tests réussis";
    out << " (" << (m_passedTests * 100 / m_totalTests) << "%)\n";

    return (m_passedTests == m_totalTests);
}

void PokerTest::displayTestResult(const QString& testName, bool success)
{
    QTextStream out(stdout);
    m_totalTests++;

    if (success) {
        m_passedTests++;
        out << "  ✓ " << testName << "\n";
    } else {
        out << "  ✗ " << testName << " - eCHEC\n";
    }
}

void PokerTest::testWinningHands()
{
    QTextStream out(stdout);
    out << "\nTest des mains gagnantes:\n";
    bool success;

    // Test 1: Quinte Flush Royale vs Quinte Flush
    Hand royalFlush = Hand::fromString("AS KS QS JS TS");
    Hand straightFlush = Hand::fromString("9H 8H 7H 6H 5H");

    success = (Evaluator::compareHands(royalFlush, straightFlush) > 0);
    displayTestResult("Quinte Flush Royale vs Quinte Flush", success);
    QVERIFY(success);

    // Test 2: Carré vs Full
    Hand fourOfAKind = Hand::fromString("AS AH AC AD KS");
    Hand fullHouse = Hand::fromString("KS KH KC AS AH");

    success = (Evaluator::compareHands(fourOfAKind, fullHouse) > 0);
    displayTestResult("Carré vs Full", success);
    QVERIFY(success);

    // Test 3: Full vs Couleur
    Hand fullHouse2 = Hand::fromString("QS QH QC AS AH");
    Hand flush = Hand::fromString("KS QS 9S 5S 3S");

    success = (Evaluator::compareHands(fullHouse2, flush) > 0);
    displayTestResult("Full vs Couleur", success);
    QVERIFY(success);

    // Test 4: Couleur vs Quinte
    Hand flush2 = Hand::fromString("AS QS 9S 5S 3S");
    Hand straight = Hand::fromString("KH QD JS TC 9H");

    success = (Evaluator::compareHands(flush2, straight) > 0);
    displayTestResult("Couleur vs Quinte", success);
    QVERIFY(success);

    // Test 5: Quinte vs Brelan
    Hand straight2 = Hand::fromString("QH JD TS 9C 8H");
    Hand threeOfAKind = Hand::fromString("KS KH KC 9S 2H");

    success = (Evaluator::compareHands(straight2, threeOfAKind) > 0);
    displayTestResult("Quinte vs Brelan", success);
    QVERIFY(success);

    // Test 6: Brelan vs Deux Paires
    Hand threeOfAKind2 = Hand::fromString("QS QH QC 9S 2H");
    Hand twoPair = Hand::fromString("KS KH JS JH 5C");

    success = (Evaluator::compareHands(threeOfAKind2, twoPair) > 0);
    displayTestResult("Brelan vs Deux Paires", success);
    QVERIFY(success);

    // Test 7: Deux Paires vs Paire (avec paire plus haute)
    Hand twoPair2 = Hand::fromString("AS AH KS KH 5C");
    Hand onePair = Hand::fromString("QS QH JC TD 9S");

    success = (Evaluator::compareHands(twoPair2, onePair) > 0);
    displayTestResult("Deux Paires vs Paire", success);
    QVERIFY(success);

    // Test 8: Départage entre deux carrés (carré plus élevé)
    Hand fourAces = Hand::fromString("AS AH AC AD 2S");
    Hand fourKings = Hand::fromString("KS KH KC KD QS");

    success = (Evaluator::compareHands(fourAces, fourKings) > 0);
    displayTestResult("Carré d'As vs Carré de Rois", success);
    QVERIFY(success);

    // Test 9: Départage entre deux fulls (brelan plus élevé)
    Hand fullHouseAces = Hand::fromString("AS AH AC KS KH");
    Hand fullHouseKings = Hand::fromString("KD KC KS QS QH");

    success = (Evaluator::compareHands(fullHouseAces, fullHouseKings) > 0);
    displayTestResult("Full aux As vs Full aux Rois", success);
    QVERIFY(success);

    // Test 10: Départage entre deux fulls (même brelan, paire plus élevée)
    Hand fullHouseAcesKings = Hand::fromString("AS AH AC KS KH");
    Hand fullHouseAcesQueens = Hand::fromString("AD AS AH QS QH");

    success = (Evaluator::compareHands(fullHouseAcesKings, fullHouseAcesQueens) > 0);
    displayTestResult("Full aux As par les Rois vs Full aux As par les Dames", success);
    QVERIFY(success);
}

void PokerTest::testLosingHands()
{
    QTextStream out(stdout);
    out << "\nTest des mains perdantes:\n";
    bool success;

    // Test 1: Paire vs Double Paire
    Hand onePair = Hand::fromString("AS AH 3C 4D 5S");
    Hand twoPair = Hand::fromString("KS KH QS QH 2C");

    success = (Evaluator::compareHands(onePair, twoPair) < 0);
    displayTestResult("Paire vs Double Paire", success);
    QVERIFY(success);

    // Test 2: Carte Haute vs Paire
    Hand highCard = Hand::fromString("AS KH 7C 5D 2S");
    Hand pair = Hand::fromString("QS QH JC TD 9S");

    success = (Evaluator::compareHands(highCard, pair) < 0);
    displayTestResult("Carte Haute vs Paire", success);
    QVERIFY(success);

    // Test 3: Couleur basse vs Couleur haute
    Hand lowFlush = Hand::fromString("9S 7S 5S 3S 2S");
    Hand highFlush = Hand::fromString("KH QH 9H 5H 3H");

    success = (Evaluator::compareHands(lowFlush, highFlush) < 0);
    displayTestResult("Couleur basse vs Couleur haute", success);
    QVERIFY(success);

    // Test 4: Quinte basse vs Quinte haute
    Hand lowStraight = Hand::fromString("6H 5D 4S 3C 2H");
    Hand highStraight = Hand::fromString("KH QD JS TC 9H");

    success = (Evaluator::compareHands(lowStraight, highStraight) < 0);
    displayTestResult("Quinte basse vs Quinte haute", success);
    QVERIFY(success);

    // Test 5: Quinte basse (As comme carte basse) vs Quinte moyenne
    Hand aceLowStraight = Hand::fromString("5H 4D 3S 2C AS");
    Hand mediumStraight = Hand::fromString("9H 8D 7S 6C 5H");

    success = (Evaluator::compareHands(aceLowStraight, mediumStraight) < 0);
    displayTestResult("Quinte basse (As bas) vs Quinte moyenne", success);
    QVERIFY(success);

    // Test 6: Brelan faible vs Brelan fort
    Hand lowThreeOfAKind = Hand::fromString("5S 5H 5C KS QH");
    Hand highThreeOfAKind = Hand::fromString("KD KC KH 5D 2C");

    success = (Evaluator::compareHands(lowThreeOfAKind, highThreeOfAKind) < 0);
    displayTestResult("Brelan faible vs Brelan fort", success);
    QVERIFY(success);

    // Test 7: Deux paires avec kicker faible vs Deux paires avec kicker fort
    Hand twoPairLowKicker = Hand::fromString("AS AH KS KH 2C");
    Hand twoPairHighKicker = Hand::fromString("AD AC KD KC QS");

    success = (Evaluator::compareHands(twoPairLowKicker, twoPairHighKicker) < 0);
    displayTestResult("Deux paires avec kicker faible vs kicker fort", success);
    QVERIFY(success);

    // Test 8: Paire faible vs Paire forte
    Hand lowPair = Hand::fromString("5S 5H AC KD QS");
    Hand highPair = Hand::fromString("KS KH 5C 4D 2S");

    success = (Evaluator::compareHands(lowPair, highPair) < 0);
    displayTestResult("Paire faible vs Paire forte", success);
    QVERIFY(success);

    // Test 9: Carte haute faible vs Carte haute forte (comparaison 2ème carte)
    Hand highCardLow2nd = Hand::fromString("AS QH 9C 7D 3S");
    Hand highCardHigh2nd = Hand::fromString("AD KH 8C 5D 2S");

    success = (Evaluator::compareHands(highCardLow2nd, highCardHigh2nd) < 0);
    displayTestResult("Carte haute (2ème faible) vs Carte haute (2ème forte)", success);
    QVERIFY(success);

    // Test 10: Carte haute équivalente jusqu'à la dernière carte
    Hand highCardLowLast = Hand::fromString("AS KH QC JD 2S");
    Hand highCardHighLast = Hand::fromString("AC KC QH JS 3D");

    success = (Evaluator::compareHands(highCardLowLast, highCardHighLast) < 0);
    displayTestResult("Carte haute (dernière faible) vs Carte haute (dernière forte)", success);
    QVERIFY(success);
}

void PokerTest::testTieHands()
{
    QTextStream out(stdout);
    out << "\nTest des mains à egalite:\n";
    bool success;

    // Test 1: Deux Quinte Flush Royale (égalité parfaite)
    Hand royalFlushHearts = Hand::fromString("AH KH QH JH TH");
    Hand royalFlushSpades = Hand::fromString("AS KS QS JS TS");

    success = (Evaluator::compareHands(royalFlushHearts, royalFlushSpades) == 0);
    displayTestResult("Quinte Flush Royale cœur = Quinte Flush Royale pique", success);
    QVERIFY(success);

    // Test 2: Deux Quinte Flush identiques
    Hand straightFlushHearts = Hand::fromString("9H 8H 7H 6H 5H");
    Hand straightFlushSpades = Hand::fromString("9S 8S 7S 6S 5S");

    success = (Evaluator::compareHands(straightFlushHearts, straightFlushSpades) == 0);
    displayTestResult("Quinte Flush 9 cœur = Quinte Flush 9 pique", success);
    QVERIFY(success);

    // Test 3: Deux carrés identiques
    Hand fourAcesHearts = Hand::fromString("AS AH AC AD KS");
    Hand fourAcesDiamonds = Hand::fromString("AS AH AC AD KH");

    success = (Evaluator::compareHands(fourAcesHearts, fourAcesDiamonds) == 0);
    displayTestResult("Carré d'As (kicker roi pique) = Carré d'As (kicker roi cœur)", success);
    QVERIFY(success);

    // Test 4: Deux Full identiques
    Hand fullAcesKings1 = Hand::fromString("AS AH AC KS KH");
    Hand fullAcesKings2 = Hand::fromString("AD AS AH KD KC");

    success = (Evaluator::compareHands(fullAcesKings1, fullAcesKings2) == 0);
    displayTestResult("Full aux As par les Rois = Full aux As par les Rois", success);
    QVERIFY(success);

    // Test 5: Deux couleurs identiques en valeur (couleurs différentes)
    Hand flushSpadesAceHigh = Hand::fromString("AS KS 9S 5S 3S");
    Hand flushHeartsAceHigh = Hand::fromString("AH KH 9H 5H 3H");

    success = (Evaluator::compareHands(flushSpadesAceHigh, flushHeartsAceHigh) == 0);
    displayTestResult("Couleur pique As high = Couleur cœur As high", success);
    QVERIFY(success);

    // Test 6: Deux quintes identiques
    Hand straightAceHigh1 = Hand::fromString("AS KH QC JD TS");
    Hand straightAceHigh2 = Hand::fromString("AD KC QH JS TD");

    success = (Evaluator::compareHands(straightAceHigh1, straightAceHigh2) == 0);
    displayTestResult("Quinte As high #1 = Quinte As high #2", success);
    QVERIFY(success);
}

void PokerTest::testEdgeCases()
{
    QTextStream out(stdout);
    out << "\nTest des cas particuliers:\n";
    bool success;

    // Test 1: Quinte basse (As comme carte basse) vs Quinte haute (As comme carte haute)
    Hand aceLowStraight = Hand::fromString("5H 4D 3S 2C AS");
    Hand aceHighStraight = Hand::fromString("AH KD QS JC TH");

    success = (Evaluator::compareHands(aceLowStraight, aceHighStraight) < 0);
    displayTestResult("Quinte basse (As bas) vs Quinte haute (As haut)", success);
    QVERIFY(success);

    // Test 2: Quinte Flush basse (As comme carte basse) vs Quinte Flush haute (mais pas royale)
    Hand aceLowStraightFlush = Hand::fromString("5S 4S 3S 2S AS");
    Hand kingHighStraightFlush = Hand::fromString("KH QH JH TH 9H");

    success = (Evaluator::compareHands(aceLowStraightFlush, kingHighStraightFlush) < 0);
    displayTestResult("Quinte Flush basse (As bas) vs Quinte Flush K high", success);
    QVERIFY(success);

    // Test 3: Deux mains avec As mais utilisé différemment (paire vs carte haute)
    Hand pairOfAces = Hand::fromString("AS AH 5C 3D 2S");
    Hand aceHighCard = Hand::fromString("AC KH QS JD 9C");

    success = (Evaluator::compareHands(pairOfAces, aceHighCard) > 0);
    displayTestResult("Paire d'As vs Carte haute As", success);
    QVERIFY(success);

    // Test 4: Full vs Brelan de même rang
    Hand fullThreesOverTwos = Hand::fromString("3S 3H 3C 2S 2H");
    Hand threeOfAKindThrees = Hand::fromString("3D 3S 3H KD QC");

    success = (Evaluator::compareHands(fullThreesOverTwos, threeOfAKindThrees) > 0);
    displayTestResult("Full aux 3 par les 2 vs Brelan de 3", success);
    QVERIFY(success);

    // Test 5: Carré vs Double paire de mêmes rangs
    Hand fourOfAKindTwos = Hand::fromString("2S 2H 2C 2D KS");
    Hand twoPairTwosAndKings = Hand::fromString("2S 2H KS KH QC");

    success = (Evaluator::compareHands(fourOfAKindTwos, twoPairTwosAndKings) > 0);
    displayTestResult("Carré de 2 vs Deux paires 2 et Rois", success);
    QVERIFY(success);
}
