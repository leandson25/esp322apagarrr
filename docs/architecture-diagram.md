# 🏗️ Arquitetura do Projeto esp322apagarrr

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                        ESP32 Firmware Architecture                          │
└─────────────────────────────────────────────────────────────────────────────┘

                              ┌──────────────┐
                              │   main.cpp   │
                              │   (setup)   │
                              └──────┬───────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                           App Layer (app/)                                 │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                            App                                       │   │
│  │  • begin()         - Inicializa todos os módulos                  │   │
│  │  • loop()          - Loop principal                                │   │
│  │  • updateLEDs()    - Atualiza LEDs com efeitos                    │   │
│  │  • processServices()- Processa serviços de alto nível              │   │
│  │  • handleComm()    - Gerencia comunicação WebSocket                │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────────┘
                                     │
           ┌──────────────────────────┼──────────────────────────┐
           │                          │                          │
           ▼                          ▼                          ▼
┌─────────────────────┐  ┌─────────────────────┐  ┌─────────────────────┐
│   Communication     │  │     Services        │  │      Drivers        │
│   (communication/)  │  │    (services/)      │  │    (drivers/)       │
├─────────────────────┤  ├─────────────────────┤  ├─────────────────────┤
│ WebSocketServer    │  │ LEDService          │  │ LEDDriver           │
│  - initWebSocket() │  │  - turnOn/off()     │  │  - begin()          │
│  - updateWebSocket │  │  - applyFade/Pulse  │  │  - setColor()      │
│  - sendMessage()   │  │ ModeService          │  │  - update()        │
│                    │  │  - setMode()         │  │ PWMDriver           │
│ JsonParser         │  │  - getMode()         │  │  - addChannel()    │
│  - parseMessage()  │  │ MessageService       │  │  - setDuty()       │
│  - buildMessage()  │  │  - processMessage()  │  │  - fadeTo()        │
└─────────────────────┘  └─────────────────────┘  └─────────────────────┘
           │                          │                          │
           └──────────────────────────┼──────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                           Effects Layer (effects/)                         │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                        EffectsEngine                                 │   │
│  │  ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────┐              │   │
│  │  │  Fade   │  │  Pulse  │  │  Wave   │  │ Strobe  │              │   │
│  │  └─────────┘  └─────────┘  └─────────┘  └─────────┘              │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                         System Layer (system/)                             │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  ┌─────────────┐  │
│  │ WiFiManager  │  │   Logger     │  │  Scheduler   │  │  Storage    │  │
│  │ - connect()  │  │ - info()     │  │ - addTask()  │  │ - init()    │  │
│  │ - reconnect()│  │ - warn()     │  │ - update()   │  │ - saveStr() │  │
│  │ - isConn()   │  │ - error()    │  │              │  │ - loadStr() │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  └─────────────┘  │
└─────────────────────────────────────────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                              Hardware Layer                                │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  ┌─────────────┐  │
│  │   ESP32      │  │ WS2812 LEDs  │  │   PWM Out   │  │   Flash     │  │
│  │   Module     │  │   (NeoPixel) │  │   (LEDs)     │  │   Memory    │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  └─────────────┘  │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## 📡 Fluxo de Comunicação

```
┌─────────────┐     WebSocket      ┌─────────────┐
│   Browser   │ ◄────────────────► │    ESP32    │
│  (Interface)│    ws://:81        │  (Firmware) │
└──────┬──────┘                    └──────┬──────┘
       │                                     │
       │ JSON: {"command": "led",           │
       │        "r": 255, "g": 0, "b": 0}  │
       │                                     │
       ▼                                     ▼
┌──────────────┐                    ┌─────────────────┐
│  WebSocket   │ ───────────────►  │  JsonParser     │
│  Client      │                    │  parseMessage() │
└──────────────┘                    └────────┬────────┘
                                             │
                                             ▼
                                    ┌─────────────────┐
                                    │   LEDService    │
                                    │   turnOn()      │
                                    └────────┬────────┘
                                             │
                                             ▼
                                    ┌─────────────────┐
                                    │   LEDDriver     │
                                    │   setColor()    │
                                    └────────┬────────┘
                                             │
                                             ▼
                                    ┌─────────────────┐
                                    │  Adafruit_      │
                                    │  NeoPixel       │
                                    │  show()         │
                                    └─────────────────┘
```

---

## 🗂️ Estrutura de Diretórios

