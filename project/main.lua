pos = Vector(0, 0)

SPEED = 50.0

function _update(delta)
    pos = Input:getMousePosition()
end

function _draw()
    Draw:clearScreen(Color(60, 60, 60, 255))
    Draw:drawText("Hello from Lua!", Vector(2, 7))
end