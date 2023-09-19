#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define pinLed1 10
#define pinLed2 9

// Ukuran tumpukan (stack size) untuk masing-masing program
#define STACK_SIZE 128

int i = 0;
// Deklarasi fungsi program
void program1(void *pvParameter) {
  (void) pvParameter; // untuk menghindari warning tidak terpakai
  for(;;) {
    Serial.println(F("Task 1 Running"));
    digitalWrite(pinLed1, HIGH);
    delay(100);
    digitalWrite(pinLed1, LOW);
    delay(100);
  }
}

void program2(void *pvParameter) {
  (void) pvParameter; // untuk menghindari warning tidak terpakai
  for (;;) {
    Serial.println(F("Task 2 Running"));
    digitalWrite(pinLed2, HIGH);
    delay(1000);
    digitalWrite(pinLed2, LOW);
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  // Buat task program1 dan program2
  xTaskCreate(program1, "Program 1", STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(program2, "Program 2", STACK_SIZE, NULL, 2, NULL);

  // Mulai scheduler
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  // NOTHING
}
