#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

#define pinLed1 10
#define pinLed2 9

void(*funcRestart)(void) = 0; // self restart program

// Ukuran tumpukan (stack size) untuk masing-masing program
static uint16_t STACK_SIZE = 256; // 256 byte 

// Handle Program
TaskHandle_t handleProgram1, handleProgram2;

// Deklarasi fungsi program
void program1(void *pvParameter) {
  (void) pvParameter; // untuk menghindari warning tidak terpakai
  int i = 1;
  while(true) {
    Serial.println(F("Task 1 Running"));
    digitalWrite(pinLed1, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(pinLed1, LOW);
    vTaskDelay(pdMS_TO_TICKS(100));
    if(i > 20) {
      Serial.println(F("Task 1 Stopped"));
      vTaskDelete(handleProgram1);
    }
    i++;
  }
}

void program2(void *pvParameter) {
  (void) pvParameter; // untuk menghindari warning tidak terpakai
  int i = 1;
  while(true) {
    Serial.println(F("Task 2 Running"));
    digitalWrite(pinLed2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));
    digitalWrite(pinLed2, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
    if(i > 5) {
      Serial.println(F("Task 2 Stopped"));
      vTaskDelete(handleProgram2);
    }
    i++;
  }
}

void RestartProgram(void *pvParameter) {
  while(true) {
    Serial.println(F("\n\n\n\nSelf Restart\n Bye...\n\n"));
    vTaskDelay(pdMS_TO_TICKS(30000));
    funcRestart();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  // Buat task tiap fungsi program
  xTaskCreate(program1, "Program 1", STACK_SIZE, NULL, 1, &handleProgram1);
  xTaskCreate(program2, "Program 2", STACK_SIZE, NULL, 2, &handleProgram2);
  xTaskCreate(RestartProgram, "Restart Program", STACK_SIZE, NULL, 3, NULL);

  // Mulai scheduler
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  // NOTHING
}
