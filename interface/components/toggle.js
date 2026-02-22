export class Toggle {
    constructor(toggleId, callback) {
        this.toggle = document.getElementById(toggleId);
        this.toggle.addEventListener('change', e => callback(e.target.checked));
    }

    setState(state) {
        this.toggle.checked = state;
    }
}
