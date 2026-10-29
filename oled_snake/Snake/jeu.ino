#include <Arduino.h>
#include "jeu.h"
#include "config.h"
#include "etat.h"
#include "son.h"



static bool caseLibre(int x, int y) {
  for (int i = 0; i < snakeLength; i++) {
    if (snakeX[i] == x && snakeY[i] == y) return false;
  }
  for (int i = 0; i < nbObs; i++) {
    if (obsX[i] == x && obsY[i] == y) return false;
  }
  return true;
}

static void spawnFood() {
  do {
    foodX = random(0, LARGEUR_ECRAN / grid) * grid;
    foodY = random(2, HAUTEUR_ECRAN / grid) * grid;
  } while (!caseLibre(foodX, foodY));
}

static void spawnObstacle() {
  if (nbObs >= MAX_OBS) return;

  int x, y;
  do {
    x = random(0, LARGEUR_ECRAN / grid) * grid;
    y = random(2, HAUTEUR_ECRAN / grid) * grid;
  } while (!caseLibre(x, y)
           || (x == foodX && y == foodY)
           || (abs(x - snakeX[0]) <= 2 * grid && abs(y - snakeY[0]) <= 2 * grid));

  obsX[nbObs] = x;
  obsY[nbObs] = y;
  nbObs++;
}

void reset() {
  centreX = analogRead(X_pin);
  centreY = analogRead(Y_pin);

  snakeLength = 3;

  dirX = 1;
  dirY = 0;
  nextDirX = 1;
  nextDirY = 0;

  score = 0;
  gameSpeed = VITESSE_DEPART;
  nbObs = 0;
  nbManges = 0;

  snakeX[0] = 48;
  snakeY[0] = 32;

  snakeX[1] = 40;
  snakeY[1] = 32;

  snakeX[2] = 32;
  snakeY[2] = 32;

  spawnFood();
}

void initialiserJeu() {
  preferences.begin("snake", false);
  record = preferences.getInt("record", 0);
  reset();
}


static void lireJoystick() {


  int dx = analogRead(X_pin) - centreX;
  int dy = analogRead(Y_pin) - centreY;

  if (abs(dx) <= ZONE_MORTE && abs(dy) <= ZONE_MORTE) {
    return;
  }

  int nouvelleDirX = dirX;
  int nouvelleDirY = dirY;

  if (abs(dx) > abs(dy)) {
    nouvelleDirX = (dx > 0) ? 1 : -1;
    nouvelleDirY = 0;
  } else {
    nouvelleDirX = 0;
    nouvelleDirY = (dy > 0) ? 1 : -1;
  }

  if (nouvelleDirX != -dirX || nouvelleDirY != -dirY) {
    dirX = nouvelleDirX;
    dirY = nouvelleDirY;
  }
}



static void deplacerSerpent() {

  for (int i = snakeLength; i > 0; i--) {

    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX * grid;
  snakeY[0] += dirY * grid;
}

static void declencherGameOver() {

  if (score > record) {

    record = score;
    preferences.putInt("record", record);
  }

  choixGameOver = 0;
  etatJeux = GAME_OVER;

  bip(400);
}

void mettreAJourMenu() {

  if (digitalRead(SW_pin) == 0) {

    etatJeux = JEU;
    reset();
    bip(40);
    delay(200);
  }
}

void mettreAJourJeu() {

  if (millis() - lastMove <= gameSpeed) return;

  lastMove = millis();

  lireJoystick();
  deplacerSerpent();

  if (snakeX[0] < 0) {

    snakeX[0] = LARGEUR_ECRAN - grid;

  } 
  else if (snakeX[0] >= LARGEUR_ECRAN) 
  {
    snakeX[0] = 0;

  }

  if (snakeY[0] < HAUT_ZONE_JEU) {

    snakeY[0] = HAUTEUR_ECRAN - grid;

  } 
  else if (snakeY[0] >= HAUTEUR_ECRAN) {

    snakeY[0] = HAUT_ZONE_JEU;

  }


  for (int i = 0; i < nbObs; i++) {
    if (snakeX[0] == obsX[i] && snakeY[0] == obsY[i]) {
      declencherGameOver();
      return;
    }
  }


  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      declencherGameOver();
      return;
    }
  }


  if (snakeX[0] == foodX && snakeY[0] == foodY) {

    if (snakeLength < LONGUEUR_MAX) snakeLength++;

    score += 2;
    nbManges++;

    gameSpeed -= PAS_VITESSE;
    if (gameSpeed < VITESSE_MIN) gameSpeed = VITESSE_MIN;

    bip(60);
    spawnFood();

    if (nbManges % FOOD_PAR_OBSTACLE == 0) {
      spawnObstacle();
    }
  }
}

void mettreAJourGameOver() {

  int x = analogRead(X_pin);
  if (x < 1000) {
    choixGameOver = 0;
  } else if (x > 3000) {
    choixGameOver = 1;
  }

  if (digitalRead(SW_pin) == 0) {
    bip(40);

    while (digitalRead(SW_pin) == 0) {
      delay(10);
    }

    etatJeux = (choixGameOver == 0) ? JEU : MENU;
    reset();
  }
}