local self = {}

local sprites = {
    Load.loadImage("assets/icons/script.png"),
    Load.loadImage("assets/icons/files.png"),
}

local measures = {
    iconTopOffset = 0,
    iconLeftOffset = 0,
    iconWidth = 5,
    iconHeight = 5,
    iconSpacing = 0,
    textTopOffset = 1,
    textLeftOffset = 30
}

function self.update(delta)
    if Input.isKeyPressed("Left Alt") or Input.isKeyPressed("Right Alt") then
        if Input.isKeyJustPressed("left") then
            Window = Window - 1
            if Window < 0 then
                Window = 0
            else
                Load_new(ScriptOpened)
            end
        elseif Input.isKeyJustPressed("right") then
            Window = Window + 1
            if Window > #sprites - 1 then
                Window = #sprites - 1
            else
                Load_new(FilesOpened)
            end
        end
    end
end

function self.draw()
    Draw.drawRect(Vector(0, 0), Vector(63, 5), Color(0, 0, 0, 255))

    local position = Vector(measures.iconLeftOffset, measures.iconTopOffset)
    for i = 1, #sprites, 1 do
        new_button(sprites[i], position)
        position.x = position.x + measures.iconWidth + measures.iconSpacing
    end

    local selectedpos = Vector(measures.iconLeftOffset + Window * (measures.iconWidth + measures.iconSpacing), measures.iconTopOffset)
    Draw.drawRect(selectedpos, selectedpos + Vector(measures.iconWidth - 1, measures.iconHeight - 1), Color(0, 0, 0, 150))
    Draw.drawLine(Vector(selectedpos.x, selectedpos.y + measures.iconHeight), Vector(selectedpos.x + measures.iconWidth - 1, selectedpos.y + measures.iconHeight), Color(255, 255, 255, 255))



    local textPos = Vector(measures.textLeftOffset, measures.textTopOffset)
    Draw.drawText(Title, textPos, Color(255, 255, 255, 255))
end

function new_button(image, position)
    Draw.drawImage(position, position + Vector(measures.iconWidth, measures.iconHeight), image)
end

return self