#include "main.h"
#include "claw.h"
#include "ports.h"

void clawSet(int speed) {
  motorSet(CLAW_MOTOR, -speed);
}
