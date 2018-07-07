#include "main.h"    // includes API.h and other headers
#include "chassis.h" // redundant, but ensures that the corresponding header file (chassis.h) is included
#include "ports.h"

void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR, left);
  motorSet(RIGHT_MOTOR, right);
}
