print("Hello from Lua!")
local pos = Vector(0, 0)
Draw:drawPixel(pos, Color(255, 255, 255, 255))

SPEED = 10.0

function _update(delta)
    pos.x = pos.x + delta * SPEED
    pos.y = pos.y + delta * SPEED
end

function _draw()
    print("HI")

    Draw:clearScreen(Color(0, 0, 0, 255))
    Draw:drawPixel(pos, Color(255, 255, 255, 255))
end