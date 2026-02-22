#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h> 
#include <WebSocketsServer.h>
#include "../services/services.h"


// Forward declarations
class JsonParser;

// Funções do servidor WebSocket
void initWebSocket();
void updateWebSocket();
void sendMessageToAll(const String& message);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

// Instância global do parser JSON
extern JsonParser jsonParser;
