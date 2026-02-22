// effects.js
// Centraliza e controla todos os efeitos visuais disponíveis no firmware
export class EffectsManager {
    constructor(ws) {
        this.ws = ws;
        this.availableEffects = ['fade', 'pulse', 'wave', 'strobe'];
        this.currentEffect = null;
        document.addEventListener("changeEffect", (e) => this.setEffect(e.detail));
    }

    setEffect(effectName) {
        if(this.availableEffects.includes(effectName)) {
            this.currentEffect = effectName;
            this.sendEffect();
        } else {
            console.warn("Efeito não disponível:", effectName);
        }
    }

    sendEffect() {
        if(this.ws && this.currentEffect) {
            this.ws.sendCommand({
                type: "effect",
                name: this.currentEffect
            });
        }
    }

    nextEffect() {
        let index = this.availableEffects.indexOf(this.currentEffect);
        index = (index + 1) % this.availableEffects.length;
        this.setEffect(this.availableEffects[index]);
    }
}
