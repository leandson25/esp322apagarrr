#include "communication.h"
#include "../services/services.h"
#include "json_parser.h"

// Instância global do servidor WebSocket
WebSocketsServer webSocket = WebSocketsServer(81);

// Implementação da instância global do parser JSON
JsonParser jsonParser;

void initWebSocket() {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("[WebSocket] Servidor iniciado na porta 81");
}

void updateWebSocket() {
    webSocket.loop();
}

void sendMessageToAll(const String& message) {
    webSocket.broadcastTXT(message);
    Serial.println("[WebSocket] Mensagem enviada: " + message);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[WebSocket] Cliente %u conectado de %s\n", num, ip.toString().c_str());
            break;
        }
        case WStype_DISCONNECTED:
            Serial.printf("[WebSocket] Cliente %u desconectado\n", num);
            break;

        case WStype_TEXT: {
            String msg = String((char*)payload);
            Serial.printf("[WebSocket] Mensagem recebida de %u: %s\n", num, msg.c_str());

            // Usa o parser JSON global
            jsonParser.parseMessage(msg);

            break;
        }
        default:
            break;
    }
}
