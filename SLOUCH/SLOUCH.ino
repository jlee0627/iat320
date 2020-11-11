#include <Adafruit_CircuitPlayground.h>
 
#define SLOUCH_ANGLE        10.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         3000      // allowable slouch time (secs) 
#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees

#define SLOUCH_OVERTIME     9000  
 
float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;

int presets[3][2][3] = {
  {
    {27, 167, 132}, {152, 54, 128} 
  },
  {
    {0, 0, 255}, {255, 215, 26} 
  },
  {
    {230, 50, 50}, {255, 0, 0} 
  }
};

int preset = 0;
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialize Circuit Playground
  CircuitPlayground.begin();
 
  // Initialize target angle to zero.
  targetAngle = 0;
  CircuitPlayground.setBrightness(255);
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  // Compute current angle
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);
 
  // Set target angle on button press
  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900,100);
    delay(100);
    CircuitPlayground.playTone(900,100);
    delay(100);
  }
  
  // Check for slouching
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) slouchStartTime = millis();
    slouching = true;
  } else {
    slouching = false;
  }
 
  // If we are slouching
  if (slouching) {
    // Check how long we've been slouching
    if (millis() - slouchStartTime > SLOUCH_TIME) {
      // Play a tone
      CircuitPlayground.playTone(300, 500);
      delay(50);    
    }   
    if (slouching) {
      if (millis() - slouchStartTime > SLOUCH_OVERTIME) {     
        CircuitPlayground.playTone(600, 500);
        for (int i = 0; i < 10; i++) {
          CircuitPlayground.setPixelColor(i, presets[preset][i % 2][0], presets[preset][i % 2][1], presets[preset][i % 2][2]);
        }
        delay(100);
        
        CircuitPlayground.clearPixels();
        delay(50);
      }
    } 
  }
}
