function Color8(r, g, b, a = 1) {
    return {r, g, b, a}
}

function ColorHSV(h, s, v, a = 1) {
    let r, g, b;

    // Hue is a value between 0 and 360 degrees
    h = h % 360;
    if (s === 0) {
        // If there's no saturation, the color is grayscale
        r = g = b = v;
    } else {
        const c = v * s;
        const x = c * (1 - Math.abs(((h / 60) % 2) - 1));
        const m = v - c;

        if (h >= 0 && h < 60) {
            r = c;
            g = x;
            b = 0;
        } else if (h >= 60 && h < 120) {
            r = x;
            g = c;
            b = 0;
        } else if (h >= 120 && h < 180) {
            r = 0;
            g = c;
            b = x;
        } else if (h >= 180 && h < 240) {
            r = 0;
            g = x;
            b = c;
        } else if (h >= 240 && h < 300) {
            r = x;
            g = 0;
            b = c;
        } else {
            r = c;
            g = 0;
            b = x;
        }

        // Apply the offset to the RGB values
        r = (r + m) * 255;
        g = (g + m) * 255;
        b = (b + m) * 255;
    }

    // Return the RGBA values
    return {
        r: Math.round(r),
        g: Math.round(g),
        b: Math.round(b),
        a: a
    };
}

function ColorHex(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16),
      a: 1
    } : null;
  }


const Color = {
    random() {
        let r = Math.round(Math.random() * 255);
        let g = Math.round(Math.random() * 255);
        let b = Math.round(Math.random() * 255);
        return {r, g, b, a: 1}
    },
    red: Color8(255, 0, 0),
    orange: Color8(255, 165, 0),
    yellow: Color8(255, 255, 0),
    green: Color8(0, 255, 0),
    blue: Color8(0, 0, 255),
    purple: Color8(255, 0, 255),
    black: Color8(0, 0, 0),
    white: Color8(255, 255, 255),
}