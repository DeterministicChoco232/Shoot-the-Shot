#include "Controller.h"
#include <vector>

// Arm settings
#define in1 3
#define in2 2
#define en 11  // pwm
unsigned int arm_pwm;
unsigned int pulse_delay;
bool using_arm = true;
std::vector<long double> w = {};


// long double distToTime(long double d) {
//   long double ret = 0;
//   long double dPow = 1;
//   for(size_t i=0; i<w.size(); ++i) {
//     ret += w[i] * dPow;
//     dPow*=d;
//   }
//   return ret;
// }

void armBrake() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(en, 0);
}

void armRelease() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(en, 0);
  delay(500);
  armBrake();
}

// in1 HIGH, in2 LOW
void enableForward() {
  armBrake();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en, arm_pwm);
}

// in1 LOW, in2 HIGH
void enableBackward() {
  armBrake();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(en, arm_pwm);
}

void armReset() {
  unsigned int old = arm_pwm;
  arm_pwm = 40;
  enableBackward();
  delay(700);
  armBrake();
  arm_pwm = old;
}


void pulseForward() {
  enableForward();
  delay(pulse_delay);
  armBrake();
}

void pulseBackward() {
  enableBackward();
  delay(pulse_delay);
  armBrake();
  delay(200);
  armReset();
}

void updatePwm(int val) {
  arm_pwm = val;
}

void updateDelay(int val) {
  pulse_delay = val;
}

Controller controller("NoahsArch", "SurvivedTheFlood");

int nudgeThr = 40;
int nudgeDur = 120;
void nudgeLeft() {
  controller.nudgeLeft(nudgeThr, nudgeDur);
}

void nudgeRight() {
  controller.nudgeRight(nudgeThr, nudgeDur);
}
void nudgeFront() {
  controller.nudgeFront(nudgeThr, nudgeDur);
}

void nudgeBack() {
  controller.nudgeBack(nudgeThr, nudgeDur);
}
void nudgeLeft5() {
  for(int i=0; i<5; ++i)
  controller.nudgeLeft(nudgeThr, nudgeDur);
}

void nudgeRight5() {
  for(int i=0; i<5; ++i)
  controller.nudgeRight(nudgeThr, nudgeDur);
}
void nudgeFront5() {
  for(int i=0; i<5; ++i)
  controller.nudgeFront(nudgeThr, nudgeDur);
}

void nudgeBack5() {
  for(int i=0; i<5; ++i)
  controller.nudgeBack(nudgeThr, nudgeDur);
}
void setup() {
  // Movement control
  Serial.begin(115200);
  controller.configureL298N(
    9,7,6, // ENA, IN1, IN2
    10,5,4 // ENB, IN3, IN4
  );
  controller.setMotorMinPWM(90);
  controller.setFailsafeTimeoutMs(1200);
  controller.enableStatusLED(LED_BUILTIN);
  controller.beginAP(true);   // true = enable debug

  // Arm control
  if (using_arm) {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en, OUTPUT);

    // Add buttons
    //controller.registerButton("Arm Forward", pulseForward);
    controller.registerButton("SHOOT", pulseBackward);
    controller.registerButton("Reset", armReset);
    controller.registerSlider("Arm pwm", updatePwm, 30, 255, 255, 1);
    controller.registerSlider("Pulse delay", updateDelay, 100, 1000, 400, 10);
  }
    controller.registerButton("Nudge Left", nudgeLeft);
    controller.registerButton("Nudge Right", nudgeRight);
    controller.registerButton("Nudge Front", nudgeFront);
    controller.registerButton("Nudge Back", nudgeBack);
    controller.registerButton("Nudge Left x5", nudgeLeft5);
    controller.registerButton("Nudge Right x5", nudgeRight5);
    controller.registerButton("Nudge Front x5", nudgeFront5);
    controller.registerButton("Nudge Back x5", nudgeBack5);
  
}

void loop() {
  controller.update();
}
