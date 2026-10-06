# Tests - Snake OLED (ESP32)

Ce fichier documente les tests du projet. Il est complété au fur et à mesure du développement, et non à la fin.

## Mode d'emploi

- Une ligne par test, avec un identifiant unique (T01, T02...).
- Colonnes **Date**, **Obtenu**, **Statut** et **Anomalie / correction** : à remplir au moment du test.
- Après une correction, refaire le test et l'ajouter sous un nouvel identifiant (T01b, T01c...) ou dans la même ligne en indiquant le retest.
- Statuts : `A faire`, `OK`, `Echec`, `Corrige` (échec corrigé et retesté avec succès).
- Dans la colonne anomalie, indiquer le commit de correction (ex. « corrigé dans abc1234 »).

## 1. Matériel et composants isolés

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T01 | | OLED | Afficher un texte et un rectangle avec un programme minimal | Texte lisible, rectangle visible, pas de scintillement | | A faire | |
| T02 | | Buzzer | Jouer un bip court puis un bip long | Deux sons distincts | | A faire | |
| T03 | | Joystick (repos) | Joystick au repos, afficher X et Y sur le moniteur série pendant 10 s | Valeurs stables autour du centre | | A faire | |
| T04 | | Joystick (extrêmes) | Pousser à fond dans chaque direction et noter les valeurs | Valeurs proches des bornes de l'ADC (min et max) | | A faire | |
| T05 | | Joystick (clic) | Appuyer 10 fois sur le bouton du joystick | 10 appuis détectés, pas de double détection | | A faire | |

## 2. Entrées utilisateur

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T06 | | Calibrage | Démarrer l'appareil sans toucher au joystick, afficher le centre mesuré | Centre cohérent avec T03 | | A faire | |
| T07 | | Zone morte | Joystick au repos pendant 30 s dans une partie | Aucun changement de direction involontaire | | A faire | |
| T08 | | Conversion 4 directions | Pousser dans chaque direction principale | Haut, bas, gauche, droite détectés correctement | | A faire | |
| T09 | | Diagonales | Pousser en diagonale (plusieurs angles) | La direction de l'axe dominant est retenue | | A faire | |
| T10 | | Clic joystick | Cliquer au menu, puis au game over | Lance une partie, puis relance une partie | | A faire | |

## 3. Règles du jeu

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T11 | | Déplacement | Observer le serpent sans toucher au joystick | Avance en ligne droite, à intervalles réguliers | | A faire | |
| T12 | | Demi-tour interdit | Serpent vers la droite, pousser à gauche (répéter pour les 4 directions) | Le serpent ne fait pas demi-tour | | A faire | |
| T13 | | Croissance | Manger 5 nourritures | +1 segment à chaque fois, score +1 | | A faire | |
| T14 | | Apparition de la nourriture | Jouer 20 nourritures de suite | Jamais sur le corps ni en dehors de la grille | | A faire | |
| T15 | | Collision mur | Aller dans chacun des 4 murs (4 essais) | Game over à chaque fois | | A faire | |
| T16 | | Collision corps | Faire toucher la tête au corps (serpent d'au moins 5 segments) | Game over | | A faire | |
| T17 | | Score | Terminer une partie avec un score connu | Score affiché = nombre de nourritures mangées | | A faire | |

## 4. États du jeu

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T18 | | Menu vers partie | Cliquer au menu | La partie démarre avec un serpent de taille initiale | | A faire | |
| T19 | | Game over | Provoquer une collision | Écran de fin avec score et meilleur score | | A faire | |
| T20 | | Relance | Jouer 5 parties de suite | Chaque partie repart de zéro (taille, score, vitesse, direction) | | A faire | |

## 5. Compléments (si réalisés)

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T21 | | Sons | Manger une nourriture, puis provoquer un game over | Bip court, puis son de fin | | A faire | |
| T22 | | Vitesse progressive | Atteindre 10 de score | Le serpent est plus rapide qu'au départ, reste jouable | | A faire | |
| T23 | | Meilleur score | Battre le record, couper l'alimentation, rallumer | Record conservé | | A faire | |
| T24 | | Meilleur score (non battu) | Faire un score inférieur au record, redémarrer | Record inchangé | | A faire | |
| T25 | | Modes de jeu | Tester chaque mode (murs mortels, passage de l'autre côté) | Comportement conforme au mode choisi | | A faire | |

## 6. Cas limites, stabilité et performance

| ID | Date | Fonctionnalité | Test (comment) | Attendu | Obtenu | Statut | Anomalie / correction |
|---|---|---|---|---|---|---|---|
| T26 | | Serpent très long | Jouer jusqu'à un serpent de 30 segments ou plus (ou forcer la taille en debug) | Pas de ralentissement, pas de plantage | | A faire | |
| T27 | | Nourriture dans un coin | Forcer la nourriture dans un coin en debug | Atteignable, collision correcte | | A faire | |
| T28 | | Grille presque pleine | Forcer un serpent très long en debug | Le jeu ne se bloque pas à la génération de la nourriture | | A faire | |
| T29 | | Coupure de courant | Débrancher pendant une partie, puis rebrancher | Redémarrage propre, meilleur score intact | | A faire | |
| T30 | | Stabilité | Laisser tourner 15 minutes (menu et parties) | Pas de blocage, pas de redémarrage | | A faire | |
| T31 | | Performance | Mesurer le temps d'une image avec `millis()` | Valeur notée, fluide à l'œil | | A faire | |

## Résumé pour la documentation technique (section A.4)

À compléter en fin de projet :

- Nombre de tests réalisés :
- Nombre d'échecs corrigés :
- Principales anomalies et corrections :
- Problèmes connus restants dans la version finale :