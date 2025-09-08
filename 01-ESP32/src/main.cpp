#include <Arduino.h>
#include <WiFi.h>

// Pin del LED incorporado del ESP32 (generalmente GPIO 2)
#define LED_PIN 2

// Intervalo de parpadeo en milisegundos
#define BLINK_INTERVAL 500

// Credenciales WiFi - REEMPLAZA CON TUS DATOS
const char* ssid = "Flia_Agreda";
const char* password = "777XonarGen";

// Variable para controlar el estado de conexión WiFi
bool wifiConnected = false;

void connectToWiFi();

void setup() {
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  
  // Inicializar la comunicación serie
  Serial.begin(115200);
  Serial.println("ESP32 LED Blink con WiFi iniciado");
  
  // Conectar a WiFi
  connectToWiFi();
}

void connectToWiFi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  
  // Intentar conectar con timeout
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    Serial.println("");
    Serial.println("¡WiFi conectado exitosamente!");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Error: No se pudo conectar a WiFi");
    Serial.println("Verifica tus credenciales y que la red esté disponible");
  }
}

void loop() {
  // Verificar conexión WiFi periódicamente
  if (!wifiConnected && WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    Serial.println("WiFi reconectado!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  } else if (wifiConnected && WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
    Serial.println("WiFi desconectado");
  }
  
  // Parpadear el LED
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(BLINK_INTERVAL);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(BLINK_INTERVAL);
}

