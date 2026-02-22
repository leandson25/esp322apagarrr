// effectSelector.js
export class EffectSelector {
    constructor(selectId, callback) {
        this.select = document.getElementById(selectId);
        this.callback = callback;
        this.init();
    }

    init() {
        this.select.addEventListener('change', (e) => {
            const effect = e.target.value;
            if (this.callback) this.callback(effect);
        });
    }
}
