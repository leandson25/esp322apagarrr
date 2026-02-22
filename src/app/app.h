#pragma once

#include <Arduino.h>
#include "../drivers/led_driver.h"
#include "../drivers/pwm_driver.h"
#include "../effects/effects.h"
#include "../services/services.h"
#include "../communication/communication.h"
#include "../system/system.h"

/**
 * @brief Classe central do firmware
 * Coordena todos os módulos: drivers, efeitos, serviços e comunicação
 */
class App {
public:
    App() = default;

    // Inicializa todos os módulos
    void begin();

    // Loop principal, chamado continuamente
    void loop();

private:
    void updateLEDs();          // Atualiza LEDs com efeitos ativos
    void processServices();     // Executa lógica de serviços
    void handleCommunication(); // Atualiza comunicação WebSocket
};
