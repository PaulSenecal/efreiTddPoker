#ifndef HANDTEST_BASE_H
#define HANDTEST_BASE_H

#include <QTest>
#include "../hand.h"

class HandTestBase : public QObject
{
    Q_OBJECT

protected:
    // Méthodes utilitaires communes
    void createBasicHand(Hand& hand);
    void createFullHand(Hand& hand);
};

#endif // HANDTEST_BASE_H 