var sprite = Draw.loadImage("flappy.png")

var pos = Vector2(10, 32)
var vel = Vector2(0, 0)
var rot = 0.0

const JUMP_VEL = -50
const GRAVITY = 100
const ACCEL = 50
const DECEL = 100
const SPEED = 50

function init() {

}

function update(delta) {
  if (Input.isKeyJustPressed("ArrowUp")) {
    vel.y = JUMP_VEL
  }
  
  vel.y += GRAVITY * delta
  pos.y += vel.y * delta
}

function render() {
  console.log(vel.x)
  Draw.clearScreen(Color.black);
  let angle = Math.min((vel.y / 80) + (-0.2), 0.5);
  Draw.drawImage(sprite, pos, 8, 8, angle);
}