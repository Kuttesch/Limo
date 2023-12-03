#include <Stepper.h>

int SPU = 2048;
int MAX = 360;

Stepper Motor1(SPU, 8, 10, 9, 11);
Stepper Motor2(SPU, 3, 5, 4, 6);

void setup()
{
  Motor1.setSpeed(10);
  Motor2.setSpeed(10);
  Serial.begin(9600);
  while (!Serial) { ; }
}

int position1 = 0;
int target1 = 0;

int position2 = 0;
int target2 = 0;

void loop() {
  if (Serial.available() > 0) {
    target1 = minimize(Serial.parseInt(SKIP_NONE));
    Serial.read();
    target2 = minimize(Serial.parseInt(SKIP_NONE));
  }
  advance(&Motor1, &position1, target1);
  advance(&Motor2, &position2, target2);
}

void advance(Stepper *motor, int *position, int target) {
    int distance = target - *position;
    if (distance < 0) {
      move(motor, position, -1);
    } else {
      move(motor, position, 1);
    }
}

int minimize(int n) {
    while (n >= MAX) {
      n -= MAX;
    }
    return n;
}

void move(Stepper *motor, int *position, int deg) {
  *position += deg;
  motor->step(getSteps(deg));
  *position = minimize(*position);
}

int getSteps(int deg) {
  return (float(deg) / MAX) * SPU;
}
