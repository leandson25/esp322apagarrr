export class Dial {
    constructor(containerId, callback) {
        this.container = document.getElementById(containerId);
        this.value = 0;
        this.callback = callback;
        this.initDial();
    }

    initDial() {
        this.container.addEventListener('input', e => {
            this.value = parseFloat(e.target.value);
            this.callback(this.value);
        });
    }

    setValue(value) {
        this.value = value;
        this.container.value = value;
    }
}
