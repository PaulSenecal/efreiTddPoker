QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

TARGET = tst_hand

# Ajout de cette ligne pour la génération automatique des moc
CONFIG += testcase

SOURCES +=  \
    test_hand.cpp \
    handtest_base.cpp \
    ../hand.cpp \
    ../card.cpp

HEADERS += \
    test_hand.h \
    handtest_base.h \
    ../hand.h \
    ../card.h \
    ../evaluator.h \
    ../game.h

# Ajout de ces lignes pour spécifier le dossier de sortie des moc
MOC_DIR = .
OBJECTS_DIR = .

INCLUDEPATH += .. 