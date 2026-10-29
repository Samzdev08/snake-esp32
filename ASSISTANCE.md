# Journal d'assistance

Ce fichier recense les aides et ressources utilisées pendant le projet. Les entrées historiques sont conservées d'après les informations du développeur. Pour le 29 octobre, les propositions sont distinguées des tests explicitement confirmés.

---

## 06.10.2026 - Claude (IA) - Idée de projet et fiche de proposition

**Besoin :**
Trouver un projet embarqué à la place de MonoGame et remplir la fiche de proposition.

**Assistance :**
Claude m'a proposé cinq idées et a rédigé un brouillon de la fiche.

**Utilisation / vérification :**
J'ai choisi le Snake sur OLED et décidé d'utiliser un joystick au lieu des boutons proposés. Le brouillon m'a servi de base pour la fiche.

---

## 06.10.2026 - Claude (IA) - Dépôt Git

**Besoin :**
Prévoir les fichiers du projet et organiser le dépôt.

**Assistance :**
Claude a proposé une arborescence pour Arduino IDE, un fichier `.gitignore` et des conseils pour les commits.

**Utilisation / vérification :**
La structure proposée a servi de base au dépôt.

---

## 08.10.2026 - Tutoriels (Instructables et Embedded Nerd) - Affichage OLED, grille et fruits

**Besoin :**
Afficher une grille sur l'OLED et placer des fruits au hasard.

**Assistance :**
J'ai consulté deux tutoriels de Snake sur ESP32 avec OLED, référencés dans `docs/REFERENCES.md`.

**Utilisation / vérification :**
Ils m'ont aidé à réaliser et adapter la grille et l'affichage de fruits aléatoires.

---

## 13.10.2026 - Elegoo Wiki - Bouton du joystick

**Besoin :**
Câbler le joystick et lire son bouton SW.

**Assistance :**
Consultation du tutoriel Elegoo indiqué dans `docs/REFERENCES.md`.

**Utilisation / vérification :**
Adaptation de `pinMode(SW_pin, INPUT_PULLUP)` et de `digitalRead(SW_pin)` pour lancer une partie depuis le menu.

---

## Jour 5 - Embedded Nerd - Structure et déplacement du serpent

**Besoin :**
Stocker les segments et déplacer le serpent.

**Assistance :**
Le tutoriel utilise deux tableaux pour les coordonnées et un décalage des segments pour suivre la tête.

**Utilisation / vérification :**
Adaptation avec `snakeX[]`, `snakeY[]`, une direction fournie par le joystick et un déplacement de `grid` pixels. L'affichage utilise `drawBox()` de U8g2. La date exacte de cette adaptation reste à compléter.

---

## 28.10.2026 - Claude (IA) - Obstacles et vérification des cases libres

**Besoin :**
Ajouter des obstacles sans qu'un obstacle ou un fruit apparaisse sur le serpent.

**Assistance :**
Claude m'a aidé pour le dessin des obstacles, avec un cadre et une croix, et pour la fonction `caseLibre()`, qui vérifie qu'une case n'est occupée ni par le serpent ni par un autre obstacle.

**Utilisation / vérification :**
J'ai relu, testé et adapté le code. `caseLibre()` est utilisée pour placer la nourriture et les obstacles.

---

## 28.10.2026 - Claude (IA) - Joystick bloqué à 4095

**Besoin :**
Comprendre pourquoi X et Y valaient 4095 lorsque je poussais le joystick.

**Assistance :**
Claude a proposé de vérifier l'alimentation : le module était alimenté en 5 V, ce qui pouvait conduire à une tension excessive sur les entrées analogiques de l'ESP32.

**Utilisation / vérification :**
J'ai branché le joystick sur le 3V3 de l'ESP32 et testé les valeurs, devenues correctes. La valeur 4095 indique une saturation de la mesure ; elle ne prouve pas, à elle seule, la cause du problème.

---

## 29.10.2026 - ChatGPT (IA) - Séparation des fichiers et erreurs de compilation

