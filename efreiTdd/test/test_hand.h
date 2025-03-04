#ifndef TEST_HAND_H
#define TEST_HAND_H

#include "handtest_base.h"

class TestHand : public HandTestBase
{
    Q_OBJECT

private slots:
    // Tests de construction
    void testDefaultConstructor();
    void testConstructorWithCards();

    // Tests des méthodes de base
    void testAddCard();
    void testIsComplete();
    void testIsValid();

    // Tests de conversion
    void testToString();
    void testFromString();
    void testToDisplayString();

    // Tests des cas limites
    void testAddCardToFullHand();
    void testAddDuplicateCard();
    void testInvalidString();
};

#endif // TEST_HAND_H 