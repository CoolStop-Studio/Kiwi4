let pos = { x: 0, y: 0 };
let vel = { x: 0, y: 0 };

const SPEED = 1000;
const GRAV = 30;
const FRICTION = 100;
const JUMP_HEIGHT = -30;

const GROUND = 50;
const SPRITE_SIZE = { width: 4, height: 8 };

const OBJECTS = [{ pos: { x: 40, y: 40 }, size: { width: 4, height: 8 } }];

var image;

var jump_buffer = false;
var can_dash = false;
var flip_h = false;

var dashing = false;
var dash_left = 0.0;
const DASH_LENGTH = 0.1;
const DASH_STRENGTH = 3;

function init() {
  image = loadImage('dude.png');
}

function update(delta) {
  dash_left -= delta;
  if (dash_left > 0) {
    dashing = true;
  } else {
    dashing = false;
  }
  var onground;

  if (isKeyJustPressed('c')) {
    jump_buffer = true;
  }
  if (isKeyJustReleased('c')) {
    jump_buffer = false;
  }

  if (isKeyPressed('ArrowLeft')) {
    if (!dashing) {
      flip_h = true;
      vel.x -= SPEED * delta;
    }
  }
  if (isKeyPressed('ArrowRight')) {
    if (!dashing) {
      flip_h = false;
      vel.x += SPEED * delta;
    }
  }
  if (isKeyJustPressed('x')) {
    if (can_dash && !dashing) {
      dash();
    }
  }

  if (!dashing) {
    if (vel.x > 0) {
      vel.x -= FRICTION * delta;
      if (vel.x < 0) {
        vel.x = 0;
      }
    } else if (vel.x < 0) {
      vel.x += FRICTION * delta;
      if (vel.x > 0) {
        vel.x = 0;
      }
    }
    

  }

  if (!(pos.y > GROUND - SPRITE_SIZE.height)) {
    onground = false;
    if (!dashing) {
      vel.y += GRAV * delta;
    }
  }

  pos.x += vel.x * delta;
  pos.y += vel.y * delta;

  if (pos.y > GROUND - SPRITE_SIZE.height) {
    onground = true;
    pos.y = GROUND - SPRITE_SIZE.height;
    vel.y = 0;
  }

  if (onground && jump_buffer) {
    jump_buffer = false;
    vel.y = JUMP_HEIGHT;
  }
  if (onground) {
    can_dash = true;
  }
}

function dash() {
  can_dash = false;
  dash_left = DASH_LENGTH;

  let dir = { x: 0, y: 0 };
  if (isKeyPressed('ArrowLeft')) {
    dir.x -= 1;
  }
  if (isKeyPressed('ArrowRight')) {
    dir.x += 1;
  }
  if (isKeyPressed('ArrowUp')) {
    dir.y -= 1;
  }
  if (isKeyPressed('ArrowDown')) {
    dir.y += 1;
  }
  if (dir.y == 0 && dir.x == 0) {
    if (flip_h) {
      dir.x = -1;
    } else {
      dir.x = 1;
    }
  }
  vel.x = dir.x * DASH_STRENGTH;
  vel.y = dir.y * DASH_STRENGTH;
}

function render() {
  clearScreen(0, 255, 0);

  drawImage(image, pos.x, pos.y, 2, 2);
  drawRect(0, GROUND, 64, GROUND, 0, 0, 0);
  drawLine(0, GROUND + 1, 64, GROUND + 1, 0, 0, 0, 2);
}
