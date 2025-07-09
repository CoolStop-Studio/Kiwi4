let engine_keysPressed = {};
let engine_keysJustPressed = {};
let engine_keysJustReleased = {};

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