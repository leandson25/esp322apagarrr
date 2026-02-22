#pragma once

#include "../drivers/led_driver.h"
#include "../effects/effects.h"
#include <Arduino.h>

/**
 * @brief Serviço que coordena o comportamento dos LEDs.
 */
class LEDService {
public:
    LEDService();

    // Inicializa o serviço com o driver
    void init(LEDDriver* driver, EffectsEngine* effects);

    // Liga todos os LEDs com cor especificada
    void turnOn(uint8_t r, uint8_t g, uint8_t b);

    // Desliga todos os LEDs
    void turnOff();

    // Efeitos
    void applyFade(uint8_t rStart, uint8_t gStart, uint8_t bStart,
                   uint8_t rEnd, uint8_t gEnd, uint8_t bEnd, uint16_t durationMs);
    void applyPulse(uint8_t r, uint8_t g, uint8_t b, uint16_t periodMs, uint16_t repeats);
    void applyWave(uint8_t r, uint8_t g, uint8_t b, uint16_t wavelength, uint16_t speedMs);
    void applyStrobe(uint8_t r, uint8_t g, uint8_t b, uint16_t onTimeMs, uint16_t offTimeMs, uint16_t repeats);

    // Atualiza o serviço
    void update();

private:
    LEDDriver* _driver;
    EffectsEngine* _effectsEngine;
};

// Instância global - definida em led_service.cpp
extern LEDService ledService;
