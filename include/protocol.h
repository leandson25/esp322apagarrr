#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <Arduino.h>
#include <ArduinoJson.h>

// Tipos de mensagem
enum MessageType {
    MSG_STATUS,
    MSG_EFFECT,
    MSG_CONTROL,
    MSG_ERROR
};

// Estrutura de mensagem JSON para enviar/receber
struct Message {
    MessageType type;
    String key;
    String value;
    bool valid;  // Indica se a mensagem é válida
};

// Função utilitária para criar JSON
inline String createJSON(MessageType type, const String& key, const String& value) {
    StaticJsonDocument<256> doc;
    doc["type"] = (int)type;
    doc["key"] = key;
    doc["value"] = value;
    String output;
    serializeJson(doc, output);
    return output;
}

// Parse de JSON recebido com verificação de erro
inline Message parseJSON(const String& jsonStr) {
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, jsonStr);
    
    Message msg;
    msg.valid = false;
    
    if (error) {
        Serial.printf("Erro ao fazer parse do JSON: %s\n", error.c_str());
        return msg;
    }
    
    // Verifica se os campos existem
    if (!doc.containsKey("type") || !doc.containsKey("key") || !doc.containsKey("value")) {
        Serial.println("JSON inválido: campos obrigatórios ausentes");
        return msg;
    }
    
    msg.type = (MessageType)doc["type"].as<int>();
    msg.key = doc["key"].as<String>();
    msg.value = doc["value"].as<String>();
    msg.valid = true;
    
    return msg;
}

#endif // PROTOCOL_H
