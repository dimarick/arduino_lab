#include <Arduino.h>

#define LED_3 3
#define LED_4 4
#define LED_5 5

#define RED LED_3
#define GREEN LED_4
#define YELLOW LED_5

#define SW1 2
#define SW1_ON LOW

// Номер задания от 1 до 6 включительно. 6 - задание индивидуальное по вариантам.
static int taskNo = 1;
static int sw1 = 0;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
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

    switch (taskNo) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break;
        default:
            break;
    }
}

// Задание 1. При нажатии кнопки включается и мигает каждые 500 мс светодиод на пятом пине.
// При отжатой кнопке сначала включается и затем гаснет светодиод на третьем пине,
// затем через 500 мс включается и гаснет светодиод на четвёртом пине.
// И с паузой в 500 мс схема горении светодиодов повторятся до тех пор,
// пока кнопка остаётся отжатой.
void task1() {
    if (sw1 == SW1_ON) {
        // При нажатии кнопки мигаем с периодом 500 мс
        ledOn(LED_5, 100);
        delay(400);
    } else {
        // При отжатой кнопке сначала включается и затем гаснет светодиод на третьем пине
        ledOn(LED_3, 100);
        // затем через 500 мс
        delay(500);
        // включается и гаснет светодиод на четвёртом пине.
        ledOn(LED_4, 100);
        // И с паузой в 500 мс схема горении светодиодов повторятся до тех пор, пока кнопка остаётся отжатой.
        delay(500);
    }
}

// Задание 2. При нажатии кнопки поочередно включаются красный, зеленый, желтый светодиоды с паузой в секунду.
// При отключении кнопки светодиоды гаснут в таком-же порядке с паузой в секунду.

static bool ledsOn[] = {false, false, false};

void task2() {
    if (sw1 == SW1_ON) {
        if (!ledsOn[0]) {
            ledsOn[0] = true;
            digitalWrite(RED, HIGH);
        } else if (!ledsOn[1]) {
            ledsOn[1] = true;
            digitalWrite(GREEN, HIGH);
        } else if (!ledsOn[2]) {
            ledsOn[2] = true;
            digitalWrite(YELLOW, HIGH);
        }
        delay(1000);
    } else {
        if (ledsOn[0]) {
            ledsOn[0] = false;
            digitalWrite(RED, LOW);
        } else if (ledsOn[1]) {
            ledsOn[1] = false;
            digitalWrite(GREEN, LOW);
        } else if (ledsOn[2]) {
            ledsOn[2] = false;
            digitalWrite(YELLOW, LOW);
        }
        delay(1000);
    }
}

static bool redOn = true;

// Задание 3. Если нажата кнопка, то каждые полсекунды поочередно включаются 3 (красный) и 5 (желтый) светодиод.
// 4 (зеленый) не включается.
// Если кнопка не нажата, то каждые 250 мс. Мигает 4 светодиод. 3 и 5 не включаются.
void task3() {
    if (sw1 == SW1_ON) {
        digitalWrite(LED_3, redOn ? LOW : HIGH);
        digitalWrite(LED_5, redOn ? HIGH : LOW);
        redOn = !redOn;
        delay(500);
    } else {
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_5, LOW);
        digitalWrite(LED_4, HIGH);
        delay(50);
        digitalWrite(LED_4, LOW);
        delay(200);
    }
}

// Задание 4. Если кнопка нажата, то все светодиоды будут выключены.
// Если не нажата, то все светодиоды будут вместе каждые 500 мс мигать.
void task4() {
    if (sw1 == SW1_ON) {
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, LOW);
        delay(100);
    } else {
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_4, HIGH);
        digitalWrite(LED_5, HIGH);
        delay(50);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, LOW);
        delay(450);
    }
}

// Задание 5. Если кнопка нажата, то горят красный, зеленый и желтый вместе.
// Если кнопку отжать, то 2 раза повторяется цикл: горит красный, пауза в 1 с, горит зеленый,
// пауза в 1 с, горит желтый, пауза в 1 с и т.д.
void task5() {
    if (sw1 == SW1_ON) {
        digitalWrite(RED, HIGH);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, HIGH);
        delay(100);
    } else {
        digitalWrite(RED, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(GREEN, LOW);

        for (int i = 0; i < 2; i++) {
            ledOn(RED, 1000);
            delay(1000);
            ledOn(GREEN, 1000);
            delay(1000);
            ledOn(YELLOW, 1000);
            delay(1000);
        }
    }
}

// Задание 6 (Индивидуальное), вариант 5.
//Первый этап. Последовательное горение лампочек:
//кр(1 с) -> пауза (1 с) -> кр (1 с) -> пауза (1 с) -> з (1 с) -> пауза (1 с) -> ж (1 с)
//Повторение: 5 раз

//Второй этап. Одновременное зажигание и мигание двух лампочек –
// красной и жёлтой - с частотой мигания 2 раза в 1 секунду.
// Миганий – всего – 12 раз.

//Третий этап. Мигание лампочек по две – по три в цикле:
//[2с (Кр+з)+2с (пауза)+2с (кр+з+ж)+2с (пауза)]
//
//10 миганий [*] по 8 секунд

void task6() {
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