#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int foodX = 0;
int foodY = 0;
int grid = 8;
const int SW_pin = 12;
const int X_pin = 34;
const int Y_pin = 35;

enum Etat { MENU,
            JEU,
            GAME_OVER };

Etat etatJeux = MENU;

int record = 0;
unsigned long dernierFruit = 0;

void spawnFood() {
  foodX = random(0, 128 / grid) * grid;
  foodY = random(2, 64 / grid) * grid;
}

void drawCentre(const char* txt, int y) {
  int x = (128 - u8g2.getStrWidth(txt)) / 2;
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

void afficherJeu(){

  if (millis() - dernierFruit >= 2000) {
    spawnFood();
    dernierFruit = millis();
  }

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(4, 10, "Score: 0");

  u8g2.drawHLine(0, 15, 128);

  for (int y = 16; y < 64; y += grid) {
    for (int x = 0; x < 128; x += grid) {
      u8g2.drawPixel(x, y);
    }
  }

  u8g2.drawFrame(foodX, foodY, grid, grid);

  u8g2.sendBuffer();
}

void setup() {
  pinMode(SW_pin, INPUT_PULLUP);
  Serial.begin(115200);
  u8g2.begin();
}

void loop() {
  switch (etatJeux) {
    case MENU:
      {

        int isPressed = digitalRead(SW_pin);

        afficherMenu();

        if(isPressed == 0){

              etatJeux = JEU;
              delay(200);
        }
        break;
      }
    case JEU:

      afficherJeu();
    
      break;
  }
}