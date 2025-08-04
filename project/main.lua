print("Hello from Lua!")
pos = Vector(0, 0)

SPEED = 10.0

function _update(delta)
    pos = Input:getMousePosition()
end

function _draw()
    Draw:clearScreen(Color(0, 0, 0, 255))
    Draw:drawImage("project/test.png" , Vector(0, 0), pos)
    Draw:drawLine(Vector(0, 0), pos, Color(255, 255, 255, 255))
end