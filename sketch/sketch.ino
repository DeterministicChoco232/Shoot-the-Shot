#include "Controller.h"
#include <vector>

// Arm settings
#define in1 3
#define in2 2
#define en 11  // pwm
unsigned int arm_pwm = 255;
unsigned int pulse_delay = 500;
bool using_arm = true;
std::vector<long double> w = {};

void increase_pwm() {arm_pwm += 10;}

void decrease_pwm() {arm_pwm -= 10;}

void increase_delay() {pulse_delay+=25;}

void decrease_delay() {pulse_delay-=25;}

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
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
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
  arm_pwm = 80;
  enableForward();
  delay(1250);
  enableBackward();
  delay(1250);
  armBrake();
  arm_pwm = old;
}  unsigned int old = arm_pwm;


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

Controller controller("NoahsArch", "SurvivedTheFlood");
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
    controller.registerButton("Arm Forward", pulseForward);
    controller.registerButton("Arm Backward", pulseBackward);
    controller.registerButton("Arm Reset", armReset);
    controller.registerButton("Arm PWM +10", increase_pwm);
    controller.registerButton("Arm PWM -10", decrease_pwm);
    controller.registerButton("Arm Delay +25", increase_delay);
    controller.registerButton("Arm Delay -25", decrease_delay);
  }
}

void loop() {
  arm_pwm = controller.pwmValue;
  pulse_delay = controller.timeDelayMs;
  controller.update();
}
