var sprite = Draw.loadImage("dude.png")

var pos = Vector2(0, 0)

function init() {

}

function update() {
  var mousePos = Input.getMousePos()
  pos = mousePos
  if (Input.isKeyJustPressed("r")) {
    Draw.clearScreen(Color.black)
    pos = Vector2(0, 0)
  }
}

function render() {
  Draw.clearScreen(Color8(0, 0, 0, 0.01))
  Draw.drawPixel(Vector2(pos.x, pos.y), ColorHex('003049'))
  Draw.drawPixel(Vector2(pos.y, pos.x), ColorHex('d62828'))
  //Draw.drawPixel(pos3, ColorHex('f77f00'))
  //Draw.drawPixel(pos4, ColorHex('fcbf49'))
}