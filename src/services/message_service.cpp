#include "message_service.h"
#include "led_service.h"
#include "mode_service.h"
#include "../system/logger.h"
#include <ArduinoJson.h>

MessageService::MessageService() : _initialized(false) {}

void MessageService::init() {
    _initialized = true;
    logger.info("MessageService inicializado");
}

void MessageService::update() {
    // Aqui você pode processar mensagens da fila se necessário
}

void MessageService::processMessage(const String& message) {
    if (!_initialized) {
        logger.warn("MessageService não inicializado");
        return;
    }

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, message);
    
    if (error) {
        logger.error("Erro ao interpretar JSON: " + String(error.c_str()));
        return;
    }

    // Suporta tanto "command" (novo) quanto "type" (antigo)
    String command = doc["command"] | doc["type"] | "";

    if (command == "led" || command == "led") {
        // Comando de LED
        int r = doc["r"] | 0;
        int g = doc["g"] | 0;
        int b = doc["b"] | 0;
        
        // Verifica se é para desligar
        if (r == 0 && g == 0 && b == 0) {
            ledService.turnOff();
        } else {
            ledService.turnOn(r, g, b);
        }
    } 
    else if (command == "effect") {
        // Comando de efeito
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
        // Comando de modo
        String mode = doc["mode"] | "manual";
        
        if (mode == "manual") {
            modeService.setMode(ModeService::MANUAL);
        } else if (mode == "auto" || mode == "automatic") {
            modeService.setMode(ModeService::AUTOMATIC);
        } else if (mode == "sequential") {
            modeService.setMode(ModeService::SEQUENTIAL);
        }
    }
    else if (command == "brightness") {
        // Comando de brilho (simplificado - seria implementado no driver)
        logger.info("Comando brightness: " + String(doc["value"].as<int>()));
    }
    else {
        logger.warn("Comando desconhecido: " + command);
    }
}

// Instância global
MessageService messageService;
