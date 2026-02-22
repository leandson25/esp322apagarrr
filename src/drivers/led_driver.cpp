#include "led_driver.h"
#include <Adafruit_NeoPixel.h>
#include <cmath> // para sin()

LEDDriver::LEDDriver(uint16_t numLEDs, uint8_t dataPin)
    : numLEDs(numLEDs), dataPin(dataPin), globalBrightness(255), 
      currentEffect(LEDEffectType::NONE), lastUpdate(0),
      effectStart(0), effectEnd(numLEDs - 1) {
    ledBuffer.resize(numLEDs, {0, 0, 0, 255});
}

LEDDriver::~LEDDriver() = default; // unique_ptr já cuida da memória

// Move constructor
LEDDriver::LEDDriver(LEDDriver&& other) noexcept
    : numLEDs(other.numLEDs),
      dataPin(other.dataPin),
      globalBrightness(other.globalBrightness),
      ledBuffer(std::move(other.ledBuffer)),
      currentEffect(other.currentEffect),
      customEffect(std::move(other.customEffect)),
      _strip(std::move(other._strip)),
      lastUpdate(other.lastUpdate),
      effectStart(other.effectStart),
      effectEnd(other.effectEnd) {
}

// Move assignment
LEDDriver& LEDDriver::operator=(LEDDriver&& other) noexcept {
    if (this != &other) {
        numLEDs = other.numLEDs;
        dataPin = other.dataPin;
        globalBrightness = other.globalBrightness;
        ledBuffer = std::move(other.ledBuffer);
        currentEffect = other.currentEffect;
        customEffect = std::move(other.customEffect);
        _strip = std::move(other._strip);
        lastUpdate = other.lastUpdate;
        effectStart = other.effectStart;
        effectEnd = other.effectEnd;
    }
    return *this;
}

void LEDDriver::begin() {
    _strip = std::make_unique<Adafruit_NeoPixel>(numLEDs, dataPin, NEO_GRB + NEO_KHZ800);
    _strip->begin();
    _strip->show(); // Inicializa LEDs apagados
}

void LEDDriver::setGlobalBrightness(uint8_t brightness) {
    globalBrightness = brightness;
}

void LEDDriver::setColor(uint16_t index, const RGB& color) {
    if (index >= numLEDs) return;
    ledBuffer[index] = color;
}

void LEDDriver::update() {
    if (!_strip) {
        Serial.println("LEDDriver::update - Strip não inicializado");
        return;
    }
    
    uint32_t now = millis();

    // Atualiza efeito automaticamente
    switch (currentEffect) {
        case LEDEffectType::FADE:   applyFade(effectStart, effectEnd); break;
        case LEDEffectType::PULSE:  applyPulse(effectStart, effectEnd); break;
        case LEDEffectType::WAVE:   applyWave(effectStart, effectEnd); break;
        case LEDEffectType::STROBE: applyStrobe(effectStart, effectEnd); break;
        default: break;
    }

    // Aplica efeito customizado, se existir
    if (customEffect) {
        for (uint16_t i = effectStart; i <= effectEnd; ++i) {
            customEffect(ledBuffer[i], now);
        }
    }

    // Atualiza LEDs físicos
    for (uint16_t i = 0; i < numLEDs; ++i) {
        RGB c = ledBuffer[i];
        uint8_t r = (c.r * globalBrightness / 255) * (c.a / 255.0);
        uint8_t g = (c.g * globalBrightness / 255) * (c.a / 255.0);
        uint8_t b = (c.b * globalBrightness / 255) * (c.a / 255.0);
        _strip->setPixelColor(i, _strip->Color(r, g, b));
    }
    _strip->show();
}

void LEDDriver::applyEffect(LEDEffectType effect, uint16_t start, uint16_t end) {
    currentEffect = effect;
    effectStart = (start >= numLEDs) ? 0 : start;
    effectEnd   = (end == 0 || end >= numLEDs) ? numLEDs - 1 : end;
}

void LEDDriver::setCustomEffect(std::function<void(RGB&, uint32_t)> callback) {
    customEffect = callback;
    currentEffect = LEDEffectType::NONE;
}

void LEDDriver::clear() {
    for (auto& c : ledBuffer) c = {0, 0, 0, 255};
    update();
}

uint16_t LEDDriver::count() const {
    return numLEDs;
}

// Implementação simplificada de efeitos
void LEDDriver::applyFade(uint16_t start, uint16_t end) {
    uint32_t now = millis();
    if (now - lastUpdate < 50) return;
    for (uint16_t i = start; i <= end; ++i) {
        ledBuffer[i].r = (ledBuffer[i].r + 1) % 256;
        ledBuffer[i].g = (ledBuffer[i].g + 2) % 256;
        ledBuffer[i].b = (ledBuffer[i].b + 3) % 256;
    }
    lastUpdate = now;
}

void LEDDriver::applyPulse(uint16_t start, uint16_t end) {
    uint32_t now = millis();
    if (now - lastUpdate < 30) return;
    float factor = (sin(now / 500.0) + 1) / 2.0;
    for (uint16_t i = start; i <= end; ++i) {
        ledBuffer[i].r = uint8_t(factor * 255);
        ledBuffer[i].g = uint8_t(factor * 255);
        ledBuffer[i].b = uint8_t(factor * 255);
    }
    lastUpdate = now;
}

void LEDDriver::applyWave(uint16_t start, uint16_t end) {
    uint32_t now = millis();
    if (now - lastUpdate < 40) return;
    for (uint16_t i = start; i <= end; ++i) {
        ledBuffer[i].r = uint8_t((sin(i + now / 100.0) + 1) * 127);
        ledBuffer[i].g = uint8_t((sin(i + now / 120.0) + 1) * 127);
        ledBuffer[i].b = uint8_t((sin(i + now / 140.0) + 1) * 127);
    }
    lastUpdate = now;
}

void LEDDriver::applyStrobe(uint16_t start, uint16_t end) {
    uint32_t now = millis();
    if (now - lastUpdate < 100) return;
    bool on = (now / 100) % 2;
    for (uint16_t i = start; i <= end; ++i) {
        ledBuffer[i].r = on ? 255 : 0;
        ledBuffer[i].g = on ? 255 : 0;
        ledBuffer[i].b = on ? 255 : 0;
    }
    lastUpdate = now;
}
