#include <Arduino.h>
#include "son.h"
#include "config.h"

void bip(int ms) {
  digitalWrite(BUZZER_pin, HIGH);
  delay(ms);
  digitalWrite(BUZZER_pin, LOW);
}