```
esp322apagarrr/
├── 📄 platformio.ini              # Configuração do projeto
├── 📄 README.md                    # Documentação principal
│
├── 📁 include/                    # Headers globais
│   ├── config.h                   # Configurações do sistema
│   ├── pins.h                     # Mapeamento de pinos
│   └── protocol.h                 # Definições de protocolo
│
├── 📁 src/                        # Código fonte do firmware
│   ├── main.cpp                   # Entry point
│   │
│   ├── 📁 app/                    # Camada de aplicação
│   │   ├── app.h
│   │   └── app.cpp
│   │
│   ├── 📁 drivers/                # Drivers de hardware
│   │   ├── led_driver.h/cpp       # Driver de LEDs NeoPixel
│   │   └── pwm_driver.h/cpp       # Driver PWM
│   │
│   ├── 📁 effects/                # Motor de efeitos
│   │   ├── effects.h
│   │   ├── fade.cpp
│   │   ├── pulse.cpp
│   │   ├── wave.cpp
│   │   └── strobe.cpp
│   │
│   ├── 📁 services/              # Serviços de alto nível
│   │   ├── services.h
│   │   ├── led_service.cpp
│   │   ├── mode_service.cpp
│   │   └── message_service.cpp
│   │
│   ├── 📁 communication/         # Comunicação
│   │   ├── communication.h/cpp
│   │   ├── websocket_server.h/cpp
│   │   └── json_parser.h/cpp
│   │
│   └── 📁 system/                # Sistema/Infraestrutura
│       ├── system.h
│       ├── logger.h/cpp
│       ├── scheduler.h/cpp
│       ├── storage.h/cpp
│       └── wifi_manager.h/cpp
│
├── 📁 interface/                  # Interface web (PC)
│   ├── index.html
│   ├── 📁 assets/
│   │   ├── 📁 css/               # Estilos
│   │   ├── 📁 js/                # Módulos JS
│   │   │   ├── api.js
│   │   │   ├── dashboard.js
│   │   │   ├── led_control.js
│   │   │   ├── websocket.js
│   │   │   └── ui_manager.js
│   │   └── 📁 fonts/
│   │   ├── 📁 components/        # Componentes
│   │   │   ├── slider.js
│   │   │   ├── toggle.js
│   │   │   └── ...
│   │   └── 📁 config/
│   │       └── settings.js
│
├── 📁 data/                       # Interface embarcada (SPIFFS)
│   ├── index.html
│   ├── app.js
│   └── style.css
│
├── 📁 docs/                      # Documentação
│   ├── architecture.md
│   ├── protocol.md
│   ├── wiring.md
│   └── roadmap.md
│
└── 📁 tools/                     # Scripts auxiliares
    ├── build.ps1
    ├── clean.ps1
    ├── monitor.ps1
    └── upload_fs.ps1
```

---

## 🔄 Ciclo de Vida

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              Boot Sequence                                  │
└─────────────────────────────────────────────────────────────────────────────┘

  ┌─────────────┐
  │   Power     │
  │   On        │
  └──────┬──────┘
         │
         ▼
  ┌─────────────┐
  │  setup()    │ ◄── Serial.begin(115200)
  └──────┬──────┘      logger.init()
         │             storage.init()
         │             storage.loadConfig()
         │             scheduler.init()
         ▼             espApp.begin()
  ┌─────────────┐
  │ App::begin()│ ◄── wifiManager.initWiFi()
  └──────┬──────┘      ledDriver.begin()
         │             pwmDriver.begin()
         │             effectsEngine.init()
         ▼             ledService.init()
  ┌─────────────┐      initWebSocket()
  │  ready!    │
  └──────┬──────┘
         │
         ▼ Loop forever
  ┌─────────────┐
  │   loop()    │ ◄── espApp.loop()
  └──────┬──────┘      scheduler.update()
         │             delay(0)  // yield to WiFi
         ▼
  ┌─────────────┐
  │  App Loop  │
  └─────────────┘
    │
    ├── wifiManager.update()
    ├── scheduler.update()
    ├── storage.update()
    ├── updateWebSocket()
    ├── processServices()
    │    ├── modeService.update()
    │    └── messageService.update()
    └── updateLEDs()
         ├── effectsEngine.update()
         └── ledService.update()
```

---

## 📋 Protocolo de Comunicação

### Comandos (Interface → ESP32)

```json
// Ligar LEDs
{"command": "led", "r": 255, "g": 0, "b": 0}

// Definir modo
{"command": "mode", "mode": "manual"}
{"command": "mode", "mode": "automatic"}

// Efeitos
{"command": "effect", "effect": "pulse", "r": 255, "g": 0, "b": 0, "period": 1000}
{"command": "effect", "effect": "fade", "rStart": 0, "gStart": 0, "bStart": 0, "rEnd": 255, "gEnd": 255, "bEnd": 255, "duration": 2000}
{"command": "effect", "effect": "wave", "r": 255, "g": 0, "b": 0, "wavelength": 2.0, "speed": 1.0}
{"command": "effect", "effect": "strobe", "r": 255, "g": 0, "b": 0, "onTime": 50, "offTime": 50, "repeats": 10}

// Brilho
{"command": "brightness", "value": 128}
```

### Respostas (ESP32 → Interface)

```json
// Status
{"type": "status", "ledState": "on", "mode": "manual", "brightness": 128}

// Erro
{"type": "error", "message": "Invalid command"}
```

---

## 🧩 Dependências do Sistema

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           Dependencies Tree                                  │
└─────────────────────────────────────────────────────────────────────────────┘

├── Adafruit NeoPixel          # Controle de LEDs WS2812
├── WebSocketsServer          # Servidor WebSocket
├── ArduinoJson               # Parse/Serialização JSON
├── Preferences               # Armazenamento NVS
└── WiFi (ESP32 Core)        # Conexão WiFi
```

---

## ⚡ Requisitos de Hardware

- **MCU**: ESP32 (qualquer variant)
- **Flash**: 4MB mínimo
- **LEDs**: WS2812B (NeoPixel) - até 150 LEDs testados
- **Pinos**:
  - GPIO 2: Data dos LEDs
  - GPIO 25-27: PWM RGB (opcional)
  - GPIO 14/12: Botões (opcional)
