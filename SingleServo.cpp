#include <Stepper.h>

int SPU = 2048;
int MAX = 360;

Stepper Motor(SPU, 8, 10, 9,11);

void setup()
{
  Motor.setSpeed(10);
  Serial.begin(9600);
  while (!Serial) { ; }
}

int position = 0;
int target = 0;

void loop() {
  if (Serial.available() > 0) {
    target = normalize(Serial.parseInt(SKIP_NONE));
    Serial.print("Target: ");
    Serial.println(target);
  }
  if (position != target) {
    int distance = target - position;
    if (distance < 0) {
      move(-1);
    } else {
      move(1);
    }
  }
}

int normalize(int n) {
    while (n >= MAX) {
      n -= MAX;
    }
    while (n < 0) {
      n += MAX;
    }
    return n;
}

void move(int deg) {
  position += deg;
  Motor.step(getSteps(deg));
  position = normalize(position);
}

int getSteps(int deg) {
  return (float(deg) / MAX) * SPU;
}
