#pragma once

#include <Arduino.h>
#include <vector>
#include <functional>
#include <memory>

// Estrutura RGB com canal alfa opcional (usado como fator de brilho)
struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // alpha / brilho opcional
};

// Tipos de efeitos de LED
enum class LEDEffectType {
    NONE,
    FADE,
    PULSE,
    WAVE,
    STROBE
};

// Forward declaration para evitar dependência direta no header
class Adafruit_NeoPixel;

// Classe principal do LED Driver
class LEDDriver {
public:
    // Construtor: recebe número de LEDs e pino de dados
    LEDDriver(uint16_t numLEDs, uint8_t dataPin);
    
    // Destrutor - unique_ptr já cuida da memória
    ~LEDDriver();

    // Move semantics
    LEDDriver(LEDDriver&& other) noexcept;
    LEDDriver& operator=(LEDDriver&& other) noexcept;

    // Inicialização do driver
    void begin();

    // Configuração de brilho global
    void setGlobalBrightness(uint8_t brightness);

    // Configuração de cor de um LED específico
    void setColor(uint16_t index, const RGB& color);

    // Atualiza todos os LEDs com base no buffer interno
    void update();

    // Aplica um efeito em um intervalo de LEDs
    void applyEffect(LEDEffectType effect, uint16_t start = 0, uint16_t end = 0);

    // Define efeito customizado via callback
    void setCustomEffect(std::function<void(RGB&, uint32_t)> callback);

    // Limpa LEDs
    void clear();

    // Retorna número de LEDs
    uint16_t count() const;

    // Verifica se está inicializado
    bool isInitialized() const { return _strip != nullptr; }

private:
    uint16_t numLEDs;
    uint8_t dataPin;
    uint8_t globalBrightness;

    std::vector<RGB> ledBuffer;                  // Buffer interno de LEDs
    LEDEffectType currentEffect;
    std::function<void(RGB&, uint32_t)> customEffect;

    // Gerenciamento automático de memória
    std::unique_ptr<Adafruit_NeoPixel> _strip;

    // Métodos internos para efeitos
    void applyFade(uint16_t start, uint16_t end);
    void applyPulse(uint16_t start, uint16_t end);
    void applyWave(uint16_t start, uint16_t end);
    void applyStrobe(uint16_t start, uint16_t end);

    // Temporização interna
    uint32_t lastUpdate;

    // Intervalo de LEDs para aplicar efeito
    uint16_t effectStart;
    uint16_t effectEnd;

    // Proibir cópia
    LEDDriver(const LEDDriver&) = delete;
    LEDDriver& operator=(const LEDDriver&) = delete;
};
