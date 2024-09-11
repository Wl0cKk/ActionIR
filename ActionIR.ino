#include <Arduino.h>

#define DECODE_NEC
#define DECODE_DISTANCE_WIDTH

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#define motionSensorPin 2

void setup() {
    Serial.begin(115200);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
    IrSender.begin();
    Serial.println(F("Send IR signals at pin " STR(IR_SEND_PIN)));

    pinMode(motionSensorPin, INPUT);
}

uint16_t sAddress = 0xEF00;
uint8_t sCommandOn = 0x03;
uint8_t sCommandOff = 0x02;
bool isOn = false;

unsigned long motionDetectedTime = 0;

void send_ir_data(bool on) {
    Serial.print(F("Sending: 0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command: 0x"));
    if (on) {
        Serial.println(sCommandOn, HEX);
        IrSender.sendNEC(sAddress, sCommandOn, 1);
    } else {
        Serial.println(sCommandOff, HEX);
        IrSender.sendNEC(sAddress, sCommandOff, 1);
    }
    delay(10);
}

void countdown(int seconds) {
    for (int i = seconds; i > 0; i--) {
        Serial.println(i);
        delay(1000);
    }
}

void loop() {
    int motionState = digitalRead(motionSensorPin);
    if (motionState == HIGH && !isOn) {
        send_ir_data(true);
        send_ir_data(true);
        send_ir_data(true);
        isOn = true;
        motionDetectedTime = millis();
        Serial.println("Motion Detected");
    }
    if (isOn && (millis() - motionDetectedTime >= 10000)) {
        send_ir_data(false);
        send_ir_data(false);
        send_ir_data(false);
        isOn = false;
        Serial.println("Timer finished. No motion detected.");
    }

    if (isOn) {
        countdown(10); // delay in sec
    }
    delay(100);
}