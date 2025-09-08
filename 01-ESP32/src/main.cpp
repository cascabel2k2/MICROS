#include <Arduino.h>

// Pin del LED incorporado del ESP32 (generalmente GPIO 2)
#define LED_PIN 2

// Intervalo de parpadeo en milisegundos
#define BLINK_INTERVAL 500

void setup() {
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  
  // Inicializar la comunicación serie para debugging (opcional)
  Serial.begin(115200);
  Serial.println("ESP32 LED Blink iniciado");
}

void loop() {
  // Encender el LED
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(BLINK_INTERVAL);
  
  // Apagar el LED
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(BLINK_INTERVAL);
}

