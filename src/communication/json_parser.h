#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class JsonParser {
public:
    JsonParser();
    
    // Recebe e processa JSON
    void parseMessage(const String& message);
    
    // Cria JSON para enviar
    String buildMessage(const String& type, const JsonVariant& payload);

private:
    bool _initialized;
};

// Instância global do parser
extern JsonParser jsonParser;
