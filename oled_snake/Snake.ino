#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int foodX = 0;
int foodY = 0;
int grid = 4;

unsigned long dernierFruit = 0;

void spawnFood() {
  foodX = random(0, 128 / grid) * grid;
  foodY = random(0, 64 / grid) * grid ;
}

void setup() {
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.drawStr(35, 30, "SNAKE");
  u8g2.sendBuffer();

  delay(3000);

  spawnFood();
  dernierFruit = millis();
}

void loop() {
  if (millis() - dernierFruit >= 2000) {
    spawnFood();
    dernierFruit = millis();
  }

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.drawStr(1, 6, "Score: 0");

  u8g2.drawHLine(0, 7, 128);

  for (int y = 8; y < 64; y += grid) {
    for (int x = 0; x < 128; x += grid) {
      u8g2.drawPixel(x, y);
    }
  }

  u8g2.drawFrame(foodX, foodY, grid, grid);

  u8g2.sendBuffer();
}