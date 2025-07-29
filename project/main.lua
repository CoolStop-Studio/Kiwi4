print("Hello from Lua!")
pos = Vector(0, 0)

SPEED = 10.0

function _update(delta)
    pos = Input:getMousePosition()
end

function _draw()
    Draw:clearScreen(Color(0, 0, 0, 255))
    Draw:drawPixel(pos, Color(255, 255, 255, 255))
end