#include "Controller.h"

void onPress() {
  Serial.println("Button pressed!");
}

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

  // Add button
  controller.registerButton("Button!", onPress);

  controller.beginAP(true);   // true = enable debug
}

void loop() {
  controller.update();
}
