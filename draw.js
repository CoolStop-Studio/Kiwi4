const engine_canvas = document.getElementById("canvas")
const engine_ctx = engine_canvas.getContext("2d");

const Draw = {
  setBlendMode(mode) {
    engine_ctx.globalCompositeOperation = mode;
  },

  loadImage(src) {
    const image = new Image();
    image.src = "./project/" + src;
  
    image.onerror = () => {
      engine_error(`Failed to load image: ${src}`);
      return null;
    };
  
    return image;
  },

  drawImage(image, position, width = 1, height = 1) {
    image.width = width;
    image.height = height;
    engine_ctx.drawImage(image, Math.round(position.x), Math.round(position.y));
  },

  drawPixel(position, color) {
    engine_ctx.fillStyle = `rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`;
    engine_ctx.fillRect(Math.round(position.x), Math.round(position.y), 1, 1);
  },

  drawLine(position1, position2, color, weight = 1) {
    engine_ctx.lineCap = "round";
    engine_ctx.strokeStyle = `rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`;
    engine_ctx.lineWidth = weight;
    // Start a new Path
    engine_ctx.beginPath();
    engine_ctx.moveTo(Math.round(position1.x), Math.round(position1.y));
    engine_ctx.lineTo(Math.round(position2.x), Math.round(position2.y));
  
    // Draw the Path
    engine_ctx.stroke();
  },

  drawRect(position1, position2, color) {
    engine_ctx.fillStyle = `rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`;

    // Calculate width and height
    var width = position2.x - position1.x;
    var height = position2.y - position1.y;

    var startX = position1.x;
    var startY = position1.y;

    if (height >= 0) {
      height++
    } else {
      startY++
      height--
    }
    if (width >= 0) {
      width++
    } else {
      startX++
      width--
    }

    // Start a new Path and draw the rectangle
    engine_ctx.fillRect(startX, startY, width, height);
    
    // Stroke the Path (if you want the border around it)
    engine_ctx.stroke();
  },



  clearScreen(color) {
    engine_ctx.fillStyle = `rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`;
  
    engine_ctx.fillRect(0, 0, canvas.width, canvas.height);
  }
}
