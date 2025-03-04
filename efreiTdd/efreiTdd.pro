QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        evaluator.cpp \
        game.cpp \
        hand.cpp \
        main.cpp \
        test/test_card.cpp \
        test/test_evaluator.cpp \
        test/test_game.cpp \
        test/test_hand.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    evaluator.h \
    game.h \
    hand.h
