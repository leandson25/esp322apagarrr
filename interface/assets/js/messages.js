// messages.js
// Gerencia logs, alertas e mensagens recebidas do ESP32
export class MessageManager {
    constructor(logContainerId) {
        this.logContainer = document.getElementById(logContainerId);
        this.messages = [];
        document.addEventListener("espMessage", (e) => this.addMessage(e.detail));
    }

    addMessage(msg) {
        const timestamp = new Date().toLocaleTimeString();
        const entry = `[${timestamp}] ${JSON.stringify(msg)}`;
        this.messages.push(entry);
        this.render();
        console.log("Mensagem ESP:", entry);
    }

    render() {
        if(this.logContainer) {
            this.logContainer.innerHTML = this.messages.slice(-50).map(m => `<div>${m}</div>`).join('');
        }
    }

    clear() {
        this.messages = [];
        this.render();
    }
}
