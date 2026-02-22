export class LogWindow {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        document.addEventListener('logMessage', e => this.addLog(e.detail));
    }

    addLog(message) {
        const entry = document.createElement('div');
        entry.textContent = `[${new Date().toLocaleTimeString()}] ${message}`;
        this.container.appendChild(entry);
        this.container.scrollTop = this.container.scrollHeight;
    }
}
