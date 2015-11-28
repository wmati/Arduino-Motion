
#include "SPI.h"
#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"
const int pingPin = 3;
long cm1;

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setTextWrap(true);

  {
    long duration1;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    pinMode(pingPin, INPUT);
    duration1 = pulseIn(pingPin, HIGH);

    // convert the time into a distance
 
    cm1 = microsecondsToCentimeters(duration1);


   
   iText(cm1);
  }
  

}


void loop(void) {
    long duration, inches, cm;
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

   
    if (cm+1 == cm1 || cm-1 == cm1 || cm1 == cm) {
      delay(1);
    } else {
    testText(cm);
    
    }

  }

unsigned long testText(long cm1) {

  tft.setRotation(1);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  
  if (cm1 >= 100){
    tft.println("______");
    tft.println();
    tft.print(cm1*0.01);
    tft.print(" m away");
    tft.println();
    delay(500);
  } else {
  tft.println("______");
  tft.println();
  tft.print(cm1);
  tft.print(" cm away");
  tft.println();
  delay(500);

   
  }
  
}

unsigned long iText(long cm1) {
 
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(1);
  tft.print("Initial Distance");
  if (cm1 >= 100){
    tft.println();
    tft.println("______");
    tft.println();
    tft.print(cm1*0.01);
    tft.print(" m away");
    tft.println();
    delay(500);
  } else {
     tft.println();
  tft.println("______");
  tft.println();
  tft.print(cm1);
  tft.print(" cm away");
  tft.println();
  }
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println();

  tft.print("Disruptions");
  tft.println();
  delay(0);

}




long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) { 
  return microseconds / 29 / 2;
}






