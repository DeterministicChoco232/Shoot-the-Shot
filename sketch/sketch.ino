#include "Controller.h"

Controller controller("NoahsArch", "SurvivedTheFlood");
void setup() {
  Serial.begin(115200);
  controller.beginAP(true);   // true = enable debug
}

void loop() {
  controller.update();
}