**Besoin :**
Corriger l'erreur de redéfinition de `dirX` après la séparation du programme en plusieurs fichiers.

**Assistance :**
ChatGPT a consulté le dépôt et repéré que `Snake.ino` contenait encore l'ancien programme complet, en plus du code réparti dans les autres fichiers. Il a proposé un fichier principal contenant les initialisations et deux blocs `switch` : mise à jour puis affichage.

**Utilisation / vérification :**
Cette proposition sert à supprimer les définitions en double. ChatGPT a expliqué le rôle des déclarations `extern` et le fait que les deux `switch` s'exécutent successivement, pas simultanément.

---

## 29.10.2026 - ChatGPT (IA) - Diagnostic de l'écran OLED

**Besoin :**
Retrouver l'affichage après les modifications du programme.

**Assistance :**
ChatGPT a fourni un test du menu, des messages série, un scanner I²C sur SDA 21 et SCL 22, puis un test affichant « OLED OK ». Il a proposé de préciser l'adresse avec `u8g2.setI2CAddress(0x3C << 1)`.

**Utilisation / vérification :**
Le scanner a détecté `0x3C` et j'ai confirmé l'affichage de « OLED OK ». Le programme du jeu a ensuite été proposé à nouveau. Ces tests confirment la communication avec l'écran, mais n'identifient pas à eux seuls la cause exacte de la panne initiale.

---

## 29.10.2026 - ChatGPT (IA) - Point d'accès Wi-Fi et serveur web

**Besoin :**
Séparer le code réseau et accéder à une page hébergée par l'ESP32.

**Assistance :**
À partir du code de point d'accès fourni dans la conversation, ChatGPT a proposé `initWifi()` et `mettreAJourWifi()`, avec les bibliothèques `WiFi` et `WebServer`. Après une erreur de compilation, il a conseillé de renommer `wifi.h` et `wifi.ino` en `reseau.h` et `reseau.ino` pour éviter un conflit de nom avec `WiFi.h` sous Windows.

**Utilisation / vérification :**
L'appui sur EN, après ouverture du moniteur série, a permis de voir l'adresse IP. J'ai confirmé l'accès à la page « Bonjour depuis l'ESP32 ! » à l'adresse `http://192.168.4.1`. ChatGPT a également expliqué la connexion au point d'accès et l'absence normale d'accès Internet sur ce réseau.

---

## 29.10.2026 - ChatGPT (IA) - Page web et première actualisation HTTP

**Besoin :**
Afficher le Snake sur un navigateur pour la démonstration, en plus de l'OLED.

**Assistance :**
ChatGPT a généré le code HTML, CSS et JavaScript de `page.h`, ainsi que la sérialisation JSON dans `reseau.ino`. La page comprend un Canvas, le menu, le score, le record, Game Over, la sélection Rejouer/Menu et un bouton de plein écran. Une première version utilise `fetch("/etat")` avec une attente de 100 ms, ensuite réduite à 30 ms après chaque réponse.

**Utilisation / vérification :**
Code fourni pour intégration et aperçu visuel présenté avec des données d'exemple. La page reçoit les coordonnées et l'état du jeu ; le joystick et la logique restent sur l'ESP32. Un aperçu visuel ne valide pas le fonctionnement de bout en bout sur le matériel.

---

## 29.10.2026 - ChatGPT (IA) - Synchronisation WebSocket

**Besoin :**
Réduire le décalage entre le navigateur et l'OLED, notamment lorsque le serpent accélère.

**Assistance :**
ChatGPT a proposé la bibliothèque WebSockets de Markus Sattler, un serveur sur le port 80 et des versions complètes de `reseau.ino` et `page.h`. Le serveur envoie un état à la connexion, puis diffuse les données lorsque le JSON change. La page reçoit les messages et prévoit une reconnexion automatique.

**Utilisation / vérification :**
Version WebSocket fournie pour remplacer la version HTTP périodique. Les fichiers réseau et page doivent utiliser le même mécanisme. Le code du jeu reste inchangé, mais la page web doit être testée pour vérifier la synchronisation et la réactivité.
---

