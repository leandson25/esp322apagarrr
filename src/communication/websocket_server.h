#pragma once
#include <Arduino.h>
#include <WebSocketsServer.h>

void initWebSocket();
void updateWebSocket();
void sendMessageToAll(const String& message);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
