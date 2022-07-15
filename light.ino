#define NUM_LEDS 1
#include "FastLED.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

#define PIN 8
#define NUM_READINGS 10
CRGB leds[NUM_LEDS];
byte i=0;
int val_max=0;
int N=10;

float vout = 0;
int val[20];
void setup(){
  lcd.init();                     
  lcd.backlight();
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
  pinMode(8, OUTPUT);
  leds[0] = CRGB::White;
  delay(100);
  lcd.begin(16, 2);

  lcd.setCursor(0,1);

  lcd.print("LIGHT: ");

}
void loop() {
  FastLED.show();
 
  for(int i = 0; i < 8; i++){ // запускаем цикл, для заполнения массива
    val[i] = analogRead(A0);
  }
  val_max=0;
  for(int i = 0; i < 8; i++){ // запускаем цикл, для обхода всех элементов массива
    val_max = max(val_max, val[i]);
  }

  vout=(5.0/1024.0)*val_max;
  Serial.println(vout);
  lcd.setCursor(7,1);

  lcd.print(vout);

delay(100);
  
}
