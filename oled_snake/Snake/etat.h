#pragma once
#include <Preferences.h>
#include "config.h"

enum Etat { MENU, JEU, GAME_OVER };


extern Preferences preferences;
extern Etat etatJeux;
extern int score;
extern int record;
extern int choixGameOver;


extern int snakeLength;
extern int snakeX[TAILLE_MAX_SERPENT];
extern int snakeY[TAILLE_MAX_SERPENT];
extern int dirX;
extern int dirY;
extern int nextDirX;
extern int nextDirY;


extern int foodX;
extern int foodY;
extern int obsX[MAX_OBS];
extern int obsY[MAX_OBS];
extern int nbObs;
extern int nbManges;


extern int gameSpeed;
extern unsigned long lastMove;
extern int centreX;
extern int centreY;