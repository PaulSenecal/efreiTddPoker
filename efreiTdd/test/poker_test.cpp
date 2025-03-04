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

bool PokerTest::testWinningHands() {
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

    return success;
}

bool PokerTest::testLosingHands() {
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

    return success;
}

void PokerTest::displayTestResult(const QString& testName, bool success) {
    QTextStream out(stdout);
    out << testName << ": " << (success ? "SUCCÈS" : "ÉCHEC") << "\n";
}

QString PokerTest::getHandDescription(const Hand& hand) {
    return Evaluator::handTypeToString(Evaluator::evaluate(hand).type);
} 