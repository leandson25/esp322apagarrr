#include "wifi_manager.h"
#include <WiFi.h>

/**
 * @brief Gerencia a conexão Wi-Fi do ESP32, incluindo reconexão automática.
 */
WiFiManagerCustom::WiFiManagerCustom() : _connected(false) {}

void WiFiManagerCustom::initWiFi() {
    // Configurações padrão - podem ser sobrescritas por storage
    // Por padrão, tenta conectar a uma rede configurada
    // Você pode modificar esta lógica conforme necessidade
    logger.info("WiFi inicializado - modo Station");
}

void WiFiManagerCustom::connect(const char* ssid, const char* password) {
    logger.info("Conectando a rede: " + String(ssid));
    WiFi.begin(ssid, password);
    
    uint8_t attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        _connected = true;
        logger.info("Wi-Fi conectado! IP: " + WiFi.localIP().toString());
    } else {
        _connected = false;
        logger.error("Falha na conexão Wi-Fi após " + String(attempts) + " tentativas");
    }
}

bool WiFiManagerCustom::isConnected() {
    if (WiFi.status() != WL_CONNECTED) {
        _connected = false;
    }
    return _connected;
}

void WiFiManagerCustom::update() {
    // Verifica conexão periodicamente
    if (!_connected && WiFi.status() == WL_CONNECTED) {
        _connected = true;
        logger.info("Wi-Fi reconectado! IP: " + WiFi.localIP().toString());
    }
}

void WiFiManagerCustom::reconnect() {
    if (!isConnected()) {
        logger.warn("Tentando reconectar Wi-Fi...");
        WiFi.reconnect();
        delay(1000);
    }
}
