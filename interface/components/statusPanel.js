export class StatusPanel {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
    }

    setStatus(text, type='info') {
        this.container.textContent = text;
        this.container.className = `status-panel ${type}`;
    }
}
