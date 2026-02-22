export class Slider {
    constructor(sliderId, min, max, step, callback) {
        this.slider = document.getElementById(sliderId);
        
        // Verifica se o elemento existe
        if (!this.slider) {
            console.warn(`Slider não encontrado: ${sliderId}`);
            return;
        }
        
        this.slider.min = min;
        this.slider.max = max;
        this.slider.step = step;
        
        // Verifica se callback é função
        if (typeof callback === 'function') {
            this.slider.addEventListener('input', e => callback(parseFloat(e.target.value)));
        }
    }

    setValue(value) {
        if (this.slider) {
            this.slider.value = value;
        }
    }
    
    // Retorna o valor atual
    getValue() {
        return this.slider ? parseFloat(this.slider.value) : 0;
    }
    
    // Verifica se o slider está disponível
    isAvailable() {
        return this.slider !== null;
    }
}
