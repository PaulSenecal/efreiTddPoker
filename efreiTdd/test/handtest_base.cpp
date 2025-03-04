#include "handtest_base.h"

void HandTestBase::createBasicHand(Hand& hand)
{
    hand.addCard(Card::fromString("AS"));
    hand.addCard(Card::fromString("KH"));
}

void HandTestBase::createFullHand(Hand& hand)
{
    hand.addCard(Card::fromString("AS"));
    hand.addCard(Card::fromString("KH"));
    hand.addCard(Card::fromString("QD"));
    hand.addCard(Card::fromString("JC"));
    hand.addCard(Card::fromString("TD"));
} 