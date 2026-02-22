#pragma once

#include <Arduino.h>
#include <vector>
#include <functional>

struct PWMChannel {
    uint8_t pin;
    uint8_t duty;      // 0-255
    uint32_t frequency;
};

class PWMDriver {
public:
    PWMDriver();
    ~PWMDriver();

    // Inicializa um canal PWM
    void addChannel(uint8_t pin, uint32_t frequency = 1000, uint8_t duty = 0);

    // Define duty cycle (0-255)
    void setDuty(uint8_t pin, uint8_t duty);

    // Faz transição suave do duty cycle
    void fadeTo(uint8_t pin, uint8_t targetDuty, uint32_t duration);

    // Atualiza todos os canais (deve ser chamado periodicamente)
    void update();

    // Para um canal
    void stop(uint8_t pin);

private:
    std::vector<PWMChannel> channels;

    struct FadeInfo {
        uint8_t pin;
        uint8_t startDuty;
        uint8_t targetDuty;
        uint32_t startTime;
        uint32_t duration;
        bool active;
    };
    std::vector<FadeInfo> fades;
};
