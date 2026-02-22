// api.js
// Este módulo permite integração com APIs externas ou endpoints do firmware
export class API {
    constructor(baseUrl) {
        this.baseUrl = baseUrl;
    }

    async get(endpoint) {
        try {
            const response = await fetch(`${this.baseUrl}/${endpoint}`);
            return await response.json();
        } catch (err) {
            console.error("Erro GET API:", err);
            return null;
        }
    }

    async post(endpoint, data) {
        try {
            const response = await fetch(`${this.baseUrl}/${endpoint}`, {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(data)
            });
            return await response.json();
        } catch (err) {
            console.error("Erro POST API:", err);
            return null;
        }
    }
}
