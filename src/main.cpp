#include <Arduino.h>
#include <LiquidCrystal.h>
#include <math.h>

const float Coef = 0.00488;
const float R_out = 10000;
const float A = 0.001129148;
const float B = 0.000234125;
const float C = 0.0000000876741;

float Temperature;
float R_thermistor;
float raw;
float V_out;


const char* scrollingText = "Temperature in room: ";
const int textLen = 21;
int scrollPosition = 0;
unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 300;

// Пины LCD
constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  raw = analogRead(A0);
  V_out = raw * Coef;
  R_thermistor = R_out / (5.0 / V_out - 1);
  Temperature = 1 / (A + B * log(R_thermistor) + C * pow(log(R_thermistor), 3)) - 273.15;


  if (millis() - lastScrollTime >= scrollInterval) {
    lastScrollTime = millis();
    scrollPosition++;
    if (scrollPosition > textLen) {
      scrollPosition = 0;
    }
  }


  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    int index = (scrollPosition + i) % textLen;
    lcd.print(scrollingText[index]);
  }

  /
  lcd.setCursor(0, 1);
  lcd.print(Temperature);
  lcd.print(" C   ");

  delay(300);
}