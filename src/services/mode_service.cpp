#include "mode_service.h"
#include "../system/logger.h"

ModeService::ModeService() : currentMode(MANUAL) {}

void ModeService::init() {
    logger.info("ModeService inicializado");
}

void ModeService::setMode(Mode mode) {
    currentMode = mode;
    logger.info("Modo alterado para: " + String(getCurrentMode()));
}

ModeService::Mode ModeService::getMode() const {
    return currentMode;
}

const char* ModeService::getCurrentMode() const {
    switch (currentMode) {
        case MANUAL: return "manual";
        case AUTOMATIC: return "auto";
        case SEQUENTIAL: return "sequential";
        default: return "manual";
    }
}

// Instância global
ModeService modeService;
