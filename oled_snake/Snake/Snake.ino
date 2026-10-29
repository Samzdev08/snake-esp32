#include <Arduino.h>
#include "config.h"
#include "etat.h"
#include "jeu.h"
#include "affichage.h"
#include "son.h"
#include "reseau.h"

void setup() {
  Serial.begin(115200);

  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(BUZZER_pin, OUTPUT);

  
  initAffichage();
  initialiserJeu();
  initWifi();
}

void loop() {


  switch (etatJeux) {
    case MENU:
      mettreAJourMenu();
      break;

    case JEU:
      mettreAJourJeu();
      break;

    case GAME_OVER:
      mettreAJourGameOver();
      break;
  }

  switch (etatJeux) {
    case MENU:
      afficherMenu();
      break;

    case JEU:
      afficherJeu();
      break;

    case GAME_OVER:
      afficherGameOver();
      break;
  }

  mettreAJourWifi();
}