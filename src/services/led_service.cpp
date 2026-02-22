#include "led_service.h"
#include "../system/logger.h"

/**
 * @brief Serviço que coordena o comportamento dos LEDs.
 */
LEDService::LEDService() : _driver(nullptr), _effectsEngine(nullptr) {}

// Inicializa o serviço com o driver
void LEDService::init(LEDDriver* driver, EffectsEngine* effects) {
    _driver = driver;
    _effectsEngine = effects;
}

// Liga todos os LEDs com cor especificada
void LEDService::turnOn(uint8_t r, uint8_t g, uint8_t b) {
    if (!_driver) {
        logger.error("LEDService::turnOn - Driver não inicializado");
        return;
    }
    for (uint16_t i = 0; i < _driver->count(); i++) {
        _driver->setColor(i, {r, g, b, 255});
    }
    _driver->update();
}

// Desliga todos os LEDs
void LEDService::turnOff() {
    if (!_driver) {
        logger.error("LEDService::turnOff - Driver não inicializado");
        return;
    }
    _driver->clear();
}

// Aplica efeito de fade
void LEDService::applyFade(uint8_t rStart, uint8_t gStart, uint8_t bStart,
                           uint8_t rEnd, uint8_t gEnd, uint8_t bEnd, uint16_t durationMs) {
    if (!_driver || !_effectsEngine) {
        logger.error("LEDService::applyFade - Componentes não inicializados");
        return;
    }
    _effectsEngine->fade();
    _driver->applyEffect(LEDEffectType::FADE);
}

// Aplica efeito pulse
void LEDService::applyPulse(uint8_t r, uint8_t g, uint8_t b, uint16_t periodMs, uint16_t repeats) {
    if (!_driver || !_effectsEngine) {
        logger.error("LEDService::applyPulse - Componentes não inicializados");
        return;
    }
    _driver->applyEffect(LEDEffectType::PULSE);
}

// Aplica efeito wave
void LEDService::applyWave(uint8_t r, uint8_t g, uint8_t b, uint16_t wavelength, uint16_t speedMs) {
    if (!_driver || !_effectsEngine) {
        logger.error("LEDService::applyWave - Componentes não inicializados");
        return;
    }
    _driver->applyEffect(LEDEffectType::WAVE);
}

// Aplica efeito strobe
void LEDService::applyStrobe(uint8_t r, uint8_t g, uint8_t b, uint16_t onTimeMs, uint16_t offTimeMs, uint16_t repeats) {
    if (!_driver || !_effectsEngine) {
        logger.error("LEDService::applyStrobe - Componentes não inicializados");
        return;
    }
    _driver->applyEffect(LEDEffectType::STROBE);
}

// Atualiza o serviço
void LEDService::update() {
    if (_driver) _driver->update();
}

// Instância global
LEDService ledService;
