// dashboard.js
// Atualiza status, indicadores e gráficos em tempo real
export class Dashboard {
    constructor() {
        this.ledStatus = document.getElementById('led-status');
        this.modeDisplay = document.getElementById('mode-display');
        this.brightnessBar = document.getElementById('brightness-bar');
        this.colorPreview = document.getElementById('color-preview');

        // Verifica se elementos existem antes de adicionar listeners
        if (document) {
            document.addEventListener("espMessage", (event) => this.update(event.detail));
        }
    }

    update(data) {
        if (!data || !data.type) return;
        
        if (data.type === 'status') {
            if (this.ledStatus) {
                this.ledStatus.textContent = (data.ledState || 'off').toUpperCase();
            }
            if (this.modeDisplay) {
                this.modeDisplay.textContent = (data.mode || 'manual').toUpperCase();
            }
            if (this.brightnessBar && data.brightness !== undefined) {
                this.brightnessBar.style.width = `${data.brightness}%`;
            }
            if (this.colorPreview && data.color) {
                this.colorPreview.style.backgroundColor = data.color;
            }
        }
    }
}
