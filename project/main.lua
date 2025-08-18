local script = require("script")
local files = require("files")
local topbar = require("topbar")

Window = 0
Opened = ""

function _update(delta)
    if Window == 0 then
        script.update(delta)
    elseif Window == 1 then
        files.update(delta)
    end

    topbar.update(delta)
end

function _draw()
    Draw.clearScreen(Color(60, 60, 60, 255))
    if Window == 0 then
        script.draw()
    elseif Window == 1 then
        files.draw()
    end
    topbar.draw()
end