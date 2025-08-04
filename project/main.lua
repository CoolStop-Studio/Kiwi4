print("Hello from Lua!")
pos = Vector(0, 0)

SPEED = 50.0

function _update(delta)
    pos = Input:getMousePosition()
end

function _draw()
    print(SPEED)
    Draw:clearScreen(Color(0, 0, 0, 255))
    Draw:drawImage("test.png" , Vector(0, 0), pos)
    Draw:drawLine(Vector(0, 0), Vector(SPEED, SPEED), Color(255, 255, 255, 255))
end