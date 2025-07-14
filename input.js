let engine_keysPressed = {};
let engine_keysJustPressed = {};
let engine_keysJustReleased = {};

let engine_mousePos = {x: 0, y: 0};

canvas.addEventListener('mousemove', (e) => {
  const rect = canvas.getBoundingClientRect();

  const mouseX = e.clientX - rect.left;
  const mouseY = e.clientY - rect.top;

  const scaleX = rect.width / 64;
  const scaleY = rect.height / 64;

  engine_mousePos.x = Math.floor(mouseX / scaleX);
  engine_mousePos.y = Math.floor(mouseY / scaleY);
});

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

const Input = {
    getMousePos() {
        return engine_mousePos;
    },
    isKeyPressed(key) {
        return engine_keysPressed[key] === true;
    },

    isKeyJustPressed(key) {
        return engine_keysJustPressed[key] === true;
    },

    isKeyJustReleased(key) {
        return engine_keysJustReleased[key] === true;
    },
}