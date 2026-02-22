#pragma once

#include <Arduino.h>

/**
 * @brief Serviço que gerencia modos de operação do sistema.
 */
class ModeService {
public:
    enum Mode {
        MANUAL,
        AUTOMATIC,
        SEQUENTIAL
    };

    ModeService();

    // Inicializa o serviço
    void init();
    
    void setMode(Mode mode);
    Mode getMode() const;
    
    // Retorna modo atual como string
    const char* getCurrentMode() const;

private:
    Mode currentMode;
};

// Instância global
extern ModeService modeService;
