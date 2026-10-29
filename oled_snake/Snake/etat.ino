#include "etat.h"


Preferences preferences;
Etat etatJeux = MENU;
int score = 0;
int record = 0;
int choixGameOver = 0;

int snakeLength = 3;
int snakeX[TAILLE_MAX_SERPENT];
int snakeY[TAILLE_MAX_SERPENT];
int dirX = 1;
int dirY = 0;
int nextDirX = 1;
int nextDirY = 0;

int foodX = 0;
int foodY = 0;
int obsX[MAX_OBS];
int obsY[MAX_OBS];
int nbObs = 0;
int nbManges = 0;

int gameSpeed = VITESSE_DEPART;
unsigned long lastMove = 0;
int centreX = 0;
int centreY = 0;