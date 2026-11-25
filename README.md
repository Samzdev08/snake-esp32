# Snake ESP32

Jeu du serpent sur ESP32 avec écran OLED, joystick et buzzer. La partie peut aussi être suivie en direct depuis un navigateur, grâce à une page web hébergée par l'ESP32 et synchronisée par WebSocket.

## Fonctionnalités

- Trois écrans : menu (avec le record), partie et Game Over (choix Rejouer ou Menu).
- Déplacement case par case sur une grille de 8 pixels, dirigé au joystick. Le serpent traverse les bords de l'écran.
- Chaque fruit rapporte 2 points, allonge le serpent (10 cases au maximum) et accélère le jeu : de 180 ms à 70 ms par déplacement, avec un pas de 8 ms.
- Un obstacle apparaît tous les 3 fruits, avec 5 obstacles au maximum. Toucher un obstacle ou son propre corps termine la partie.
- Le record est sauvegardé en mémoire flash et conservé après un redémarrage.
- Des bips sonores signalent les fruits, les clics dans les menus et le Game Over.
- La page web redessine le jeu dans un Canvas, avec un mode plein écran.

## Matériel

- Carte de développement ESP32
- Écran OLED SSD1306 128x64, I²C (adresse `0x3C`)
- Joystick analogique KY-023
- Buzzer

## Câblage

| Composant | Broche du composant | Broche de l'ESP32 |
|---|---|---|
| Écran OLED | SDA / SCL | GPIO21 / GPIO22 |
| Écran OLED | VCC / GND | 3V3 / GND |
| Joystick | VRx / VRy | GPIO34 / GPIO35 |
| Joystick | SW | GPIO12 |
| Joystick | VCC / GND | 3V3 / GND |
| Buzzer | + / - | GPIO5 / GND |

Le joystick doit être alimenté en 3,3 V : en 5 V, les lectures analogiques restent bloquées à 4095. Les broches sont définies dans `oled_snake/Snake/config.h`.

## Structure du projet

```
oled_snake/Snake/
├── Snake.ino        Point d'entrée : setup() et boucle principale
├── config.h         Broches, dimensions, vitesse, obstacles
├── etat.h / .ino    État global du jeu (serpent, score, record, obstacles)
├── jeu.h / .ino     Logique : déplacement, collisions, nourriture, obstacles
├── affichage.h/.ino Rendu OLED avec U8g2
├── son.h / .ino     Buzzer
├── wifi.ino         Point d'accès, serveur HTTP et WebSocket
└── page.h           Page web (HTML, CSS, JavaScript)
docs/
├── conception/      Schémas : câblage, états, maquette des écrans
├── code_source/     Code source complet en LaTeX et PDF
└── REFERENCES.md    Sources, bibliothèques et licences
ASSISTANCE.md        Journal des aides utilisées (tutoriels, IA)
```

## Installation

1. Installer Arduino IDE et le paquet de cartes ESP32 (Espressif).
2. Installer les bibliothèques **U8g2** (olikraus) et **WebSockets** (Markus Sattler) depuis le gestionnaire de bibliothèques. Preferences, WiFi et WebServer sont incluses dans le paquet ESP32.
3. Ouvrir `oled_snake/Snake/Snake.ino`, choisir la carte ESP32 et le port, puis téléverser.

## Utilisation

- **Menu** : cliquer sur le joystick pour lancer une partie.
- **Partie** : diriger le serpent avec le joystick.
- **Game Over** : pousser le joystick à gauche ou à droite pour choisir Rejouer ou Menu, puis cliquer pour valider.

### Page web

1. Se connecter au réseau Wi-Fi `ESP32-MonReseau` (mot de passe `12345678`).
2. Ouvrir `http://192.168.4.1` dans un navigateur.

Le serveur HTTP (port 80) sert la page, et le serveur WebSocket (port 81) envoie l'état du jeu en JSON à chaque changement. La logique du jeu reste entièrement sur l'ESP32. Le réseau n'a pas d'accès à Internet, c'est normal. L'adresse IP s'affiche aussi dans le moniteur série (115200 bauds).

## Documentation

- `docs/REFERENCES.md` : tutoriels consultés, bibliothèques, licences et code repris.
- `ASSISTANCE.md` : aides utilisées pendant le développement, dont l'IA (Claude et ChatGPT).
- `docs/code_source/code_source.pdf` : code source complet en PDF.
