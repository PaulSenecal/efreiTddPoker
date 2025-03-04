#include "poker_test.h"
#include <QTextStream>

bool PokerTest::runTests() {
    QTextStream out(stdout);
    out << "\n=== Début des tests ===\n\n";
    
    bool allTestsPassed = true;
    allTestsPassed &= testWinningHands();
    allTestsPassed &= testLosingHands();
    
    out << "\n=== Fin des tests ===\n";
    out << "Résultat final: " << (allTestsPassed ? "SUCCÈS" : "ÉCHEC") << "\n\n";
    
    return allTestsPassed;
}

bool PokerTest::testWinningHands()
{
    QTextStream out(stdout);
    out << "Test des mains gagnantes:\n";
    bool success = true;

    // Test 1: Quinte Flush Royale vs Quinte Flush
    Hand royalFlush = Hand::fromString("AS KS QS JS TS");
    Hand straightFlush = Hand::fromString("9H 8H 7H 6H 5H");

    success &= (Evaluator::compareHands(royalFlush, straightFlush) > 0);
    displayTestResult("Quinte Flush Royale vs Quinte Flush", success);

    // Test 2: Carré vs Full
    Hand fourOfAKind = Hand::fromString("AS AH AC AD KS");
    Hand fullHouse = Hand::fromString("KS KH KC AS AH");

    success &= (Evaluator::compareHands(fourOfAKind, fullHouse) > 0);
    displayTestResult("Carré vs Full", success);

    // Test 3: Full vs Couleur
    Hand fullHouse2 = Hand::fromString("QS QH QC AS AH");
    Hand flush = Hand::fromString("KS QS 9S 5S 3S");

    success &= (Evaluator::compareHands(fullHouse2, flush) > 0);
    displayTestResult("Full vs Couleur", success);

    // Test 4: Couleur vs Quinte
    Hand flush2 = Hand::fromString("AS QS 9S 5S 3S");
    Hand straight = Hand::fromString("KH QD JS TC 9H");

    success &= (Evaluator::compareHands(flush2, straight) > 0);
    displayTestResult("Couleur vs Quinte", success);

    // Test 5: Quinte vs Brelan
    Hand straight2 = Hand::fromString("QH JD TS 9C 8H");
    Hand threeOfAKind = Hand::fromString("KS KH KC 9S 2H");

    success &= (Evaluator::compareHands(straight2, threeOfAKind) > 0);
    displayTestResult("Quinte vs Brelan", success);

    // Test 6: Brelan vs Deux Paires
    Hand threeOfAKind2 = Hand::fromString("QS QH QC 9S 2H");
    Hand twoPair = Hand::fromString("KS KH JS JH 5C");

    success &= (Evaluator::compareHands(threeOfAKind2, twoPair) > 0);
    displayTestResult("Brelan vs Deux Paires", success);

    // Test 7: Deux Paires vs Paire (avec paire plus haute)
    Hand twoPair2 = Hand::fromString("AS AH KS KH 5C");
    Hand onePair = Hand::fromString("QS QH JC TD 9S");

    success &= (Evaluator::compareHands(twoPair2, onePair) > 0);
    displayTestResult("Deux Paires vs Paire", success);

    // Test 8: Départage entre deux carrés (carré plus élevé)
    Hand fourAces = Hand::fromString("AS AH AC AD 2S");
    Hand fourKings = Hand::fromString("KS KH KC KD QS");

    success &= (Evaluator::compareHands(fourAces, fourKings) > 0);
    displayTestResult("Carré d'As vs Carré de Rois", success);

    // Test 9: Départage entre deux fulls (brelan plus élevé)
    Hand fullHouseAces = Hand::fromString("AS AH AC KS KH");
    Hand fullHouseKings = Hand::fromString("KD KC KS QS QH");

    success &= (Evaluator::compareHands(fullHouseAces, fullHouseKings) > 0);
    displayTestResult("Full aux As vs Full aux Rois", success);

    // Test 10: Départage entre deux fulls (même brelan, paire plus élevée)
    Hand fullHouseAcesKings = Hand::fromString("AS AH AC KS KH");
    Hand fullHouseAcesQueens = Hand::fromString("AD AS AH QS QH");

    success &= (Evaluator::compareHands(fullHouseAcesKings, fullHouseAcesQueens) > 0);
    displayTestResult("Full aux As par les Rois vs Full aux As par les Dames", success);

    return success;
}

