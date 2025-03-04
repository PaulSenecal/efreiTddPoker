# Évaluateur de Mains de Poker en C++ avec Qt

Ce projet est une implémentation en C++ utilisant Qt d'un évaluateur de mains de poker. Développé selon les principes de Test-Driven Development (TDD), il permet de comparer deux mains de poker et d'identifier la main gagnante selon les règles officielles.

## Fonctionnalités

- Analyse et évaluation de mains de poker de 5 cartes
- Reconnaissance des 10 combinaisons du poker (Quinte Flush Royale, Quinte Flush, Carré, etc.)
- Gestion des règles de départage en cas d'égalité
- Tests unitaires complets pour valider la logique du jeu
- Interface en ligne de commande simple pour comparer deux mains

## Règles du Poker

Le projet implémente les règles classiques du poker avec 52 cartes :
- 4 couleurs (Cœur, Carreau, Trèfle, Pique)
- 13 rangs (2, 3, 4, 5, 6, 7, 8, 9, 10, Valet, Dame, Roi, As)

Les combinaisons, du plus fort au plus faible, sont :
1. Quinte Flush Royale (A, K, Q, J, 10 de la même couleur)
2. Quinte Flush (5 cartes consécutives de la même couleur)
3. Carré (4 cartes de même rang)
4. Full (3 cartes de même rang + 2 cartes de même rang)
5. Couleur (5 cartes de la même couleur)
6. Quinte (5 cartes consécutives)
7. Brelan (3 cartes de même rang)
8. Deux Paires (2 paires de cartes de même rang)
9. Paire (2 cartes de même rang)
10. Carte Haute (aucune combinaison ci-dessus)

## Structure du Projet

```
poker-tdd/
├── CMakeLists.txt
├── poker_tdd.pro
├── src/
│   ├── card.h / card.cpp         # Classe représentant une carte
│   ├── hand.h / hand.cpp         # Classe représentant une main de 5 cartes
│   ├── evaluator.h / evaluator.cpp  # Évaluateur de mains
│   ├── game.h / game.cpp         # Logique de jeu et comparaison 
│   └── main.cpp                  # Point d'entrée du programme
└── tests/
    ├── poker_test.cpp # Tests intégrés
    └── poker_test.cpp
```

## Compilation et Exécution

### Avec qmake

```bash
mkdir build
cd build
qmake ../poker_tdd.pro
make
```

### Avec CMake

```bash
mkdir build
cd build
cmake ..
make
```

## Utilisation

Une fois compilé, exécutez le programme :

```bash
./poker_tdd
```

Pour comparer deux mains, entrez-les séparées par un `|` :

```
AH KH QH JH 10H | 9S 8S 7S 6S 5S
```

### Options

- `-t` ou `--test` : Exécuter les tests intégrés
- Saisir `test` pendant l'exécution pour lancer les tests
- Saisir `exit` ou `quit` pour quitter le programme

### Format des Cartes

Les cartes peuvent être spécifiées dans les formats suivants :
- Rang : `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`, `10`, `J`, `Q`, `K`, `A`
- Couleur : `H` (Cœurs), `D` (Carreaux), `C` (Trèfles), `S` (Piques)
- Ou avec des symboles : `♥` (Cœurs), `♦` (Carreaux), `♣` (Trèfles), `♠` (Piques)

Exemples : `AH` (As de cœur), `KS` (Roi de pique), `10♦` (10 de carreau)

## Tests

Le projet inclut plusieurs niveaux de tests :

1. **Tests unitaires** pour chaque classe (via QtTest)
2. **Tests intégrés** accessibles directement depuis l'application

Pour exécuter les tests unitaires :

```bash
cd build
make check
```

Pour exécuter les tests intégrés :

```bash
./poker_tdd --test
```

## Exemples

### Comparer une Quinte Flush Royale et une Quinte Flush

```
Entrée: AH KH QH JH 10H | 9S 8S 7S 6S 5S

Main 1: Quinte Flush Royale
Main 2: Quinte Flush
Le joueur 1 gagne!
```

### Comparer un Carré et un Full

```
Entrée: AS AH AC AD KS | KH KC KD AH AC

Main 1: Carré
Main 2: Full
Le joueur 1 gagne!
```

## Développement

Ce projet a été développé en suivant les principes du Test-Driven Development (TDD), ce qui garantit une haute qualité du code et une couverture complète des cas d'utilisation.