print("Hello from Lua!")
pos = Vector(0, 0)

SPEED = 50.0

function _update(delta)
    pos = Input:getMousePosition()
end

function _draw()
    print(Input:getMousePosition().x, Input:getMousePosition().y)
    Draw:clearScreen(Color(0, 0, 0, 255))
    Draw:drawLine(Vector(0, 0), Input:getMousePosition(), Color(255, 255, 255, 255))
    -- Draw:drawText("Hello from Lua!", Vector(0, 0), Color(255, 255, 255, 255))
end