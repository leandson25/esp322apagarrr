#include "storage.h"
#include <Preferences.h>

/**
 * @brief Gerencia armazenamento persistente do ESP32 via NVS.
 */
Storage::Storage() : _initialized(false) {}

bool Storage::init() {
    // Tenta iniciar com namespace padrão
    return begin("esp322apagarrr");
}

bool Storage::begin(const char* namespaceName) {
    _initialized = _prefs.begin(namespaceName, false);
    if (!_initialized) {
        logger.error("Falha ao inicializar NVS namespace: " + String(namespaceName));
    }
    return _initialized;
}

void Storage::saveString(const String& key, const String& value) {
    if (!_initialized) {
        logger.warn("Storage não inicializado - não foi possível salvar: " + key);
        return;
    }
    _prefs.putString(key.c_str(), value);
    logger.debug("Salvo string: " + key);
}

String Storage::loadString(const String& key, const String& defaultValue) {
    if (!_initialized) {
        logger.warn("Storage não inicializado - retornando padrão para: " + key);
        return defaultValue;
    }
    return _prefs.getString(key.c_str(), defaultValue);
}

void Storage::saveInt(const String& key, int value) {
    if (!_initialized) {
        logger.warn("Storage não inicializado - não foi possível salvar: " + key);
        return;
    }
    _prefs.putInt(key.c_str(), value);
    logger.debug("Salvo int: " + key + " = " + String(value));
}

int Storage::loadInt(const String& key, int defaultValue) {
    if (!_initialized) {
        logger.warn("Storage não inicializado - retornando padrão para: " + key);
        return defaultValue;
    }
    return _prefs.getInt(key.c_str(), defaultValue);
}

void Storage::loadConfig() {
    // Carrega configurações salvas - implementação básica
    logger.info("Carregando configurações...");
}

void Storage::update() {
    // Verificação periódica se necessário
}

void Storage::end() {
    if (_initialized) {
        _prefs.end();
        _initialized = false;
    }
}
