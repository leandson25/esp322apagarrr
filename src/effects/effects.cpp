#include "effects.h"
#include <Arduino.h>
#include <math.h>

EffectsEngine::EffectsEngine(LEDDriver& driver)
    : ledDriver(driver), lastUpdate(0), _initialized(false) {}

void EffectsEngine::init() {
    _initialized = true;
    lastUpdate = millis();
}

void EffectsEngine::update() {
    if (!_initialized) return;
    // Os efeitos são atualizados através do LEDDriver
    // Esta função pode ser expandida para gerenciar múltiplos efeitos ativos
}

void EffectsEngine::fade(uint16_t start, uint16_t end, uint32_t speed) {
    if (!_initialized) return;
    
    uint32_t now = millis();
    if (now - lastUpdate < speed) return;

    uint16_t ledCount = ledDriver.count();
    if (start >= ledCount) start = 0;
    if (end >= ledCount || end == 0) end = ledCount > 0 ? ledCount - 1 : 0;

    for (uint16_t i = start; i <= end; ++i) {
        RGB color = {
            uint8_t((i + now / 100) % 256),
            uint8_t((i * 2 + now / 150) % 256),
            uint8_t((i * 3 + now / 200) % 256),
            255
        };
        ledDriver.setColor(i, color);
    }

    lastUpdate = now;
}

void EffectsEngine::pulse(uint16_t start, uint16_t end, uint32_t period) {
    if (!_initialized) return;
    
    uint32_t now = millis();
    float factor = (sin(2 * PI * now / period) + 1.0) / 2.0;

    uint16_t ledCount = ledDriver.count();
    if (start >= ledCount) start = 0;
    if (end >= ledCount || end == 0) end = ledCount > 0 ? ledCount - 1 : 0;

    uint8_t brightness = uint8_t(factor * 255);
    for (uint16_t i = start; i <= end; ++i) {
        RGB color = {brightness, brightness, brightness, 255};
        ledDriver.setColor(i, color);
    }
}

void EffectsEngine::wave(uint16_t start, uint16_t end, float wavelength, float speed) {
    if (!_initialized) return;
    
    uint32_t now = millis();

    uint16_t ledCount = ledDriver.count();
    if (start >= ledCount) start = 0;
    if (end >= ledCount || end == 0) end = ledCount > 0 ? ledCount - 1 : 0;

    for (uint16_t i = start; i <= end; ++i) {
        RGB color = {
            uint8_t((sin((i / wavelength) + now * speed / 1000.0) + 1.0) * 127),
            uint8_t((sin((i / wavelength) + now * speed / 1200.0) + 1.0) * 127),
            uint8_t((sin((i / wavelength) + now * speed / 1400.0) + 1.0) * 127),
            255
        };
        ledDriver.setColor(i, color);
    }
}

void EffectsEngine::strobe(uint16_t start, uint16_t end, uint32_t interval) {
    if (!_initialized) return;
    
    uint32_t now = millis();
    bool on = (now / interval) % 2;

    uint16_t ledCount = ledDriver.count();
    if (start >= ledCount) start = 0;
    if (end >= ledCount || end == 0) end = ledCount > 0 ? ledCount - 1 : 0;

    uint8_t brightness = on ? 255 : 0;
    for (uint16_t i = start; i <= end; ++i) {
        RGB color = {brightness, brightness, brightness, 255};
        ledDriver.setColor(i, color);
    }
}

void EffectsEngine::custom(std::function<void(RGB&, uint32_t)> effectFunc) {
    if (!_initialized) return;
    
    uint32_t now = millis();
    uint16_t ledCount = ledDriver.count();
    
    for (uint16_t i = 0; i < ledCount; ++i) {
        RGB color = {0, 0, 0, 255};
        effectFunc(color, now);
        ledDriver.setColor(i, color);
    }
}

void EffectsEngine::clear() {
    ledDriver.clear();
    activeEffects.clear();
}
