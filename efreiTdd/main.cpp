#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "card.h"
#include "hand.h"
#include "evaluator.h"
#include "game.h"
#include "test/poker_test.h"

void displayHelp() {
    QTextStream out(stdout);
    out << "Poker Evaluator - Comparez deux mains de poker\n";
    out << "Utilisation: Entrez deux mains de poker séparées par '|'\n";
    out << "Format: [carte1] [carte2] [carte3] [carte4] [carte5] | [carte1] [carte2] [carte3] [carte4] [carte5]\n";
    out << "Exemple: AH KH QH JH 10H | 9S 8S 7S 6S 5S\n";
    out << "\n";
    out << "Notations des cartes:\n";
    out << "  - Rangs: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A\n";
    out << "  - Couleurs: H (Hearts/Cœurs), D (Diamonds/Carreaux), C (Clubs/Trèfles), S (Spades/Piques)\n";
    out << "  ou ♥ (Cœurs), ♦ (Carreaux), ♣ (Trèfles), ♠ (Piques)\n";
    out << "\nTapez 'exit' pour quitter.\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    // Exécuter les tests
    bool testsOk = PokerTest::runTests();
    if (!testsOk) {
        out << "Attention: Certains tests ont échoué!\n\n";
    }

    displayHelp();

    while (true) {
        out << "\nEntrez les mains à comparer (ou 'exit' pour quitter): ";
        out.flush();

        QString input = in.readLine().trimmed();

        if (input.toLower() == "exit" || input.toLower() == "quit") {
            break;
        }

        try {
            Game game = Game::fromString(input);

            // Afficher les mains pour confirmation
            out << "Main 1: " << game.getHand1().toString() << "\n";
            out << "Main 2: " << game.getHand2().toString() << "\n";

            // Vérifier si les mains sont complètes
            if (!game.getHand1().isComplete() || !game.getHand2().isComplete()) {
                out << "Erreur: Les deux mains doivent contenir exactement 5 cartes.\n";
                continue;
            }

            // Évaluer les mains et afficher le résultat
            Game::Result result = game.determineWinner();

            out << "Main 1: " << Evaluator::handTypeToString(result.hand1Type) << "\n";
            out << "Main 2: " << Evaluator::handTypeToString(result.hand2Type) << "\n";

            if (result.winner == 1) {
                out << "Le joueur 1 gagne!\n";
            } else if (result.winner == 2) {
                out << "Le joueur 2 gagne!\n";
            } else {
                out << "Égalité!\n";
            }

            out << "Description: " << result.description << "\n";

        } catch (const std::exception& e) {
            out << "Erreur: " << e.what() << "\n";
            out << "Essayez à nouveau avec un format valide.\n";
        }
    }

    out << "Au revoir!\n";
    return 0;
}
