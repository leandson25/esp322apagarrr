#include "app.h"
#include <cstring>

// Instâncias globais dos drivers
static LEDDriver* g_ledDriver = nullptr;
static PWMDriver* g_pwmDriver = nullptr;
static EffectsEngine* g_effectsEngine = nullptr;

// Inicialização de todos os módulos do firmware
bool App::begin() {
    logger.info("Inicializando App...");

    // Inicializa drivers
    if (!g_ledDriver) {
        g_ledDriver = new LEDDriver(150, 2); // Default: 150 LEDs, pino 2
    }
    g_ledDriver->begin();
    logger.info("LED Driver inicializado.");

    if (!g_pwmDriver) {
        g_pwmDriver = new PWMDriver();
    }
    logger.info("PWM Driver inicializado.");

    // Inicializa efeitos
    if (!g_effectsEngine) {
        g_effectsEngine = new EffectsEngine(*g_ledDriver);
    }
    g_effectsEngine->init();
    logger.info("Effects Engine inicializado.");

    // Inicializa serviços de alto nível
    ledService.init(g_ledDriver, g_effectsEngine);
    logger.info("LED Service inicializado.");
    
    modeService.init();
    logger.info("Mode Service inicializado.");
    
    messageService.init();
    logger.info("Message Service inicializado.");

    // Inicializa comunicação WebSocket
    initWebSocket();
    logger.info("WebSocket inicializado.");

    logger.info("App inicializado com sucesso!");
    return true;
}

/**
 * @brief Loop principal do firmware
 */
void App::loop() {
    // Atualiza infraestrutura
    wifiManager.update();
    scheduler.update();
    storage.update();

    // Atualiza comunicação
    handleCommunication();

    // Processa serviços de controle
    processServices();

    // Atualiza LEDs
    updateLEDs();
}

/**
 * @brief Atualiza os LEDs com os efeitos ativos
 */
void App::updateLEDs() {
    // Aplica efeitos dependendo do modo ativo
    const char* mode = modeService.getCurrentMode();
    if (mode != nullptr && strcmp(mode, "auto") == 0) {
        if (g_effectsEngine) {
            g_effectsEngine->update();
        }
    }
    ledService.update();
}

/**
 * @brief Processa a lógica de serviços de alto nível
 */
void App::processServices() {
    messageService.update();
}

/**
 * @brief Atualiza a comunicação WebSocket
 */
void App::handleCommunication() {
    updateWebSocket();
}
