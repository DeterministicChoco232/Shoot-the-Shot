#include "Controller.h"

Controller controller("NoahsArch", "SurvivedTheFlood");
void setup() {
  Serial.begin(115200);

  // Configure pins
  controller.configureL298N(9,7,6,10,5,4);

  // Set motor PWM for a medium-weight robot
  controller.setMotorMinPWM(90);

  // Stops after no command received
  controller.setFailsafeTimeoutMs(1200);

  // Enable status LED
  controller.enableStatusLED(LED_BUILTIN);

  controller.beginAP(true);   // true = enable debug
}

void loop() {
  controller.update();
}
