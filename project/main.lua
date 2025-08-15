local script = require("script")
local topbar = require("topbar")

function _update(delta)
    script.update_cursor(delta)
    topbar.update()
end

function _draw()
    Draw.clearScreen(Color(60, 60, 60, 255))
    script.draw()
    topbar.draw()
end