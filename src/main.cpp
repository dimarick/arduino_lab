#include <Arduino.h>

#define RED 4
#define YELLOW 5
#define GREEN 6

#define SW1 2
#define SW1_ON LOW

static int sw1 = 0;

void ledOn(int pin, unsigned long ms);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
    // обязательно используем подтягивающие резисторы, так как пины висят "в воздухе"
    pinMode(SW1, INPUT_PULLUP);
}

void loop() {
    sw1 = digitalRead(SW1);

    // Индикатор нажатия кнопки
    digitalWrite(LED_BUILTIN, sw1 == SW1_ON ? HIGH : LOW);

    if (sw1 != SW1_ON) {
        return;
    }

    for (int i = 0; i < 5; i++) {
        ledOn(RED, 1000);
        delay(1000);
        ledOn(RED, 1000);
        delay(1000);
        ledOn(GREEN, 1000);
        delay(1000);
        ledOn(YELLOW, 1000);
        delay(1000);
    }
    for (int i = 0; i < 12; i++) {
        digitalWrite(RED, HIGH);
        digitalWrite(YELLOW, HIGH);
        delay(250);
        digitalWrite(RED, LOW);
        digitalWrite(YELLOW, LOW);
        delay(250);
    }
    for (int i = 0; i < 10; i++) {
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        delay(2000);
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        delay(2000);
        digitalWrite(RED, HIGH);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, HIGH);
        delay(2000);
        digitalWrite(RED, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(GREEN, LOW);
        delay(2000);
    }
}

void ledOn(int pin, unsigned long ms) {
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin, LOW);
}