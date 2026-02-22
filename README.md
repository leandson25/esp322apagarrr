# 🌟 ESP322Apagarrr

Firmware ESP32 para controle avançado de LEDs com interface web embarcada e comunicação WebSocket em tempo real.

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-blue)](https://platformio.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

## 📱 Visão Geral

O **esp322apagarrr** é um firmware completo para ESP32 que permite:

- ✅ Controle de LEDs WS2812B (NeoPixel) via WebSocket
- ✅ Interface web embarcada (acesse pelo navegador)
- ✅ Múltiplos efeitos visuais (Fade, Pulse, Wave, Strobe)
- ✅ Modos de operação (Manual, Automático, Sequencial)
- ✅ Armazenamento persistente de configurações
- ✅ Reconexão automática Wi-Fi
- ✅ Arquitetura modular e expansível

## 🖥️ Interfaces Disponíveis

| Interface | Descrição | Acesso |
|-----------|-----------|--------|
| **Embarcada** | Interface no ESP32 | `http://<IP_DO_ESP>` |
| **PC** | Interface web local | Via `interface/` |

## 🚀 Quick Start

### Pré-requisitos

- [PlatformIO Core](https://platformio.org/install/cli) instalado
- ESP32 conectado via USB

### Compilar e Enviar

```bash
# Compilar firmware
pio run

# Enviar firmware + sistema de arquivos
pio run --target upload
pio run --target uploadfs
```

### Usando Scripts PowerShell

```powershell
# Compilar
.\tools\build.ps1

# Upload
.\tools\upload_fs.ps1

# Monitor serial
.\tools\monitor.ps1
```

## 🎮 Como Usar

### 1. Conecte ao Wi-Fi do ESP32

O ESP32 cria um ponto de acesso Wi-Fi ou conecta à sua rede.

### 2. Acesse a Interface

No navegador, vá para:
```
http://192.168.4.1:80
```

### 3. Controle os LEDs

- **Ligar/Desligar**: Clique nos botões
- **Cores**: Use o seletor de cores
- **Brilho**: Ajuste o slider
- **Efeitos**: Selecione Fade, Pulse, Wave ou Strobe

## 📡 Protocolo de Comunicação

### Comandos JSON

```json
// Ligar LEDs
{"command": "led", "r": 255, "g": 0, "b": 0}

// Definir modo
{"command": "mode", "mode": "manual"}

// Efeito pulse
{"command": "effect", "effect": "pulse", "r": 255, "g": 0, "b": 0, "period": 1000}

// Brilho
{"command": "brightness", "value": 128}
```

## 📂 Estrutura do Projeto

```
## 🗂️ Estrutura de Diretórios


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

Consulte [docs/architecture-diagram.md](docs/architecture-diagram.md) para diagramas detalhados.

## 🔧 Configuração

### Pinos (include/pins.h)

```cpp
#define LED_PIN_DATA    2     // Data dos LEDs NeoPixel
#define LED_PIN_R       25    // PWM Red (opcional)
#define LED_PIN_G       26    // PWM Green (opcional)
#define LED_PIN_B       27    // PWM Blue (opcional)
```

### Configurações (include/config.h)

```cpp
#define WS_PORT            81   // Porta WebSocket
#define DEFAULT_BRIGHTNESS 128 // Brilho padrão
#define DEFAULT_MODE       "manual"
```

## 🧩 Bibliotecas

- **Adafruit NeoPixel** - Controle de LEDs WS2812
- **WebSocketsServer** - Servidor WebSocket
- **ArduinoJson** - Parse/Serialização JSON
- **Preferences** - Armazenamento NVS

## 📖 Documentação

- [Arquitetura do Sistema](docs/architecture-diagram.md)
- [Protocolo de Comunicação](docs/protocol.md)
- [Esquema de Ligação](docs/wiring.md)
- [Roadmap](docs/roadmap.md)

## 🐛 Problemas Conhecidos

1. **LEDs não respondem**: Verifique a conexão Data no pino correto
2. **WebSocket não conecta**: Confirme que o ESP32 está na mesma rede
3. **Upload falha**: Verifique a porta USB e drivers CH340/CP2102

## 🤝 Contribuindo

1. Fork o projeto
2. Crie uma branch (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -am 'Adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Crie um Pull Request

## 📝 Licença

MIT License - consulte [LICENSE](LICENSE) para detalhes.

---

Feito com ❤️ para a comunidade ESP32





_______________________________________________________________________________________________




Explicação Geral do Projeto esp322apagarrr

O projeto esp322apagarrr é um firmware completo para o microcontrolador ESP32, desenvolvido para controle avançado de LEDs e efeitos visuais, com suporte a comunicação em tempo real por uma interface web embarcada. Ele foi projetado com arquitetura modular, permitindo fácil manutenção, escalabilidade e integração com novas funcionalidades ou hardware adicional.

O sistema é estruturado para lidar com três camadas principais: hardware, lógica de controle e interface com o usuário, garantindo que cada parte do projeto seja independente e expansível.

______________________________________________________________________________________________


Explicação de cada modulo do projeto


📖 Explicação dos Módulos do Projeto esp322apagarrr

1. Arquivos de Configuração
platformio.ini

Arquivo de configuração do PlatformIO, definindo parâmetros do projeto, como a placa ESP32 utilizada, framework, bibliotecas externas e opções de compilação. É o ponto central para o ambiente de desenvolvimento do firmware.

2. Diretório include/ – Cabeçalhos Globais

config.h
Contém definições globais do sistema, como constantes de tempo, valores padrão e parâmetros de inicialização. Centraliza configurações que podem ser ajustadas sem alterar o código principal.

pins.h
Mapeia os pinos do ESP32 para funcionalidades específicas, como LEDs, PWM, botões ou sensores. Facilita mudanças de hardware sem precisar modificar o código em múltiplos arquivos.

protocol.h
Define a estrutura das mensagens enviadas e recebidas pelo sistema, garantindo que todos os módulos utilizem o mesmo padrão de comunicação.

3. Diretório src/ – Código-Fonte do Firmware
main.cpp

Arquivo de inicialização do firmware. Aqui ocorre a configuração inicial do sistema, inicialização de drivers, serviços e agendamento de tarefas.

3.1. app/ – Núcleo do Sistema

app.h / app.cpp
Contém a lógica principal do software, atuando como orquestrador entre drivers, efeitos, serviços e comunicação. Define o fluxo de operação do firmware e a integração de todos os módulos.

3.2. drivers/ – Interface com Hardware

led_driver.h / led_driver.cpp
Gerencia o controle direto de LEDs, incluindo ligar, desligar, atualizar brilho e cores. Interage diretamente com o hardware.

pwm_driver.h / pwm_driver.cpp
Responsável por controlar saídas PWM (Pulse Width Modulation) para efeitos de intensidade e modulação de sinais nos LEDs ou outros periféricos.

3.3. effects/ – Motor de Efeitos Visuais

fade.cpp – Implementa efeitos de transição suave entre cores ou intensidades.

pulse.cpp – Cria pulsos rítmicos de luz.

wave.cpp – Gera efeitos ondulatórios de brilho e cor.

strobe.cpp – Produz flashes rápidos ou estroboscópicos.

effects.h – Cabeçalho que unifica os efeitos, permitindo que outros módulos chamem qualquer efeito de forma padronizada.

3.4. services/ – Lógica de Alto Nível

led_service.cpp – Coordena o comportamento geral dos LEDs, aplicando efeitos e respondendo a comandos do usuário.

mode_service.cpp – Gerencia modos de operação do sistema, como automático, manual ou sequencial.

message_service.cpp – Processa mensagens recebidas da interface, garantindo interpretação correta e acionamento dos serviços adequados.

services.h – Cabeçalho unificador para exportar todas as funções de serviço para outros módulos.

3.5. communication/ – Comunicação com Interface

websocket_server.cpp – Implementa servidor WebSocket no ESP32, permitindo comunicação em tempo real com a interface web.

json_parser.cpp – Converte mensagens JSON em comandos compreensíveis pelo firmware e vice-versa.

communication.h – Centraliza funções de comunicação para todos os módulos que precisam enviar ou receber dados.

3.6. system/ – Infraestrutura

wifi_manager.cpp – Gerencia a conexão Wi-Fi do ESP32, incluindo reconexão automática e configuração de rede.

logger.cpp – Registra eventos do sistema, erros e informações de debug.

scheduler.cpp – Agenda tarefas periódicas e temporizações do firmware.

storage.cpp – Gerencia armazenamento persistente, como salvar configurações ou estados.

system.h – Cabeçalho que unifica todos os serviços de infraestrutura.

4. Diretório data/ – Interface Web Embarcada

index.html – Página principal da interface web embarcada.

app.js – Contém scripts que controlam interações e comunicação com o ESP32.

style.css – Define o estilo visual da interface.

assets/ – Recursos auxiliares como CSS, JS e fontes adicionais.

5. Diretório interface/ – Versão Web Opcional (PC)

Permite rodar uma versão da interface web diretamente no computador, útil para simulações ou testes sem o hardware conectado.

index.html – Página principal da versão web PC.

assets/ – Recursos como imagens, scripts e estilos.

components/ – Componentes reutilizáveis da interface.

config/ – Configurações específicas da versão PC.

6. Diretório test/ – Testes Automatizados

test_main.cpp – Contém testes unitários e de integração do firmware, garantindo que os módulos funcionem corretamente antes do deploy.

7. Diretório docs/ – Documentação

architecture.md – Descreve a arquitetura do firmware, fluxo de dados e hierarquia de módulos.

wiring.md – Esquemas de ligação de hardware, mapeamento de pinos e conexões.

protocol.md – Define os protocolos de comunicação utilizados entre ESP32 e interface.

8. Diretório tools/ – Scripts Auxiliares

upload_fs.ps1 – Script para enviar arquivos do sistema de arquivos (SPIFFS/LittleFS) para o ESP32.

monitor.ps1 – Script para monitorar logs do ESP32 via terminal.

build.ps1 – Automatiza compilação e upload do firmware.
