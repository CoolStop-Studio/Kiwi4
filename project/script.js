var sprite = Draw.loadImage("dude.png")

var pos = Vector2(0, 0)
var vel = Vector2(0, 0)

const JUMP_VEL = -50
const GRAVITY = 100
const ACCEL = 50
const DECEL = 100
const SPEED = 50

function init() {

}

function update(delta) {
  if (Input.isKeyPressed("ArrowUp")) {
    vel.y = JUMP_VEL
  }
  if (Input.isKeyPressed("ArrowRight")) {
    vel.x += ((SPEED - vel.x) * ACCEL) * delta;
  } else if (Input.isKeyPressed("ArrowLeft")) {
    vel.x -= ((SPEED + vel.x) * ACCEL) * delta;
  } else {
    vel.x += ((0 - vel.x) * DECEL) * delta;
  }
  // vel.y += GRAVITY * delta
  pos.x += vel.x * delta
  pos.y += vel.y * delta
}

function render() {
  console.log(vel.x)
  Draw.clearScreen(Color.black);
  Draw.drawImage(sprite, pos)
}