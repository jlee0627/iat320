#include <Adafruit_CircuitPlayground.h>

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

bool lastRightPress = false;
bool lastLeftPress = false;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {

  bool leftPress = CircuitPlayground.leftButton();
  if (leftPress && (lastLeftPress == false)) {
    preset = ((preset - 1) + 3) % 3;
  }
  lastLeftPress = leftPress;

  bool rightPress = CircuitPlayground.rightButton();
  if (rightPress && (lastRightPress == false)) {
    preset = (preset + 1) % 3;
  }
  lastRightPress = rightPress;

  float acc = abs(CircuitPlayground.motionX()) + abs (CircuitPlayground.motionY()) + abs (CircuitPlayground.motionZ());
  if (acc > 25) {
    preset = rand() % 3;
  }

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor (i, presets[preset][i % 2][0], presets[preset][i % 2][1], presets[preset][i % 2][2]);
  }

  delay (10);
}
