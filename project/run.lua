local self = {}

local measures = {
    areaTopOffset = 6,
    textTopOffset = 1,
    textLeftOffset = 5,
    charHeight = 4,
    lineSpacing = 1,
    charWidth = 4,
    iconWidth = 5,
    iconHeight = 5
}

local colors = {
    textColor = Color.hex("FFFFFF"),
    bgColor = Color.hex("202020"),
}

local path = "test.main"
local script = require(path)

function self.update(delta)
    script._update(delta)
end

function self.draw()
    script._draw()
end

return self