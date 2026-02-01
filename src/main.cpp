#include <Arduino.h>

#define SIMULATED_IR_PIN 13

// Constants based on your provided table
const uint32_t IR_ON    = 0xFC03EF00;
const uint32_t IR_OFF   = 0xFD02EF00;
const uint32_t IR_RED   = 0xFB04EF00;
const uint32_t IR_GREEN = 0xFA05EF00;
const uint32_t IR_BLUE  = 0xF906EF00;

void setup() {
  pinMode(SIMULATED_IR_PIN, OUTPUT);
  digitalWrite(SIMULATED_IR_PIN, HIGH); 
  
  Serial.begin(115200);
  Serial.println("Starting IR Signal Simulation...");
}

void transmitPulse(unsigned long lowTime, unsigned long highTime) {
  digitalWrite(SIMULATED_IR_PIN, LOW);   // Signal detected (Active LOW)
  delayMicroseconds(lowTime);
  digitalWrite(SIMULATED_IR_PIN, HIGH);  // Space/Idle
  delayMicroseconds(highTime);
}

void sendNEC(uint32_t rawData) {
  // Header: 9ms pulse followed by 4.5ms space
  transmitPulse(9000, 4500);

  // 32-bit Data payload (LSB first)
  for (int i = 0; i < 32; i++) {
    if (rawData & (1UL << i)) {
      // Bit 1: 560us pulse, 1680us space
      transmitPulse(560, 1680);
    } else {
      // Bit 0: 560us pulse, 560us space
      transmitPulse(560, 560);
    }
  }

  // Stop Bit: 560us pulse to terminate the last bit
  digitalWrite(SIMULATED_IR_PIN, LOW);
  delayMicroseconds(560);
  digitalWrite(SIMULATED_IR_PIN, HIGH);
}

void loop() {
  Serial.println("Sending: ON");
  sendNEC(IR_ON);
  delay(3000);

  Serial.println("Sending: RED");
  sendNEC(IR_RED);
  delay(3000);

  Serial.println("Sending: GREEN");
  sendNEC(IR_GREEN);
  delay(3000);

  Serial.println("Sending: BLUE");
  sendNEC(IR_BLUE);
  delay(3000);

  Serial.println("Sending: OFF");
  sendNEC(IR_OFF);
  delay(3000);
}