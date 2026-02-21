#include "Controller.h"

// IDK how any of this works

// TODO: placeholder
int armDirectionPin = 12;
int armBrakePin = 9;
int armpwmPin = 3;

void onPressTest() {
  Serial.println("Button pressed!");
}

// Move a bit in the HIGH direction
void powerArmHigh() {
  digitalWrite(armDirectionPin, HIGH);
  digitalWrite(armBrakePin, LOW);
  analogWrite(armpwmPin, 30);
  delay(500); // TODO: configure this
  digitalWrite(armBrakePin, HIGH);
  analogWrite(armpwmPin, 0);
}

// Move a bit in the LOW direction
void powerArmLow() {
  digitalWrite(armDirectionPin, LOW);
  digitalWrite(armBrakePin, LOW);
  analogWrite(armpwmPin, 30);
  delay(500); // TODO: configure this
  digitalWrite(armBrakePin, HIGH);
  analogWrite(armpwmPin, 0);
}

Controller controller("NoahsArch", "SurvivedTheFlood");
void setup() {
  Serial.begin(115200);

  // Configure pins
  controller.configureL298N(
    9,7,6,10,5,4
  );

  // Set motor PWM for a medium-weight robot
  controller.setMotorMinPWM(90);

  // Stops after no command received
  controller.setFailsafeTimeoutMs(1200);

  // Enable status LED
  controller.enableStatusLED(LED_BUILTIN);

  // Add buttons
  // controller.registerButton("Button!", onPressTest);
  // controller.registerButton("Arm LOW", powerArmLow);
  // controller.registerButton("Arm HIGH", powerArmHigh)
;
  // Set arm pin mode
  // pinMode(armDirectionPin, OUTPUT);

  controller.beginAP(true);   // true = enable debug
}

void loop() {
  controller.update();
}
