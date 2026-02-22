/**
 * ============================================================
 * ESP32 LED CONTROL SYSTEM
 * Entry Point - main.cpp
 * ------------------------------------------------------------
 * Responsável por:
 *  - Boot do sistema
 *  - Inicialização de infraestrutura
 *  - Start dos serviços
 *  - Registro de tarefas no scheduler
 *  - Loop principal determinístico
 *
 * Arquitetura baseada em separação por camadas:
 *  Application → Services → Drivers → HAL
 * ============================================================
 */

#include <Arduino.h>

/* ===================== SYSTEM ===================== */
#include "system/system.h"
#include "system/logger.h"
#include "system/scheduler.h"
#include "system/wifi_manager.h"
#include "system/storage.h"

/* ===================== DRIVERS ===================== */
#include "drivers/led_driver.h"
#include "drivers/pwm_driver.h"

/* ===================== SERVICES ===================== */
#include "services/led_service.h"
#include "services/mode_service.h"
#include "services/message_service.h"

/* ===================== COMMUNICATION ===================== */
#include "communication/websocket_server.h"
#include "communication/json_parser.h"

/* ===================== APPLICATION ===================== */
#include "app/app.h"

/* ===================== CONFIG ===================== */
#include "config.h"
#include "pins.h"

/* ============================================================
   INSTÂNCIAS GLOBAIS (Single Ownership Model)
   ============================================================ */

Scheduler scheduler;
WifiManager wifi;
Storage storage;

LEDDriver LEDDriver;
PwmDriver pwmDriver;

LedService ledService(LEDDriver);
ModeService modeService;
MessageService messageService;

WebSocketServer wsServer;
JsonParser jsonParser;

App app;

/* ============================================================
   SETUP - Executado uma única vez no boot
   ============================================================ */
void setup()
{
    Serial.begin(115200);
    delay(500);

    Logger::init();
    Logger::info("==== SYSTEM BOOT START ====");

    /* ---------- STORAGE ---------- */
    if (!storage.init())
    {
        Logger::error("Storage initialization failed!");
    }

    /* ---------- WIFI ---------- */
    wifi.begin(WIFI_SSID, WIFI_PASSWORD);

    /* ---------- DRIVERS ---------- */
    ledDriver.init(LED_PIN, LED_COUNT);
    pwmDriver.init();

    /* ---------- SERVICES ---------- */
    ledService.begin();
    modeService.begin();
    messageService.begin();

    /* ---------- COMMUNICATION ---------- */
    wsServer.begin(WS_PORT);
    wsServer.onMessage([](const String &msg)
    {
        Command cmd;
        if (jsonParser.parse(msg, cmd))
        {
            messageService.dispatch(cmd);
        }
    });

    /* ---------- APPLICATION ---------- */
    app.begin(&ledService, &modeService);

    /* ---------- SCHEDULER TASKS ---------- */
    scheduler.addTask("LED Update", 10, []()
    {
        ledService.update();
    });

    scheduler.addTask("Mode Engine", 20, []()
    {
        modeService.update();
    });

    scheduler.addTask("WebSocket Loop", 5, []()
    {
        wsServer.loop();
    });

    scheduler.addTask("App Logic", 16, []()
    {
        app.update();
    });

    Logger::info("==== SYSTEM BOOT COMPLETE ====");
}

/* ============================================================
   LOOP PRINCIPAL
   Não contém lógica — apenas executa o scheduler.
   ============================================================ */
void loop()
{
    scheduler.run();
}
