const engine_ctx = document.getElementById("canvas").getContext("2d");

function loadImage(src) {
  const image = new Image();
  image.src = "./project/" + src;

  image.onerror = () => {
    engine_error(`Failed to load image: ${src}`);
    return null;
  };

  return image;
}

function drawImage(image, x, y, width = 1, height = 1) {
  image.width = width;
  image.height = height;
  engine_ctx.drawImage(image, Math.round(x), Math.round(y));
}
function drawPixel(x, y, r, g, b) {
  engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;
  engine_ctx.fillRect(Math.round(x), Math.round(y), 1, 1);
}
function drawLine(x1, y1, x2, y2, r, g, b, weight = 1) {
  engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;
  engine_ctx.lineWidth = weight;
  // Start a new Path
  engine_ctx.beginPath();
  engine_ctx.moveTo(Math.round(x1), Math.round(y1));
  engine_ctx.lineTo(Math.round(x2), Math.round(y2));

  // Draw the Path
  engine_ctx.stroke();
}

function drawRect(x1, y1, x2, y2, r, g, b) {
  engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;

  // Start a new Path
  engine_ctx.fillRect(x1, y1, x1 - x2, y1 - y2); // x, y, width, height

  // Draw the Path
  engine_ctx.stroke();
}

function clearScreen(r, g, b) {
  engine_ctx.fillStyle = `rgb(${r} ${g} ${b})`;

  engine_ctx.fillRect(0, 0, canvas.width, canvas.height);
}

const engine_keysPressed = {};
var engine_keysJustPressed = {};
var engine_keysJustReleased = {};

document.addEventListener("keydown", (event) => {
  if (!engine_keysPressed[event.key]) {
    engine_keysJustPressed[event.key] = true;
  }
  engine_keysPressed[event.key] = true;
});

document.addEventListener("keyup", (event) => {
  if (engine_keysPressed[event.key]) {
    engine_keysJustReleased[event.key] = true;
  }
  delete engine_keysPressed[event.key];
});

function isKeyPressed(key) {
  return engine_keysPressed[key] === true;
}

function isKeyJustPressed(key) {
  return engine_keysJustPressed[key] === true;
}

function isKeyJustReleased(key) {
  return engine_keysJustReleased[key] === true;
}

let engine_lastTime = 0;

function engine_process(currentTime) {
  const delta = (currentTime - engine_lastTime) / 1000;
  engine_lastTime = currentTime;

  update(delta);
  render();

  engine_keysJustPressed = {};
  engine_keysJustReleased = {};
  requestAnimationFrame(engine_process);
}

function engine_error(error) {
  console.error(error);
}
init();
requestAnimationFrame(engine_process);
