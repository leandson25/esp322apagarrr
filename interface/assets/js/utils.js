// utils.js
export function hexToRgb(hex) {
    const bigint = parseInt(hex.replace('#',''), 16);
    return [(bigint >> 16) & 255, (bigint >> 8) & 255, bigint & 255];
}

export function rgbToHex(r, g, b) {
    return "#" + ((1 << 24) + (r << 16) + (g << 8) + b).toString(16).slice(1);
}

export function debounce(func, wait) {
    let timeout;
    return (...args) => {
        clearTimeout(timeout);
        timeout = setTimeout(() => func.apply(this, args), wait);
    };
}
