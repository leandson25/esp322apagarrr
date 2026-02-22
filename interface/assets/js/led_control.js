// led_control.js
import { ESPWebSocket } from './websocket.js';

export class LEDController {
    constructor(ws) {
        this.ws = ws;
        this.currentMode = 'manual';
        this.brightness = 100;
        this.color = { r: 255, g: 255, b: 255 };
    }

    setMode(mode) {
        this.currentMode = mode;
        this.sendModeUpdate();
    }

    setBrightness(value) {
        this.brightness = value;
        // Envia como comando separado para brilho
        this.sendCommand({
            command: "brightness",
            value: value
        });
    }

    setColor(hex) {
        // Converte hex para RGB
        this.color = this.hexToRgb(hex);
        // Envia comando de LED com cores
        this.sendLedCommand();
    }

    // Converte cor hex para RGB
    hexToRgb(hex) {
        const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
        return result ? {
            r: parseInt(result[1], 16),
            g: parseInt(result[2], 16),
            b: parseInt(result[3], 16)
        } : { r: 255, g: 255, b: 255 };
    }

    // Envia comando de LED com cores
    sendLedCommand() {
        const command = {
            command: "led",
            r: this.color.r,
            g: this.color.g,
            b: this.color.b
        };
        this.sendCommand(command);
    }

    // Envia comando de modo
    sendModeUpdate() {
        const command = {
            command: "mode",
            mode: this.currentMode
        };
        this.sendCommand(command);
    }

    // Envia comando genérico
    sendCommand(command) {
        if (this.ws) {
            this.ws.sendCommand(command);
        } else {
            console.warn("WebSocket não disponível");
        }
    }

    // Liga LEDs com cor atual
    turnOn() {
        this.sendLedCommand();
    }

    // Desliga LEDs
    turnOff() {
        this.sendCommand({
            command: "led",
            r: 0,
            g: 0,
            b: 0
        });
    }

    // Aplica efeito
    applyEffect(effectType, params = {}) {
        const command = {
            command: "effect",
            effect: effectType,
            ...params
        };
        this.sendCommand(command);
    }
}
