local script = {}

script.lines = {"apple", "banana", "orange", "kiwi"}
script.keys = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "c", "v", "b", "n", "m"}
script.ShiftKeys = {}
script.cursorPos = Vector(1, 1)

script.measures = {
    areaTopOffset = 6,
    TextLeftOffset = 2,
    charHeight = 4,
    lineSpacing = 1,
    charWidth = 4
}

script.colors = {
    textColor = Color(255, 255, 255, 255),
    bgColor = Color(30, 30, 30, 255),
    cursorColor = Color(255, 0, 0, 255),
    markerColor = Color(0, 0, 255, 255)
}

function script.update_cursor()
    if Input.isKeyJustPressed("up") then
        cursorPos.y = cursorPos.y - 1
        if cursorPos.y < 1 then
            cursorPos.y = 1
        end
        if cursorPos.x > #lines[cursorPos.y] then
            cursorPos.x = #lines[cursorPos.y]
        end
    elseif Input.isKeyJustPressed("down") then
        cursorPos.y = cursorPos.y + 1
        if cursorPos.y > #lines then
            cursorPos.y = #lines
        end
        if cursorPos.x > #lines[cursorPos.y] then
            cursorPos.x = #lines[cursorPos.y]
        end
    elseif Input.isKeyJustPressed("left") then
        cursorPos.x = cursorPos.x - 1
        if cursorPos.x < 0 then
            cursorPos.x = 0
        end
    elseif Input.isKeyJustPressed("right") then
        cursorPos.x = cursorPos.x + 1
        if cursorPos.x > #lines[cursorPos.y] then
            cursorPos.x = #lines[cursorPos.y]
        end
    end


    for key = 1, #keys, 1 do
        if Input.isKeyJustPressed(keys[key]) then
            start = lines[cursorPos.y]:sub(1, cursorPos.x)
            after = lines[cursorPos.y]:sub(cursorPos.x + 1)
            lines[cursorPos.y] = start .. keys[key] .. after
            cursorPos.x = cursorPos.x + 1
        end
    end
    if Input.isKeyJustPressed("space") then
        start = lines[cursorPos.y]:sub(1, cursorPos.x)
        after = lines[cursorPos.y]:sub(cursorPos.x + 1)
        lines[cursorPos.y] = start .. " " .. after
        cursorPos.x = cursorPos.x + 1
    end
    if Input.isKeyJustPressed("return") then
        start = lines[cursorPos.y]:sub(1, cursorPos.x)
        after = lines[cursorPos.y]:sub(cursorPos.x + 1)
        lines[cursorPos.y] = start
        table.insert(lines, cursorPos.y + 1, after)
        cursorPos.y = cursorPos.y + 1
        cursorPos.x = 0
    end
    if Input.isKeyJustPressed("backspace") then
        if cursorPos.x - 1 < 0 then
            original_string = lines[cursorPos.y - 1]
            after = lines[cursorPos.y]:sub(cursorPos.x + 1)
            lines[cursorPos.y - 1] = original_string .. after
            table.remove(lines, cursorPos.y)
            cursorPos.x = #lines[cursorPos.y - 1] - #after
            cursorPos.y = cursorPos.y - 1
        else
            lines[cursorPos.y] = lines[cursorPos.y]:sub(1, cursorPos.x - 1) .. lines[cursorPos.y]:sub(cursorPos.x + 1)
            cursorPos.x = cursorPos.x - 1
        end
    end

end

function script.draw()
    Draw:drawRect(Vector(0, script.measures.areaTopOffset), Vector(63, 63), script.colors.bgColor)
    for line = 1, #lines, 1 do
        markerTop = script.measures.areaTopOffset + (line - 1) * (script.measures.charHeight + script.measures.lineSpacing)
        Draw:drawLine(Vector(0, markerTop), Vector(0, markerTop + 1), script.colors.markerColor)
        Draw:drawText(lines[line], Vector(script.measures.TextLeftOffset, line * (script.measures.charHeight + script.measures.lineSpacing)), script.colors.textColor)
    end
    cursorTop = script.measures.areaTopOffset + (cursorPos.y - 1) * (script.measures.charHeight + script.measures.lineSpacing) - 1
    Draw:drawLine(Vector(cursorPos.x * script.measures.charWidth + 1, cursorTop), Vector(cursorPos.x * script.measures.charWidth + 1, cursorTop + script.measures.charHeight - 1), script.colors.cursorColor)
end

return script