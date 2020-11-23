#include <Adafruit_CircuitPlayground.h>

float value = 0;


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(150);

//  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Take 10 milliseconds of sound data to calculate
  value = CircuitPlayground.mic.soundPressureLevel(10);
  
  Serial.println(value);
   
  
  if (value > 65){
     for (int i = 1; i < 10; i+=2) {
          CircuitPlayground.setPixelColor(i,115, 195, 108);
    }
    delay(400);
    CircuitPlayground.clearPixels();
   // delay(1000);
  }

  if (value > 85){
    for (int i = 0; i < 10; i+=2) {
          CircuitPlayground.setPixelColor(i, 255, 247, 0);
    }
    delay(300);
    CircuitPlayground.clearPixels();
    delay(500);
  }

  if (value > 100){
     for (int i = 0; i < 10; i++) {
          CircuitPlayground.setPixelColor(i, 255, 0, 0);
          CircuitPlayground.playTone(300, 500);
    }
    delay(300);
    CircuitPlayground.clearPixels();
    delay(500);
  }
  
  
}
