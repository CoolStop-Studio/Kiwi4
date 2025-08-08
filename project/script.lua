local script = {}

lines = {"apple", "banana", "orange", "kiwi"}
keys = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "c", "v", "b", "n", "m", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}
ShiftKeys = {}
cursorPlace = Vector(1, 1)

measures = {
    areaTopOffset = 6,
    textTopOffset = 1,
    textLeftOffset = 2,
    charHeight = 4,
    lineSpacing = 1,
    charWidth = 4
}

colors = {
    textColor = Color(255, 255, 255, 255),
    bgColor = Color(30, 30, 30, 255),
    cursorColor = Color(255, 0, 0, 255),
    markerColor = Color(0, 0, 255, 255)
}

scroll = Vector(0, 0)

function move_cursor_up()
    if cursorPlace.y <= 1 then
        return
    end
    cursorPlace.y = cursorPlace.y - 1
    if cursorPlace.x > #lines[cursorPlace.y] then
        cursorPlace.x = #lines[cursorPlace.y]
    end
end

function move_cursor_down()
    if cursorPlace.y >= #lines then
        return
    end
    cursorPlace.y = cursorPlace.y + 1
    if cursorPlace.x > #lines[cursorPlace.y] then
        cursorPlace.x = #lines[cursorPlace.y]
    end
end

function move_cursor_left()
    if cursorPlace.x <= 0 then
        if cursorPlace.y <= 1 then
            return
        end
        cursorPlace.y = cursorPlace.y - 1
        cursorPlace.x = #lines[cursorPlace.y]
        return
    end
    cursorPlace.x = cursorPlace.x - 1
end

function move_cursor_right()
    if cursorPlace.x >= #lines[cursorPlace.y] then
        if cursorPlace.y >= #lines then
            return
        end
        cursorPlace.y = cursorPlace.y + 1
        cursorPlace.x = 0
        return
    end
    cursorPlace.x = cursorPlace.x + 1
end

function script.update_cursor()
    if Input.isKeyPressed("Left Ctrl") then
        if Input.isKeyJustPressed("up") then
            scroll.y = scroll.y - 1
        elseif Input.isKeyJustPressed("down") then
            scroll.y = scroll.y + 1
        elseif Input.isKeyJustPressed("left") then
            scroll.x = scroll.x - 1
        elseif Input.isKeyJustPressed("right") then
            scroll.x = scroll.x + 1
        end
    else
        if Input.isKeyJustPressed("up") then
            move_cursor_up()
        elseif Input.isKeyJustPressed("down") then
            move_cursor_down()
        elseif Input.isKeyJustPressed("left") then
            move_cursor_left()
        elseif Input.isKeyJustPressed("right") then
            move_cursor_right()
        end
    end

    -- print(Input:getLastKeyPressed())

    for key = 1, #keys, 1 do
        if Input.isKeyJustPressed(keys[key]) then
            start = lines[cursorPlace.y]:sub(1, cursorPlace.x)
            after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
            lines[cursorPlace.y] = start .. keys[key] .. after
            cursorPlace.x = cursorPlace.x + 1
        end
    end
    if Input.isKeyJustPressed("space") then
        start = lines[cursorPlace.y]:sub(1, cursorPlace.x)
        after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
        lines[cursorPlace.y] = start .. " " .. after
        cursorPlace.x = cursorPlace.x + 1
    end
    if Input.isKeyJustPressed("return") then
        start = lines[cursorPlace.y]:sub(1, cursorPlace.x)
        after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
        lines[cursorPlace.y] = start
        table.insert(lines, cursorPlace.y + 1, after)
        cursorPlace.y = cursorPlace.y + 1
        cursorPlace.x = 0
    end
    if Input.isKeyJustPressed("backspace") then
        if cursorPlace.x - 1 < 0 then
            original_string = lines[cursorPlace.y - 1]
            after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
            lines[cursorPlace.y - 1] = original_string .. after
            table.remove(lines, cursorPlace.y)
            cursorPlace.x = #lines[cursorPlace.y - 1] - #after
            cursorPlace.y = cursorPlace.y - 1
        else
            lines[cursorPlace.y] = lines[cursorPlace.y]:sub(1, cursorPlace.x - 1) .. lines[cursorPlace.y]:sub(cursorPlace.x + 1)
            cursorPlace.x = cursorPlace.x - 1
        end
    end

end

function script.draw()
    fullLineHeight = measures.charHeight + measures.lineSpacing
    fullLineOffset = measures.areaTopOffset + measures.textTopOffset
    Draw:drawRect(Vector(0, measures.areaTopOffset), Vector(63, 63), colors.bgColor)

    for line = 1, #lines, 1 do
        textPos = Vector(0, 0)
        textPos.y = ((line - 1) * fullLineHeight) + fullLineOffset + scroll.y
        textPos.x = measures.textLeftOffset + scroll.x
        Draw:drawLine(Vector(0, textPos.y + 1), Vector(0, textPos.y + measures.charHeight - 2), colors.markerColor)
        Draw:drawText(lines[line], textPos, colors.textColor)
    end

    cursorPos = Vector(0, 0)
    cursorPos.y = fullLineOffset + (cursorPlace.y - 1) * fullLineHeight + scroll.y
    cursorPos.x = cursorPlace.x * measures.charWidth + 1 + scroll.x
    Draw:drawLine(cursorPos, Vector(cursorPos.x, cursorPos.y + measures.charHeight - 1), colors.cursorColor)
end

return script