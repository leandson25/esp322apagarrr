#include "websocket_server.h"
#include "../system/logger.h"
#include "json_parser.h"
#include <WiFi.h>

WebSocketsServer wsServer(81);

/**
 * @brief Inicializa o servidor WebSocket
 */
void initWebSocket() {
    wsServer.begin();
    wsServer.onEvent(webSocketEvent);
    logger.info("Servidor WebSocket iniciado na porta 81");
}

/**
 * @brief Atualiza o servidor WebSocket (deve ser chamado no loop)
 */
void updateWebSocket() {
    wsServer.loop();
}

/**
 * @brief Callback de eventos do WebSocket
 */
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_CONNECTED: {
            IPAddress ip = wsServer.remoteIP(num);
            logger.info("Cliente conectado: " + ip.toString());
            break;
        }
        case WStype_DISCONNECTED:
            logger.info("Cliente desconectado");
            break;
        case WStype_TEXT: {
            String message = String((char*)payload);
            logger.debug("Mensagem recebida: " + message);
            jsonParser.parseMessage(message);  // Processa JSON
            break;
        }
        default:
            break;
    }
}

/**
 * @brief Envia mensagem para todos os clientes conectados
 */
void sendMessageToAll(const String& message) {
    wsServer.broadcastTXT(message);
}
