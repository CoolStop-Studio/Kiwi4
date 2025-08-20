local script = require("script")
local files = require("files")
local topbar = require("topbar")

Window = 0
Title = ""

ScriptOpened = "project/main.lua"
FilesOpened = "project/"

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

function Load_new(path)
    if Window == 0 then
        ScriptOpened = path
        script.load(path)
    elseif Window == 1 then
        FilesOpened = path
        files.load(path)
    end
end