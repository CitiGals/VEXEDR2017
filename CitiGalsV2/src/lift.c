#include "main.h"
#include "ports.h"

void liftSet(int speed) {
  motorSet(LIFT_MOTOR, speed);
}
