#ifndef CONFIG_H
#define CONFIG_H

// ====================
// Configurações Gerais
// ====================

// Firmware
#define FIRMWARE_NAME      "ESP322Apagarrr"
#define FIRMWARE_VERSION   "1.0.0"

// Debug - ative para ver logs de debug
// Defina via platformio.ini: -DDEBUG ou descomente abaixo
// #define DEBUG

// LEDs
#define MAX_BRIGHTNESS     255
#define MIN_BRIGHTNESS     0
#define DEFAULT_BRIGHTNESS 128

#define MAX_SPEED          100
#define MIN_SPEED          1
#define DEFAULT_SPEED      50

// WebSocket e Servidor
#define WS_PORT            81
#define HTTP_PORT          80
#define WS_RECONNECT_DELAY 5000  // ms

// Intervalos de atualização
#define STATUS_UPDATE_INTERVAL 500   // ms
#define EFFECT_UPDATE_INTERVAL 30    // ms

// Misc
#define DEFAULT_MODE       "manual"

#endif // CONFIG_H
