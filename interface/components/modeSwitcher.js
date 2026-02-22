// modeSwitcher.js
export class ModeSwitcher {
    constructor(buttonSelector, callback) {
        this.buttons = document.querySelectorAll(buttonSelector);
        this.callback = callback;
        this.init();
    }

    init() {
        this.buttons.forEach(button => {
            button.addEventListener('click', () => {
                const mode = button.dataset.mode;
                if (this.callback) this.callback(mode);
            });
        });
    }
}
