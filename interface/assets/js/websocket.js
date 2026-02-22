// websocket.js
// Gerencia a conexão WebSocket com o ESP32
import { Settings } from '../config/settings.js';

export class ESPWebSocket {
    constructor(url) {
        // Usa URL fornecida ou pega do settings
        this.url = url || Settings.get('websocket.url') || 'ws://192.168.4.1:81';
        this.reconnectInterval = Settings.get('websocket.reconnectInterval') || 3000;
        this.maxReconnectAttempts = 10;
        this.reconnectAttempts = 0;
        this.ws = null;
        this.connect();
    }

    connect() {
        if (this.reconnectAttempts >= this.maxReconnectAttempts) {
            console.error("Máximo de tentativas de conexão alcançado");
            return;
        }

        console.log(`Conectando ao ESP32 em: ${this.url}`);
        
        try {
            this.ws = new WebSocket(this.url);

            this.ws.onopen = () => {
                console.log("✅ Conectado ao ESP32 via WebSocket");
                this.reconnectAttempts = 0; // Reset attempts na conexão bem-sucedida
            };

            this.ws.onmessage = (msg) => {
                try {
                    const data = JSON.parse(msg.data);
                    this.handleMessage(data);
                } catch (err) {
                    console.error("Erro ao processar mensagem:", err);
                }
            };

            this.ws.onclose = () => {
                console.warn("⚠ WebSocket desconectado, tentando reconectar...");
                this.scheduleReconnect();
            };

            this.ws.onerror = (err) => {
                console.error("Erro WebSocket:", err);
                this.ws.close();
            };
        } catch (e) {
            console.error("Falha ao criar WebSocket:", e);
            this.scheduleReconnect();
        }
    }

    scheduleReconnect() {
        this.reconnectAttempts++;
        if (this.reconnectAttempts < this.maxReconnectAttempts) {
            const delay = this.reconnectInterval * Math.min(this.reconnectAttempts, 5);
            console.log(`Tentativa ${this.reconnectAttempts}/${this.maxReconnectAttempts}. Reconectando em ${delay}ms...`);
            setTimeout(() => this.connect(), delay);
        } else {
            console.error("Não foi possível conectar após múltiplas tentativas");
        }
    }

    sendCommand(command) {
        if (this.ws && this.ws.readyState === WebSocket.OPEN) {
            this.ws.send(JSON.stringify(command));
        } else {
            console.warn("WebSocket não está aberto. Comando não enviado:", command);
        }
    }

    handleMessage(data) {
        // Mensagens recebidas do firmware
        // Exemplo: { type: "status", ledState: "on", mode: "pulse" }
        if (data && typeof data === 'object') {
            document.dispatchEvent(new CustomEvent("espMessage", { detail: data }));
        }
    }
    
    // Fecha a conexão
    disconnect() {
        if (this.ws) {
            this.ws.close();
            this.ws = null;
        }
    }
    
    // Verifica se está conectado
    isConnected() {
        return this.ws && this.ws.readyState === WebSocket.OPEN;
    }
}
