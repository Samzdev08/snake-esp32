# Références et ressources externes

Une ligne est ajoutée lorsqu'une bibliothèque, du code externe, une image, un son ou une police est utilisé. Les dates des tutoriels ci-dessous correspondent aux dates de consultation déclarées, pas aux dates de publication.

## Documents et outils utilisés

| Ressource | Utilisation |
|---|---|
| Mandat MonoGame (PDF du formateur) | Cadre du projet |
| Annexe du mandat | Documentation |
| Google Sheets | Planning |
| Git | Suivi du code et historique des modifications |
| GitHub | Hébergement du dépôt : https://github.com/Samzdev08/snake-esp32 |
| Canva | Réalisation des schémas : câblage, états, classes et maquette des écrans |
| Arduino IDE | Écriture, compilation et téléversement du code sur l'ESP32 ; moniteur série |
| Claude (Anthropic) | Assistance à la préparation du projet et au développement ; détails dans `ASSISTANCE.md` |
| ChatGPT (OpenAI) | Assistance au réseau Wi-Fi, à la page web, au WebSocket  ; détails dans `ASSISTANCE.md` |
| Navigateur web | Accès à la page hébergée par l'ESP32 et affichage du jeu |

## Tutoriels et exemples consultés

| Source | Auteur / éditeur | Consultation | Lien | Utilisation |
|---|---|---|---|---|
| ESP32 OLED Snake Game - Best SSD1306 and Joystick Setup | Instructables ; auteur individuel à vérifier | 08.10.2026 | https://www.instructables.com/-ESP32-OLED-Snake-Game-Best-SSD1306-and-Joystick-S/ | Affichage OLED : grille et fruits aléatoires (jour 3) |
| ESP32 Snake Game Tutorial: MPU6050 Tilt Control & OLED | Embedded Nerd | 08.10.2026 | https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Grille et fruits aléatoires (jour 3) ; création, affichage et déplacement du serpent (jour 5) |
| Joystick Module – Getting Started | Elegoo | 13.10.2026 | https://wiki.elegoo.com/oshw-getting-started-&-kits/joystick | Câblage du joystick et lecture du bouton SW en `INPUT_PULLUP` (jour 4) |
| Dépôt arduinoWebSockets | Markus Sattler / Links2004 et contributeurs | 29.10.2026, consulté par ChatGPT pendant l'assistance | https://github.com/Links2004/arduinoWebSockets | Choix de la bibliothèque WebSocket compatible ESP32 et préparation de son intégration (jour 9) |

## Bibliothèques

Les versions exactes installées doivent être relevées dans Arduino IDE. « À relever » ne signifie pas que la bibliothèque n'a pas de version. Les licences sont à contrôler dans la version effectivement utilisée avant remise du projet.

| Bibliothèque | Version | Licence / statut | Lien | Utilisation |
|---|---|---|---|---|
| U8g2 | À relever | BSD-2-Clause ; licences des polices à vérifier séparément | https://github.com/olikraus/u8g2 | Textes et formes sur l'OLED SSD1306 via I²C |
| Preferences, incluse dans Arduino-ESP32 | Version du noyau à relever | LGPL-2.1, selon la référence initiale ; à confirmer dans la version installée | https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences | Sauvegarde du record en mémoire flash avec `putInt()` et `getInt()` (jour 7) |
| Wire, incluse dans Arduino-ESP32 | Version du noyau à relever | À vérifier dans la version installée | https://github.com/espressif/arduino-esp32/tree/master/libraries/Wire | Communication I²C et test de détection de l'OLED à l'adresse `0x3C` |
| WiFi, incluse dans Arduino-ESP32 | Version du noyau à relever | À vérifier dans la version installée | https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi | Création du point d'accès avec `WiFi.softAP()` et affichage de son adresse IP |
| WebServer, incluse dans Arduino-ESP32 | Version du noyau à relever | À vérifier dans la version installée | https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer | Serveur HTTP sur le port 80 et envoi de la page web ; route `/etat` dans la première version HTTP |
| WebSockets / arduinoWebSockets | À relever après installation | LGPL-2.1, indiquée par le dépôt consulté | https://github.com/Links2004/arduinoWebSockets | Serveur WebSocket sur le port 81 ; transmission des changements du jeu au navigateur |

