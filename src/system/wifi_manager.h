#pragma once
#include <Arduino.h>

class WiFiManagerCustom {
public:
    WiFiManagerCustom();

    // Inicializa WiFi com configurações padrão
    void initWiFi();
    
    // Conecta a uma rede WiFi
    void connect(const char* ssid, const char* password);
    
    // Tenta reconectar
    void reconnect();
    
    // Verifica se está conectado
    bool isConnected();
    
    // Atualiza o manager (chamado no loop)
    void update();

private:
    bool _connected;
};
