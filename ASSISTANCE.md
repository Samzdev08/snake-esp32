# Journal d'assistance

Ce fichier recense les aides et ressources utilisées pendant le projet

---

## 06.10.2026 - Claude (IA) - Idée de projet et fiche de proposition

**Besoin :**
Trouver un projet embarqué à la place de MonoGame et remplir la fiche de proposition

**Assistance :**
Claude m'a proposé 5 idées et a rédigé un brouillon de la fiche

**Utilisation / vérification :**
J'ai choisi le Snake sur OLED et j'ai décidé d'utiliser un joystick au lieu de bouton comme l'IA m'a dit. Le brouillon m'a servi de base pour la fiche

---


## 06.10.2026 - Claude (IA) - Dépôt Git

**Besoin :**
Prevoir tous les fichiers prévoir pour pas avoir de surprise

**Assistance :**
Claude a proposé une arborescence pour Arduino IDE, un gitignore et des conseils pour les commits

**Utilisation / vérification :**
Structure utilisée pour le dépôt

---


## 08.10.2026 - Tutoriels (Instructables et Embedded Nerd) - Affichage OLED, grille et fruits

**Besoin :**
Afficher la grille sur l'OLED et placer des fruits au hasard

**Assistance :**
Deux tutoriels de Snake sur ESP32 avec OLED consultés (liens dans REFERENCES.md)

**Utilisation / vérification :**
Grâce à eux j'ai pu faire et « adaptée » la grille et afficher des fruits aléatoires

---


## 28.10.2026 - Claude (IA) - Obstacles et vérification des cases libres

**Besoin :**
Ajouter des obstacles au jeu, sans qu'un obstacle ou un fruit apparaisse sur le serpent

**Assistance :**
Claude m'a aidé pour le dessin des obstacles (cadre avec une croix) et pour la fonction `caseLibre()`, qui vérifie qu'une case n'est occupée ni par le serpent ni par un autre obstacle

**Utilisation / vérification :**
J'ai relu, testé et adapté le code moi-même. `caseLibre()` est utilisée pour placer la nourriture et les obstacles

---


## 28.10.2026 - Claude (IA) - Joystick bloqué à 4095

**Besoin :**
Comprendre pourquoi X et Y valaient 4095 dès que je poussais le joystick

**Assistance :**
Claude m'a aidé à diagnostiquer le problème : le module était alimenté en 5 V, alors que l'ADC de l'ESP32 supporte 3,3 V au maximum

**Utilisation / vérification :**
J'ai branché le joystick sur le 3V3 de l'ESP32 et j'ai testé : les valeurs sont maintenant correctes

---