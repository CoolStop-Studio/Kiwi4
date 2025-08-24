local script = require("script")
local files = require("benchmark.filetest")
local topbar = require("topbar")
local run = require("run")

Window = 0

ScriptOpened = "project/main.lua"
FilesOpened = "project/"

ScriptTitle = "script"
FilesTitle = "files"

function _update(delta)
    print(Config.window.width)
    if Window == 0 then
        script.update(delta)
    elseif Window == 1 then
        files.update(delta)
    elseif Window == 2 then
        run.update(delta)
    end

    topbar.update(delta)
end

function _draw()
    Draw.clearScreen(Color(60, 60, 60, 255))
    if Window == 0 then
        script.draw()
    elseif Window == 1 then
        files.draw()
    elseif Window == 2 then
        run.draw(delta)
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