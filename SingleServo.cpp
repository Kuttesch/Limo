#include <Stepper.h>

int SPU = 2048;
int MAX = 3;

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
    target = Serial.parseInt(SKIP_NONE);
    target = minimize(target);
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

int minimize(int n) {
    while (n >= MAX) {
      n -= MAX;
    }
    return n;
}

void move(int deg) {
  position += deg;
  Motor.step(getSteps(deg));
  position = minimize(position);
}

int getSteps(int deg) {
  return (float(deg) / MAX) * SPU;
}
