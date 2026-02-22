// ledPanel.js
export class LedPanel {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        this.ledElements = [];
        this.currentEffect = null;
        this.brightness = 0;
        this.init();
    }

    init() {
        // Cria LEDs dinamicamente
        for (let i = 0; i < 10; i++) {
            const led = document.createElement('div');
            led.classList.add('led', 'futuristic');
            led.dataset.id = i;
            this.container.appendChild(led);
            this.ledElements.push(led);
        }
    }

    updateEffect(effectName) {
        this.currentEffect = effectName;
        // Atualiza display do efeito atual
        document.getElementById('current-effect').textContent = `Efeito: ${effectName}`;
    }

    setBrightness(value) {
        this.brightness = value;
        this.ledElements.forEach(led => {
            led.style.opacity = value / 100;
        });
        document.getElementById('current-brightness').textContent = `Brilho: ${value}%`;
    }

    updateLed(id, color) {
        if (this.ledElements[id]) {
            this.ledElements[id].style.backgroundColor = color;
        }
    }
}
