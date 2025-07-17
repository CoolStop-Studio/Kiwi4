var flappy_sprite = Draw.loadImage("flappy.png")
var pipe_sprite = Draw.loadImage("pipe.png")
var pipes = []

var pos = Vector2(10, 32)
var vel = Vector2(0, 0)
var rot = 0.0
var active_pipe = Vector2(0, 0)
var is_active_pipe = false

const JUMP_VEL = -50
const GRAVITY = 150
const PIPE_TIME = 30000.0
const PIPE_SPEED = 15.0

var pipe_countdown = PIPE_TIME

function new_pipe() {
  pipe_countdown = PIPE_TIME
  pipes.push(Vector2(64 + 16, Random.rand_int_range(17, 48)))
}

function init() {
  new_pipe()
}

function update(delta) {
  is_active_pipe = false
  for (let i = 0; i < pipes.length; i++) {
    pipes[i].x -= PIPE_SPEED * delta
    if ((pipes[i].x > 10) && (pipes[i].x < 20) ) {
      active_pipe = pipes[i]
      is_active_pipe = true
    }
  }

  if (is_active_pipe) {
    console.log("activeEEEE")
    if ((pos.y < active_pipe.x - 8) || (pos.y > active_pipe.x + 8)) {
      console.log("DIEEEE")
    }
  }

  pipe_countdown -= delta
  if (pipe_countdown <= 0) {
    new_pipe(0)
  }

  if (Input.isKeyJustPressed("ArrowUp")) {
    vel.y = JUMP_VEL
  }
  
  vel.y += GRAVITY * delta
  pos.y += vel.y * delta
}

function render() {
  Draw.clearScreen(Color8(135, 206, 235));
  let angle = Math.min((vel.y / 80) + (-0.2), 0.5);
  Draw.drawImage(flappy_sprite, pos, Vector2(8, 8), angle);

  for (let i = 0; i < pipes.length; i++) {
    Draw.drawImage(pipe_sprite, Vector2(pipes[i].x, pipes[i].y), Vector2(16, 128))
  }
}