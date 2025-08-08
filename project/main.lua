local script = require("script")

function _update(delta)
    script.update_cursor()
end

function _draw()
    Draw:clearScreen(Color(60, 60, 60, 255))
    script.draw()
end