lines = {"apple", "banana", "orange", "kiwi"}
keys = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "c", "v", "b", "n", "m"}
cursorPos = Vector(1, 1)

local script = require("script")

function _update(delta)
    script.update_cursor()
end

function _draw()
    Draw:clearScreen(Color(60, 60, 60, 255))
    script.draw()
end