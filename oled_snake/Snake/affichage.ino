#include <Arduino.h>
#include <U8g2lib.h>
#include "affichage.h"
#include "config.h"
#include "etat.h"


static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void initAffichage() {
  u8g2.setI2CAddress(0x3C << 1);
  u8g2.begin();
}
static void drawCentre(const char* txt, int y) {
  int x = (LARGEUR_ECRAN - u8g2.getStrWidth(txt)) / 2;
  u8g2.drawStr(x, y, txt);
}

void afficherMenu() {
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_courB18_tf);
  drawCentre("SNAKE", 20);

  u8g2.setFont(u8g2_font_7x13_tf);
  String txt = "Record : " + String(record);
  drawCentre(txt.c_str(), 42);
  drawCentre("Clic pour jouer", 60);

  u8g2.sendBuffer();
}

void afficherJeu() {
  u8g2.clearBuffer();


  for (int i = 0; i < snakeLength; i++) {
    u8g2.drawBox(snakeX[i], snakeY[i], grid, grid);
  }


  u8g2.setFont(u8g2_font_6x10_tf);
  String txtScore = "Score: " + String(score);
  u8g2.drawStr(4, 10, txtScore.c_str());
  u8g2.drawHLine(0, 15, LARGEUR_ECRAN);


  for (int y = HAUT_ZONE_JEU; y < HAUTEUR_ECRAN; y += grid) {
    for (int x = 0; x < LARGEUR_ECRAN; x += grid) {
      u8g2.drawPixel(x, y);
    }
  }


  for (int i = 0; i < nbObs; i++) {
    u8g2.drawFrame(obsX[i], obsY[i], grid, grid);
    u8g2.drawLine(obsX[i], obsY[i], obsX[i] + grid - 1, obsY[i] + grid - 1);
    u8g2.drawLine(obsX[i] + grid - 1, obsY[i], obsX[i], obsY[i] + grid - 1);
  }


  u8g2.drawFrame(foodX, foodY, grid, grid);

  u8g2.sendBuffer();
}

void afficherGameOver() {
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_courB12_tf);
  drawCentre("GAME OVER", 14);

  u8g2.setFont(u8g2_font_6x10_tf);
  String txtScore = "Score : " + String(score);
  drawCentre(txtScore.c_str(), 30);
  String txtRecord = "Record : " + String(record);
  drawCentre(txtRecord.c_str(), 42);

  u8g2.drawStr(14, 59, "Rejouer");
  u8g2.drawStr(84, 59, "Menu");

  if (choixGameOver == 0) {
    u8g2.drawFrame(10, 49, u8g2.getStrWidth("Rejouer") + 8, 13);
  } else {
    u8g2.drawFrame(80, 49, u8g2.getStrWidth("Menu") + 8, 13);
  }

  u8g2.sendBuffer();
}