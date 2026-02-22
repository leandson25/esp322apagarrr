export class HeaderFooter {
    constructor(headerId, footerId) {
        this.header = document.getElementById(headerId);
        this.footer = document.getElementById(footerId);
    }

    setHeader(title) {
        this.header.textContent = title;
    }

    setFooter(text) {
        this.footer.textContent = text;
    }
}
