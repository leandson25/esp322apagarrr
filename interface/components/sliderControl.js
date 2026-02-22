export class SliderControl {
    constructor(sliderId, callback) {
        this.slider = document.getElementById(sliderId);
        this.slider.addEventListener('input', e => callback(parseFloat(e.target.value)));
    }
}