## Technologies web utilisées

| Technologie | Utilisation |
|---|---|
| HTML et CSS | Structure et présentation de la page stockée dans `page.h` |
| Canvas 2D | Dessin du serpent, du fruit, des obstacles et de la grille |
| JSON | Format des données : état, score, record, positions et sélection Game Over |
| Fetch API | Première version : requêtes HTTP espacées de 100 ms, puis de 30 ms après chaque réponse |
| WebSocket du navigateur | Version suivante : réception des changements via une connexion persistante, sans requêtes périodiques |
| Fullscreen API | Bouton de plein écran lorsque le navigateur le permet |



## Code repris ou adapté

Les emplacements ci-dessous correspondent à l'organisation proposée après séparation des fichiers. Vérifier qu'ils correspondent à la version finale du dépôt.

| Source | Ce qui est repris ou proposé | Où dans le projet | Adaptation / utilisation |
|---|---|---|---|
| https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Fonction `randomFood()` | `jeu.ino`, `spawnFood()` ; auparavant `snake.ino` | Positions alignées sur la grille et exclusion de la bande de score ; coordonnées finales exprimées en pixels, multiples de `grid` |
| https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Tableaux `snakeX[]`, `snakeY[]`, décalage du corps et avancée de la tête | `etat.ino`, `jeu.ino`, `affichage.ino` ; auparavant `snake.ino` | Joystick à la place du MPU6050 ; déplacement par cases et rendu avec U8g2 |
| https://wiki.elegoo.com/oshw-getting-started-&-kits/joystick | Configuration et lecture du bouton SW | `Snake.ino`, `jeu.ino` | `INPUT_PULLUP`, lancement d'une partie et validation des menus ; temporisation initiale contre les lectures multiples |
| ChatGPT, conversation du 29.10.2026 | Point d'accès, serveur HTTP et données JSON | `reseau.ino`, `reseau.h` | Intégration au jeu existant et première route `/etat` |
| ChatGPT, conversation du 29.10.2026 | HTML, CSS et JavaScript de la page complète | `page.h` | Menu, terrain, scores, Game Over, sélection, plein écran ; actualisation HTTP puis version WebSocket |
| ChatGPT, conversation du 29.10.2026 | Intégration WebSocket et reconnexion du navigateur | `reseau.ino`, `page.h` | Envoi initial à la connexion, puis diffusion lorsque le JSON change ; réception et dessin côté navigateur |



## Images, sons, polices

| Ressource | Type | Licence / statut | Lien | Utilisation |
|---|---|---|---|---|
| `u8g2_font_courB18_tf`, `u8g2_font_courB12_tf` | Polices incluses dans U8g2 | À vérifier pour chaque police | https://github.com/olikraus/u8g2/wiki/fntlistall | Titres « SNAKE » et « GAME OVER » sur l'OLED |
| `u8g2_font_7x13_tf`, `u8g2_font_6x10_tf` | Polices incluses dans U8g2 | À vérifier pour chaque police | https://github.com/olikraus/u8g2/wiki/fntlistall | Menu, score, record et options sur l'OLED |
| Arial / `sans-serif` | Police système du navigateur | Aucun fichier de police distribué avec le projet | — | Textes de la page web |
| Formes U8g2 et Canvas | Graphismes dessinés par le programme | Aucun fichier image externe | — | Serpent, fruit, obstacles et grille |
| Bips du buzzer | Sons produits par le programme | Aucun fichier audio externe | — | Fruit, clic des menus et Game Over |

Aucune image ni aucun fichier sonore externe n'est intégré au jeu. Les sons sont générés par le buzzer.
