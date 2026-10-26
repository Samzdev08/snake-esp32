#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int foodX = 0;
int foodY = 0;
int grid = 8;

const int SW_pin = 12;
const int X_pin = 34;
const int Y_pin = 35;
const int BUZZER_pin = 5;

int lastMove = 0;

int gameSpeed = 180;

int nextDirX = 1;
int nextDirY = 0;

int snakeLength = 5;

int dirX = 1;
int dirY = 0;

int snakeX[20];
int snakeY[20];

int centreX = 0;
int centreY = 0;
const int ZONE_MORTE = 1000;


enum Etat { MENU,
            JEU,
            GAME_OVER };

Etat etatJeux = MENU;

int record = 0;


int choixGameOver = 0;


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



void declencherGameOver() {
  int score = snakeLength - 5;
  if (score > record) {
    record = score;
  }
  choixGameOver = 0;
  etatJeux = GAME_OVER;

  digitalWrite(BUZZER_pin, HIGH);
  delay(400);
  digitalWrite(BUZZER_pin, LOW);
}

void afficherGameOver() {


  int x = analogRead(X_pin);
  if (x < 1000) {
    choixGameOver = 0;
  } else if (x > 3000) {
    choixGameOver = 1;
  }

  int score = snakeLength - 5;

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

  if (digitalRead(SW_pin) == 0) {
    digitalWrite(BUZZER_pin, HIGH);
    delay(100);
    digitalWrite(BUZZER_pin, LOW);


    while (digitalRead(SW_pin) == 0) {
      delay(10);
    }

    if (choixGameOver == 0) {
      etatJeux = JEU;
      reset();

    } else {
      etatJeux = MENU;
      reset();
    }
  }
}

void reset() {
  
  centreX = analogRead(X_pin);
  centreY = analogRead(Y_pin);

  snakeLength = 5;

  dirX = 1;
  dirY = 0;
  nextDirX = 1;
  nextDirY = 0;

  snakeX[0] = 48;
  snakeY[0] = 32;

  snakeX[1] = 40;
  snakeY[1] = 32;

  snakeX[2] = 32;
  snakeY[2] = 32;

  snakeX[3] = 24;
  snakeY[3] = 32;

  snakeX[4] = 16;
  snakeY[4] = 32;

  spawnFood();
}

void lireJoystick() {

  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);

  Serial.println(x);
  Serial.println(y);

  int dx = x - centreX;
  int dy = y - centreY;

  if (abs(dx) > abs(dy) && abs(dx) > ZONE_MORTE) {
    nextDirX = (dx > 0) ? 1 : -1;
    nextDirY = 0;
  } else if (abs(dy) > abs(dx) && abs(dy) > ZONE_MORTE) {
    nextDirX = 0;
    nextDirY = (dy > 0) ? 1 : -1;
  }

  if (!(nextDirX == -dirX && nextDirY == -dirY)) {
    dirX = nextDirX;
    dirY = nextDirY;
  }

  for (int i = snakeLength; i > 0; i--) {

    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX * grid;
  snakeY[0] += dirY * grid;
}

void afficherJeu() {

  u8g2.clearBuffer();


  for (int i = 0; i < snakeLength; i++) {

    if (snakeX[i] >= 0 && snakeX[i] + grid <= 128
        && snakeY[i] >= 16 && snakeY[i] + grid <= 64) {

      u8g2.drawBox(snakeX[i], snakeY[i], grid, grid);

    } else {
      declencherGameOver();
      return;
    }
  }

  if (millis() - lastMove > gameSpeed) {

    lastMove = millis();
    lireJoystick();

    if (snakeX[0] == foodX && snakeY[0] == foodY) {
      snakeLength++;
      spawnFood();
    }
  }

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
  pinMode(BUZZER_pin, OUTPUT);
  Serial.begin(115200);
  u8g2.begin();

  centreX = analogRead(X_pin);
  centreY = analogRead(Y_pin);


  snakeX[0] = 48;
  snakeY[0] = 32;

  snakeX[1] = 40;
  snakeY[1] = 32;

  snakeX[2] = 32;
  snakeY[2] = 32;

  snakeX[3] = 24;
  snakeY[3] = 32;

  snakeX[4] = 16;
  snakeY[4] = 32;

  spawnFood();
}

void loop() {
  switch (etatJeux) {
    case MENU:
      {

        int isPressed = digitalRead(SW_pin);

        afficherMenu();

        if (isPressed == 0) {

          etatJeux = JEU;
          digitalWrite(BUZZER_pin, HIGH);
          delay(100);
          digitalWrite(BUZZER_pin, LOW);
          delay(200);
        }
        break;
      }
    case JEU:

      afficherJeu();

      break;


    case GAME_OVER:

      afficherGameOver();

      break;
  }
}
