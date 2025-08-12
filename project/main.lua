local script = require("script")
local topbar = require("topbar")

img = Load.loadImage("extra/kiwi4.png")
function _update(delta)
    script.update_cursor(delta)
end

function _draw()
    Draw.clearScreen(Color(60, 60, 60, 255))
    script.draw()
    topbar.draw()
    Draw.drawImage(Vector(0, 0), Vector(63, 63))
end