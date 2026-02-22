// Configurações do WebSocket
const ws = new WebSocket(`ws://${location.hostname}/ws`);

// Elementos do DOM
const ledOnBtn = document.getElementById('led-on');
const ledOffBtn = document.getElementById('led-off');
const brightnessSlider = document.getElementById('brightness');
const effectSelector = document.getElementById('effect-selector');
const applyEffectBtn = document.getElementById('apply-effect');

const wifiStatus = document.getElementById('wifi-status');
const ledStatus = document.getElementById('led-status');
const currentEffect = document.getElementById('current-effect');

// Eventos do WebSocket
ws.onopen = () => console.log('Conexão WebSocket aberta');
ws.onclose = () => console.log('Conexão WebSocket fechada');
ws.onmessage = (event) => {
    const data = JSON.parse(event.data);
    // Atualiza status do sistema
    if (data.wifi) wifiStatus.textContent = `Wi-Fi: ${data.wifi}`;
    if (data.led) ledStatus.textContent = `LEDs: ${data.led}`;
    if (data.effect) currentEffect.textContent = `Efeito Atual: ${data.effect}`;
};

// Eventos de UI
ledOnBtn.addEventListener('click', () => sendCommand({ led: "on" }));
ledOffBtn.addEventListener('click', () => sendCommand({ led: "off" }));
brightnessSlider.addEventListener('input', () => sendCommand({ brightness: brightnessSlider.value }));
applyEffectBtn.addEventListener('click', () => sendCommand({ effect: effectSelector.value }));

// Função para enviar comandos
function sendCommand(cmd) {
    if (ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify(cmd));
    }
}
