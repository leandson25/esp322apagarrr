#include "pwm_driver.h"

PWMDriver::PWMDriver() {}

PWMDriver::~PWMDriver() {}

void PWMDriver::addChannel(uint8_t pin, uint32_t frequency, uint8_t duty) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, duty);
    channels.push_back({pin, duty, frequency});
}

void PWMDriver::setDuty(uint8_t pin, uint8_t duty) {
    for (auto& ch : channels) {
        if (ch.pin == pin) {
            ch.duty = duty;
            analogWrite(ch.pin, duty);
            break;
        }
    }
}

void PWMDriver::fadeTo(uint8_t pin, uint8_t targetDuty, uint32_t duration) {
    for (auto& ch : channels) {
        if (ch.pin == pin) {
            fades.push_back({pin, ch.duty, targetDuty, millis(), duration, true});
            break;
        }
    }
}

void PWMDriver::update() {
    uint32_t now = millis();
    for (auto& fade : fades) {
        if (!fade.active) continue;
        uint32_t elapsed = now - fade.startTime;
        if (elapsed >= fade.duration) {
            setDuty(fade.pin, fade.targetDuty);
            fade.active = false;
        } else {
            float factor = float(elapsed) / float(fade.duration);
            uint8_t duty = fade.startDuty + (fade.targetDuty - fade.startDuty) * factor;
            setDuty(fade.pin, duty);
        }
    }
}
void PWMDriver::stop(uint8_t pin) {
    setDuty(pin, 0);
}
