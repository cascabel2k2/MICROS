#include <Arduino.h>
#include <WiFi.h>

// Pin del LED incorporado del ESP32 (generalmente GPIO 2)
#define LED_PIN 2

// Intervalos de tiempo en milisegundos
#define BLINK_INTERVAL 500
#define WIFI_CHECK_INTERVAL 10000  // Verificar WiFi cada 10 segundos
#define WIFI_TIMEOUT 15000         // Timeout de conexión WiFi

// Credenciales WiFi
const char* ssid = "Flia_Agreda";
const char* password = "777XonarGen";

// Variables de estado
static bool wifiConnected = false;
static bool ledState = false;
static unsigned long lastBlinkTime = 0;
static unsigned long lastWifiCheck = 0;
static unsigned long wifiStartTime = 0;

// Declaraciones de funciones
void connectToWiFi();
void handleLEDBlink();
void handleWiFiStatus();

void setup() {
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  
  // Inicializar la comunicación serie
  Serial.begin(115200);
  Serial.println("ESP32 LED Blink con WiFi iniciado");
  
  // Conectar a WiFi
  connectToWiFi();
  
  // Inicializar variables de tiempo
  lastBlinkTime = millis();
  lastWifiCheck = millis();
}

void connectToWiFi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  wifiStartTime = millis();
}

void handleWiFiStatus() {
  unsigned long currentTime = millis();
  
  // Verificar WiFi solo cada WIFI_CHECK_INTERVAL
  if (currentTime - lastWifiCheck >= WIFI_CHECK_INTERVAL) {
    lastWifiCheck = currentTime;
    
    wl_status_t wifiStatus = WiFi.status();
    
    if (wifiStatus == WL_CONNECTED && !wifiConnected) {
      wifiConnected = true;
      Serial.println("¡WiFi conectado exitosamente!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    } else if (wifiStatus != WL_CONNECTED && wifiConnected) {
      wifiConnected = false;
      Serial.println("WiFi desconectado");
    } else if (wifiStatus != WL_CONNECTED && !wifiConnected) {
      // Verificar timeout de conexión inicial
      if (currentTime - wifiStartTime >= WIFI_TIMEOUT) {
        Serial.println("Timeout WiFi - reintentando...");
        connectToWiFi();
      }
    }
  }
}

void handleLEDBlink() {
  unsigned long currentTime = millis();
  
  // Parpadear LED sin bloquear usando millis()
  if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
    lastBlinkTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    
    // Solo imprimir estado del LED ocasionalmente para reducir overhead
    static int blinkCount = 0;
    if (++blinkCount % 20 == 0) {  // Cada 20 parpadeos (10 segundos)
      Serial.print("LED: ");
      Serial.println(ledState ? "ON" : "OFF");
    }
  }
}

void loop() {
  // Manejar estado WiFi de forma no bloqueante
  handleWiFiStatus();
  
  // Manejar parpadeo LED de forma no bloqueante
  handleLEDBlink();
  
  // El loop ahora es muy eficiente - no hay delays bloqueantes
}

