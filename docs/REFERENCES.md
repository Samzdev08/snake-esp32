# Références et ressources externes

À compléter au fur et à mesure : une ligne dès qu'on utilise une bibliothèque, du code repris, une image, un son ou une police.

## Documents et outils utilisés

| Ressource | Utilisation |
|---|---|
| Mandat MonoGame (PDF du formateur) | Cadre du projet |
| Annexe du mandat | Documentation |
| Google Sheets | Planning |
| Git | Suivi du code |
| Canva | Réalisation des schémas (câblage, états, classes, maquette des écrans) |
| Arduino IDE | Écriture, compilation et téléversement du code sur l'ESP32 |

## Tutoriels et exemples consultés

| Source | Auteur | Date | Lien | Utilisation |
|---|---|---|---|---|
| ESP32 OLED Snake Game - Best SSD1306 and Joystick Setup (Instructables) | instructables | 08.10.2026 | https://www.instructables.com/-ESP32-OLED-Snake-Game-Best-SSD1306-and-Joystick-S/ | Affichage OLED : grille et fruits aléatoires (jour 3) |
| ESP32 Snake Game Tutorial: MPU6050 Tilt Control & OLED (Embedded Nerd) | Embedded Nerd | 08.10.2026 | https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Affichage OLED : grille et fruits aléatoires (jour 3) ; création, affichage et déplacement du serpent (jour 5) |
| Joystick Module – Getting Started (Elegoo Wiki) | Elegoo | 13.10.2026 | https://wiki.elegoo.com/oshw-getting-started-&-kits/joystick | Câblage du joystick et lecture du bouton SW (clic) en `INPUT_PULLUP` (jour 4) |

## Bibliothèques

| Bibliothèque | Version | Licence | Lien | Utilisation |
|---|---|---|---|---|
| U8g2 | N/A | BSD-2-Clause | [GitHub – U8g2](https://github.com/olikraus/u8g2) | Affichage de textes et de formes graphiques sur l'écran OLED SSD1306 via I2C |
| Preferences (incluse dans le noyau ESP32 pour Arduino) | N/A | LGPL-2.1 | [GitHub – arduino-esp32 / Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences) | Sauvegarde du record dans la mémoire flash de l'ESP32 (`putInt()` / `getInt()`), conservé après une coupure de courant (jour 7) |

## Code repris ou adapté

| Source (lien) | Ce qui est repris | Où dans le projet | Adapté comment |
|---|---|---|---|
| https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Fonction `randomFood()` | Fichier `snake.ino` | Coordonnées en cases au lieu de pixels, décalage pour la bande de score ; renommée `spawnFood()` |
| https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Stockage du serpent dans deux tableaux (`snakeX[]`, `snakeY[]`), décalage des segments et avancée de la tête | Fichier `snake.ino` – `setup()`, `lireJoystick()`, `afficherJeu()` | Direction lue au joystick au lieu du MPU6050, déplacement par cases de `grid` pixels, affichage avec `drawBox()` de U8g2 |
| https://wiki.elegoo.com/oshw-getting-started-&-kits/joystick | Configuration et lecture du bouton SW (`pinMode(SW_pin, INPUT_PULLUP)`, `digitalRead(SW_pin)`) | Fichier `snake.ino` – `afficherMenu()` et état `MENU` | Utilisé pour passer du menu au jeu, ajout d'un `delay(200)` contre les lectures multiples |

## Images, sons, polices

| Ressource | Type | Licence | Lien | Utilisation |
|---|---|---|---|---|
| `u8g2_font_courB18_tf`, `u8g2_font_courB12_tf` | Police (incluse dans U8g2) | À vérifier | https://github.com/olikraus/u8g2/wiki/fntlistall | Titres « SNAKE » et « GAME OVER » |
| `u8g2_font_7x13_tf`, `u8g2_font_6x10_tf` | Police (incluse dans U8g2) | À vérifier | https://github.com/olikraus/u8g2/wiki/fntlistall | Textes du menu, score, record, options |

Aucune image ni aucun son pour l'instant.