bool PokerTest::testLosingHands()
{
    QTextStream out(stdout);
    out << "\nTest des mains perdantes:\n";
    bool success = true;

    // Test 1: Paire vs Double Paire
    Hand onePair = Hand::fromString("AS AH 3C 4D 5S");
    Hand twoPair = Hand::fromString("KS KH QS QH 2C");

    success &= (Evaluator::compareHands(onePair, twoPair) < 0);
    displayTestResult("Paire vs Double Paire", success);

    // Test 2: Carte Haute vs Paire
    Hand highCard = Hand::fromString("AS KH 7C 5D 2S");
    Hand pair = Hand::fromString("QS QH JC TD 9S");

    success &= (Evaluator::compareHands(highCard, pair) < 0);
    displayTestResult("Carte Haute vs Paire", success);

    // Test 3: Couleur basse vs Couleur haute
    Hand lowFlush = Hand::fromString("9S 7S 5S 3S 2S");
    Hand highFlush = Hand::fromString("KH QH 9H 5H 3H");

    success &= (Evaluator::compareHands(lowFlush, highFlush) < 0);
    displayTestResult("Couleur basse vs Couleur haute", success);

    // Test 4: Quinte basse vs Quinte haute
    Hand lowStraight = Hand::fromString("6H 5D 4S 3C 2H");
    Hand highStraight = Hand::fromString("KH QD JS TC 9H");

    success &= (Evaluator::compareHands(lowStraight, highStraight) < 0);
    displayTestResult("Quinte basse vs Quinte haute", success);

    // Test 5: Quinte basse (As comme carte basse) vs Quinte moyenne
    Hand aceLowStraight = Hand::fromString("5H 4D 3S 2C AS");
    Hand mediumStraight = Hand::fromString("9H 8D 7S 6C 5H");

    success &= (Evaluator::compareHands(aceLowStraight, mediumStraight) < 0);
    displayTestResult("Quinte basse (As bas) vs Quinte moyenne", success);

    // Test 6: Brelan faible vs Brelan fort
    Hand lowThreeOfAKind = Hand::fromString("5S 5H 5C KS QH");
    Hand highThreeOfAKind = Hand::fromString("KD KC KH 5D 2C");

    success &= (Evaluator::compareHands(lowThreeOfAKind, highThreeOfAKind) < 0);
    displayTestResult("Brelan faible vs Brelan fort", success);

    // Test 7: Deux paires avec kicker faible vs Deux paires avec kicker fort
    Hand twoPairLowKicker = Hand::fromString("AS AH KS KH 2C");
    Hand twoPairHighKicker = Hand::fromString("AD AC KD KC QS");

    success &= (Evaluator::compareHands(twoPairLowKicker, twoPairHighKicker) < 0);
    displayTestResult("Deux paires avec kicker faible vs kicker fort", success);

    // Test 8: Paire faible vs Paire forte
    Hand lowPair = Hand::fromString("5S 5H AC KD QS");
    Hand highPair = Hand::fromString("KS KH 5C 4D 2S");

    success &= (Evaluator::compareHands(lowPair, highPair) < 0);
    displayTestResult("Paire faible vs Paire forte", success);

    // Test 9: Carte haute faible vs Carte haute forte (comparaison 2ème carte)
    Hand highCardLow2nd = Hand::fromString("AS QH 9C 7D 3S");
    Hand highCardHigh2nd = Hand::fromString("AD KH 8C 5D 2S");

    success &= (Evaluator::compareHands(highCardLow2nd, highCardHigh2nd) < 0);
    displayTestResult("Carte haute (2ème faible) vs Carte haute (2ème forte)", success);

    // Test 10: Carte haute équivalente jusqu'à la dernière carte
    Hand highCardLowLast = Hand::fromString("AS KH QC JD 2S");
    Hand highCardHighLast = Hand::fromString("AC KC QH JS 3D");

    success &= (Evaluator::compareHands(highCardLowLast, highCardHighLast) < 0);
    displayTestResult("Carte haute (dernière faible) vs Carte haute (dernière forte)", success);

    return success;
}

void PokerTest::displayTestResult(const QString& testName, bool success) {
    QTextStream out(stdout);
    out << testName << ": " << (success ? "SUCCÈS" : "ÉCHEC") << "\n";
}

QString PokerTest::getHandDescription(const Hand& hand) {
    return Evaluator::handTypeToString(Evaluator::evaluate(hand).type);
} 
