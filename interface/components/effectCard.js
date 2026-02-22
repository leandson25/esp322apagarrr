export class EffectCard {
    constructor(containerId, effectData, onSelect) {
        this.container = document.getElementById(containerId);
        this.effectData = effectData;
        this.onSelect = onSelect;
        this.render();
    }

    render() {
        this.container.innerHTML = '';
        this.effectData.forEach(effect => {
            const card = document.createElement('div');
            card.className = 'effect-card';
            card.textContent = effect.name;
            card.addEventListener('click', () => this.onSelect(effect));
            this.container.appendChild(card);
        });
    }
}
