#include "logger.h"

/**
 * @brief Inicializa o logger
 */
void Logger::init() {
    // Serial já deve estar inicializado em setup() antes de chamar logger.init()
}

/**
 * @brief Registra logs do sistema, erros e informações de debug.
 */
void Logger::info(const String& msg) {
    Serial.printf("[INFO] %s\n", msg.c_str());
}

void Logger::warn(const String& msg) {
    Serial.printf("[WARN] %s\n", msg.c_str());
}

void Logger::error(const String& msg) {
    Serial.printf("[ERROR] %s\n", msg.c_str());
}

void Logger::debug(const String& msg) {
#ifdef DEBUG
    Serial.printf("[DEBUG] %s\n", msg.c_str());
#endif
}
