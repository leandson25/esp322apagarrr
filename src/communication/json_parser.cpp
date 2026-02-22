#include "json_parser.h"
#include "communication.h"
#include "../services/services.h"
#include "../system/logger.h"

JsonParser::JsonParser() : _initialized(false) {}

void JsonParser::parseMessage(const String& message) {
    if (!_initialized) {
        logger.warn("JsonParser não inicializado");
    }

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, message);

    if (error) {
        logger.error("Erro ao decodificar JSON: " + String(error.c_str()));
        return;
    }

    String command = doc["command"] | "";
    String target = doc["target"] | "";

    // Processa comandos
    if (command == "led") {
        int r = doc["r"] | 0;
        int g = doc["g"] | 0;
        int b = doc["b"] | 0;
        
        if (r == 0 && g == 0 && b == 0) {
            ledService.turnOff();
        } else {
            ledService.turnOn(r, g, b);
        }
    } 
    else if (command == "effect") {
        String effectType = doc["effect"] | "";
        
        if (effectType == "pulse") {
            ledService.applyPulse(
                doc["r"] | 255,
                doc["g"] | 0,
                doc["b"] | 0,
                doc["period"] | 1000,
                doc["repeats"] | 5
            );
        } else if (effectType == "fade") {
            ledService.applyFade(
                doc["rStart"] | 0,
                doc["gStart"] | 0,
                doc["bStart"] | 0,
                doc["rEnd"] | 255,
                doc["gEnd"] | 255,
                doc["bEnd"] | 255,
                doc["duration"] | 2000
            );
        } else if (effectType == "wave") {
            ledService.applyWave(
                doc["r"] | 255,
                doc["g"] | 0,
                doc["b"] | 0,
                doc["wavelength"] | 2.0,
                doc["speed"] | 1.0
            );
        } else if (effectType == "strobe") {
            ledService.applyStrobe(
                doc["r"] | 255,
                doc["g"] | 0,
                doc["b"] | 0,
                doc["onTime"] | 50,
                doc["offTime"] | 50,
                doc["repeats"] | 10
            );
        }
    }
    else if (command == "mode") {
        String mode = doc["mode"] | "manual";
        
        if (mode == "manual") {
            modeService.setMode(ModeService::MANUAL);
        } else if (mode == "auto" || mode == "automatic") {
            modeService.setMode(ModeService::AUTOMATIC);
        } else if (mode == "sequential") {
            modeService.setMode(ModeService::SEQUENTIAL);
        }
    }
    else {
        logger.warn("Comando desconhecido no JSON: " + command);
    }
}

String JsonParser::buildMessage(const String& type, const JsonVariant& payload) {
    StaticJsonDocument<256> doc;
    doc["type"] = type;
    doc["payload"] = payload;
    String output;
    serializeJson(doc, output);
    return output;
}

// Instância global
JsonParser jsonParser;
