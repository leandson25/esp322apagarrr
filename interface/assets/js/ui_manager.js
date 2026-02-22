// ui_manager.js
export class UIManager {
    constructor() {
        this.initButtons();
        this.initSliders();
        this.initColorPicker();
    }

    initButtons() {
        const buttons = document.querySelectorAll('.mode-btn');
        buttons.forEach(btn => {
            btn.addEventListener('click', () => {
                const mode = btn.dataset.mode;
                if (mode) {
                    document.dispatchEvent(new CustomEvent('changeMode', { detail: mode }));
                }
            });
        });
    }

    initSliders() {
        const brightnessSlider = document.getElementById('brightness-slider');
        if (brightnessSlider) {
            brightnessSlider.addEventListener('input', () => {
                const value = brightnessSlider.value;
                document.dispatchEvent(new CustomEvent('changeBrightness', { detail: value }));
            });
        }
    }

    initColorPicker() {
        const colorPicker = document.getElementById('color-picker');
        if (colorPicker) {
            colorPicker.addEventListener('input', () => {
                const color = colorPicker.value;
                document.dispatchEvent(new CustomEvent('changeColor', { detail: color }));
            });
        }
    }
}
