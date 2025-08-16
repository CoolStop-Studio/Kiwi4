local topbar = {}

local sprites = {
    Load.loadImage("assets/icons/audio.png"),
    Load.loadImage("assets/icons/files.png"),
    Load.loadImage("assets/icons/script.png"),
    Load.loadImage("assets/icons/sprite.png")
}

local measures = {
    iconTopOffset = 0,
    iconLeftOffset = 0,
    iconWidth = 5,
    iconHeight = 5,
    iconSpacing = 0
}

local selected = 0

function topbar.update(delta)
    print(selected)
    if Input.isKeyPressed("Left Alt") or Input.isKeyPressed("Right Alt") then
        if Input.isKeyJustPressed("left") then
            selected = selected - 1
            if selected < 0 then
                selected = 0
            end
        elseif Input.isKeyJustPressed("right") then
            selected = selected + 1
            if selected > #sprites - 1 then
                selected = #sprites - 1
            end
        end
    end
end

function topbar.draw()
    Draw.drawRect(Vector(0, 0), Vector(63, 5), Color(0, 0, 0, 255))

    local position = Vector(measures.iconLeftOffset, measures.iconTopOffset)
    for i = 1, #sprites, 1 do
        new_button(sprites[i], position)
        position.x = position.x + measures.iconWidth + measures.iconSpacing
    end

    selectedpos = Vector(measures.iconLeftOffset + selected * (measures.iconWidth + measures.iconSpacing), measures.iconTopOffset)
    Draw.drawRect(selectedpos, selectedpos + Vector(measures.iconWidth - 1, measures.iconHeight - 1), Color(255, 0, 0, 50))
end

function new_button(image, position)
    Draw.drawImage(position, position + Vector(measures.iconWidth, measures.iconHeight), image)
end

return topbar