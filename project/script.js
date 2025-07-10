var sprite = Draw.loadImage("dude.png")

var pos1 = Vector2(0, 0)
var pos2 = Vector2(63, 63)
var pos3 = Vector2(0, 63)
var pos4 = Vector2(63, 0)

function init() {

}

function update() {
  if (Input.isKeyPressed("ArrowUp")) {
    pos1.y -= 1
    pos2.y += 1
    pos3.x -= 1
    pos4.x += 1
  }
  if (Input.isKeyPressed("ArrowDown")) {
    pos1.y += 1
    pos2.y -= 1
    pos3.x += 1
    pos4.x -= 1
  }
  if (Input.isKeyPressed("ArrowLeft")) {
    pos1.x -= 1
    pos2.x += 1
    pos3.y += 1
    pos4.y -= 1
  }
  if (Input.isKeyPressed("ArrowRight")) {
    pos1.x += 1
    pos2.x -= 1
    pos3.y -= 1
    pos4.y += 1
  }
}

function render() {
  Draw.drawPixel(pos1, Color.red)
  Draw.drawPixel(pos2, Color.blue)
  Draw.drawPixel(pos3, Color.green)
  Draw.drawPixel(pos4, Color.yellow)
}