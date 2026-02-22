#pragma once

#include <Arduino.h>

/**
 * @brief Serviço que processa mensagens recebidas da interface.
 */
class MessageService {
public:
    MessageService();
    
    // Inicializa o serviço
    void init();
    
    // Processa uma mensagem JSON
    void processMessage(const String& message);
    
    // Atualiza o serviço (chamado no loop)
    void update();

private:
    bool _initialized;
};

// Instância global
extern MessageService messageService;
