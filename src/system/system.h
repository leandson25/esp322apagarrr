#pragma once
#include "wifi_manager.h"
#include "logger.h"
#include "scheduler.h"
#include "storage.h"

// Instâncias globais para fácil acesso em outros módulos
extern WiFiManagerCustom wifiManager;
extern Logger logger;
extern Scheduler scheduler;
extern Storage storage;
