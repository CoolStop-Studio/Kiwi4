var sprite = Draw.loadImage("dude.png")

var pos1 = {x: 5, y: 5}
var pos2 = {x: 5, y: 5}

function init() {

}

function update() {
  if (Input.isKeyPressed("ArrowUp")) {
    pos1.y -= 1
  }
  if (Input.isKeyPressed("ArrowDown")) {
    pos1.y += 1
  }
  if (Input.isKeyPressed("ArrowLeft")) {
    pos1.x -= 1
  }
  if (Input.isKeyPressed("ArrowRight")) {
    pos1.x += 1
  }

  if (Input.isKeyPressed("w")) {
    pos2.y -= 1
  }
  if (Input.isKeyPressed("s")) {
    pos2.y += 1
  }
  if (Input.isKeyPressed("a")) {
    pos2.x -= 1
  }
  if (Input.isKeyPressed("d")) {
    pos2.x += 1
  }
}

function render() {
  Draw.clearScreen(20, 0, 100)
  Draw.drawRect(pos1.x, pos1.y, pos2.x, pos2.y, 0, 255, 255)
  Draw.drawPixel(pos1.x, pos1.y, 255, 0, 0)
  Draw.drawPixel(pos2.x, pos2.y, 0, 255, 0)
}