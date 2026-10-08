# Références et ressources externes

À compléter au fur et à mesure : une ligne dès qu'on utilise une bibliothèque, du code repris, une image, un son ou une police.

## Documents et outils utilisés

| Ressource | Utilisation |
|---|---|
| Mandat MonoGame (PDF du formateur) | Cadre du projet |
| Annexe du mandat de la documentation | Documentation |
| Google Sheets | Planning |
| Git | Suivi du code |
| Canva | Réalisation des schémas (câblage, états, classes, maquette des écrans) |

## Tutoriels et exemples consultés

| Source | Auteur | Date | Lien | Utilisation |
|---|---|---|---|---|
| ESP32 OLED Snake Game - Best SSD1306 and Joystick Setup (Instructables) | instructables | 08.10.2026 | https://www.instructables.com/-ESP32-OLED-Snake-Game-Best-SSD1306-and-Joystick-S/ | Affichage OLED : grille et fruits aléatoires (jour 3) |
| ESP32 Snake Game Tutorial: MPU6050 Tilt Control & OLED (Embedded Nerd) | Embedded Nerd | 08.10.2026 | https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/ | Affichage OLED : grille et fruits aléatoires (jour 3) |


## Bibliothèques

Prévues (à confirmer, avec version et licence quand je les installe) :


| Bibliothèque | Version | Licence | Lien | Utilisation |
|---|---|---|---|---|
| U8g2 | N/A | BSD-2-Clause | [GitHub – U8g2](https://github.com/olikraus/u8g2) | Affichage de textes et de formes graphiques sur l'écran OLED SSD1306 via I2C |

## Code repris ou adapté



| Source (lien) | Ce qui est repris | Où dans le projet | Adapté comment |
|---|---|---|---|
|  https://embeddednerd.com/esp32-snake-game-with-mpu6050-and-oled-display/| fonction randomFood() | Fichier `snake.ino` | Coordonnées en cases au lieu de pixels, décalage pour la bande de score |

## Images, sons, polices

Aucun pour l'instant