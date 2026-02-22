#pragma once

#include "../drivers/led_driver.h"
#include <vector>
#include <functional>

class EffectsEngine {
public:
    EffectsEngine(LEDDriver& driver);

    // Inicializa o motor de efeitos
    void init();
    
    // Atualiza todos os efeitos ativos
    void update();

    // Aplicar efeitos individuais
    void fade(uint16_t start = 0, uint16_t end = 0, uint32_t speed = 50);
    void pulse(uint16_t start = 0, uint16_t end = 0, uint32_t period = 1000);
    void wave(uint16_t start = 0, uint16_t end = 0, float wavelength = 2.0, float speed = 1.0);
    void strobe(uint16_t start = 0, uint16_t end = 0, uint32_t interval = 100);

    // Permite efeitos customizados
    void custom(std::function<void(RGB&, uint32_t)> effectFunc);

    // Limpa efeitos e LEDs
    void clear();

private:
    LEDDriver& ledDriver;
    std::vector<std::function<void(uint16_t start, uint16_t end)>> activeEffects;
    uint32_t lastUpdate;
    bool _initialized;
};
