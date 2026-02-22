export class WebsocketStatus {
    constructor(containerId, api) {
        this.container = document.getElementById(containerId);
        this.api = api;
    }

    connect() {
        this.api.connect();
        this.api.onMessage(() => this.updateStatus('Conectado'));
        this.api.ws.addEventListener('close', () => this.updateStatus('Desconectado'));
    }

    updateStatus(status) {
        this.container.textContent = status;
        this.container.className = `status ${status.toLowerCase()}`;
    }
}
