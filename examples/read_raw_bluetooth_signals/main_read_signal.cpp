#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 13

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}


void loop() {
  if (IrReceiver.decode()) {

    IrReceiver.printIRResultShort(&Serial);
    Serial.println();

    IrReceiver.resume();
  }
}