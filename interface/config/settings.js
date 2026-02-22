/**
 * settings.js
 * 
 * Gerenciamento central de configurações para a interface web
 * do projeto esp322apagarrr. Suporta:
 * - Armazenamento local (localStorage)
 * - Atualização dinâmica de parâmetros
 * - Integração com WebSocket para sincronização com o ESP32
 * - Temas, modos e presets de efeitos
 */

export const Settings = (function () {
    const defaultSettings = {
        theme: 'futuristic',        // Tema visual padrão
        brightness: 80,             // Brilho inicial dos LEDs
        speed: 50,                  // Velocidade dos efeitos
        effect: 'fade',             // Efeito padrão
        mode: 'auto',               // Modo de operação
        websocket: {
            url: 'ws://192.168.4.1:81',
            reconnectInterval: 3000
        }
    };

    let currentSettings = {...defaultSettings};

    // Carrega configurações do localStorage
    function load() {
        const stored = localStorage.getItem('esp322apagarrr_settings');
        if (stored) {
            try {
                currentSettings = {...currentSettings, ...JSON.parse(stored)};
            } catch (e) {
                console.warn('Falha ao carregar configurações salvas', e);
            }
        }
    }

    // Salva configurações no localStorage
    function save() {
        localStorage.setItem('esp322apagarrr_settings', JSON.stringify(currentSettings));
    }

    // Atualiza uma configuração específica
    function set(key, value) {
        if (key in currentSettings) {
            currentSettings[key] = value;
            save();
            return true;
        }
        console.warn(`Chave de configuração inválida: ${key}`);
        return false;
    }

    // Retorna o valor de uma configuração
    function get(key) {
        return key in currentSettings ? currentSettings[key] : null;
    }

    // Reset completo para as configurações padrão
    function reset() {
        currentSettings = {...defaultSettings};
        save();
    }

    // Retorna todas as configurações
    function getAll() {
        return {...currentSettings};
    }

    // Atualiza várias configurações de uma vez
    function update(settings) {
        currentSettings = {...currentSettings, ...settings};
        save();
    }

    // Inicializa o módulo
    function init() {
        load();
        console.log('Settings carregadas', currentSettings);
    }

    return {
        init,
        get,
        set,
        getAll,
        reset,
        update
    };
})();
