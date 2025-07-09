const engine_canvas = document.getElementById("canvas")
const engine_ctx = engine_canvas.getContext("2d");

const Draw = {
  loadImage(src) {
    const image = new Image();
    image.src = "./project/" + src;
  
    image.onerror = () => {
      engine_error(`Failed to load image: ${src}`);
      return null;
    };
  
    return image;
  },

  drawImage(image, x, y, width = 1, height = 1) {
    image.width = width;
    image.height = height;
    engine_ctx.drawImage(image, Math.round(x), Math.round(y));
  },

  drawPixel(x, y, r, g, b) {
    engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;
    engine_ctx.fillRect(Math.round(x), Math.round(y), 1, 1);
  },

  drawLine(x1, y1, x2, y2, r, g, b, weight = 1) {
    engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;
    engine_ctx.lineWidth = weight;
    // Start a new Path
    engine_ctx.beginPath();
    engine_ctx.moveTo(Math.round(x1), Math.round(y1));
    engine_ctx.lineTo(Math.round(x2), Math.round(y2));
  
    // Draw the Path
    engine_ctx.stroke();
  },

  drawRect(x1, y1, x2, y2, r, g, b) {
    engine_ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;

    // Calculate width and height
    var width = x2 - x1;
    var height = y2 - y1;

    // Ensure width and height are never zero (force at least 1px if same)
    if (width === 0) {
        width = (x2 > x1) ? 1 : -1; // Ensure the width has a direction
    }
    if (height === 0) {
        height = (y2 > y1) ? 1 : -1; // Ensure the height has a direction
    }

    // Calculate start positions based on original coordinates
    var startX = x1;
    var startY = y1;

    console.log(`Width: ${width}, Height: ${height}`);

    // Start a new Path and draw the rectangle
    engine_ctx.fillRect(startX, startY, width, height);
    
    // Stroke the Path (if you want the border around it)
    engine_ctx.stroke();
},



  clearScreen(r, g, b) {
    engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;
  
    engine_ctx.fillRect(0, 0, canvas.width, canvas.height);
  }
}
