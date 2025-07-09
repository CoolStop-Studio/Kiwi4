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