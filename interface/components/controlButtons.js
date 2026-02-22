export class ControlButtons {
    constructor(buttonSelector, callback) {
        this.buttons = document.querySelectorAll(buttonSelector);
        this.buttons.forEach(btn => btn.addEventListener('click', () => callback(btn.dataset.action)));
    }
}
