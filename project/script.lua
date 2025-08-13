local script = {}

lines = {"apple", "banana", "orange", "kiwi"}
keys = {
    "q","w","e","r","t","y","u","i","o","p",
    "a","s","d","f","g","h","j","k","l",
    "z","x","c","v","b","n","m",
    "0","1","2","3","4","5","6","7","8","9",
    "-", "=", "[", "]", "\\", ";", "'", ",", ".", "/",
    "space", "backspace", "up", "down", "left", "right", "return", "tab"
}

shiftKeys = {
    ["1"] = "!", ["2"] = "@", ["3"] = "#", ["4"] = "$", ["5"] = "%",
    ["6"] = "^", ["7"] = "&", ["8"] = "*", ["9"] = "(", ["0"] = ")",
    ["-"] = "_", ["="] = "+", ["["] = "{", ["]"] = "}", ["\\"] = "|",
    [";"] = ":", ["'"] = "\"", [","] = "<", ["."] = ">", ["/"] = "?"
}

cursorPlace = Vector(1, 1)
lastCursorMove = Vector(0, 0)
desiredCursorX = cursorPlace.x

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

scrollSpeed = 60
scroll = Vector(0, 0)

holdWaitTime = 0.35
holdWaitTimeLeft = holdWaitTime
holdSpeedTime = 0.05
holdSpeedTimeLeft = holdSpeedTime

lastHoldKey = ""

function move_cursor_up()
    if cursorPlace.y <= 1 then return end
    if lastCursorMove.y == 0 then desiredCursorX = cursorPlace.x end
    cursorPlace.y = cursorPlace.y - 1
    cursorPlace.x = math.min(desiredCursorX, #lines[cursorPlace.y])
    lastCursorMove = Vector(0, -1)
end

function move_cursor_down()
    if cursorPlace.y >= #lines then return end
    if lastCursorMove.y == 0 then desiredCursorX = cursorPlace.x end
    cursorPlace.y = cursorPlace.y + 1
    cursorPlace.x = math.min(desiredCursorX, #lines[cursorPlace.y])
    lastCursorMove = Vector(0, 1)
end

function move_cursor_left()
    if cursorPlace.x <= 0 then
        if cursorPlace.y <= 1 then return end
        cursorPlace.y = cursorPlace.y - 1
        cursorPlace.x = #lines[cursorPlace.y]
    else
        cursorPlace.x = cursorPlace.x - 1
    end
    desiredCursorX = cursorPlace.x
    lastCursorMove = Vector(-1, 0)
end

function move_cursor_right()
    if cursorPlace.x >= #lines[cursorPlace.y] then
        if cursorPlace.y >= #lines then return end
        cursorPlace.y = cursorPlace.y + 1
        cursorPlace.x = 0
    else
        cursorPlace.x = cursorPlace.x + 1
    end
    desiredCursorX = cursorPlace.x
    lastCursorMove = Vector(1, 0)
end

function type_char(char)
    local start = lines[cursorPlace.y]:sub(1, cursorPlace.x)
    local after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
    lines[cursorPlace.y] = start .. char .. after
    cursorPlace.x = cursorPlace.x + #char
end

function backspace()
    if cursorPlace.x - 1 < 0 then
        local originalString = lines[cursorPlace.y - 1]
        local after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
        lines[cursorPlace.y - 1] = originalString .. after
        table.remove(lines, cursorPlace.y)
        cursorPlace.x = #lines[cursorPlace.y - 1] - #after
        cursorPlace.y = cursorPlace.y - 1
    else
        lines[cursorPlace.y] = lines[cursorPlace.y]:sub(1, cursorPlace.x - 1) ..
                               lines[cursorPlace.y]:sub(cursorPlace.x + 1)
        cursorPlace.x = cursorPlace.x - 1
    end
end

function new_line()
    local start = lines[cursorPlace.y]:sub(1, cursorPlace.x)
    local after = lines[cursorPlace.y]:sub(cursorPlace.x + 1)
    lines[cursorPlace.y] = start
    table.insert(lines, cursorPlace.y + 1, after)
    cursorPlace.y = cursorPlace.y + 1
    cursorPlace.x = 0
end

function script.update_cursor(delta)
    local shiftHeld = Input.isKeyPressed("Left Shift") or Input.isKeyPressed("Right Shift")
    local ctrlHeld = Input.isKeyPressed("Left CTRL") or Input.isKeyPressed("Right CTRL")

    if ctrlHeld then
        if Input.isKeyPressed("up") then
            if scroll.y >= 0 then return end
            scroll.y = scroll.y + scrollSpeed * delta
        elseif Input.isKeyPressed("down") then
            scroll.y = scroll.y - scrollSpeed * delta
        elseif Input.isKeyPressed("left") then
            if scroll.x >= 0 then return end
            scroll.x = scroll.x + scrollSpeed * delta
        elseif Input.isKeyPressed("right") then
            scroll.x = scroll.x - scrollSpeed * delta
        end
        return
    end
    for i = 1, #keys do
        local keyName = keys[i]
        if Input.isKeyJustPressed(keyName) then
            handle_key_press(keyName, shiftHeld)
            lastHoldKey = keyName
        end
    end

    if Input.isKeyJustReleased(lastHoldKey) then
        holdWaitTimeLeft = holdWaitTime
        holdSpeedTimeLeft = 0
        lastHoldKey = ""
    end

    if lastHoldKey ~= "" then
        holdWaitTimeLeft = holdWaitTimeLeft - delta
        if holdWaitTimeLeft <= 0 then
            holdSpeedTimeLeft = holdSpeedTimeLeft - delta
            if holdSpeedTimeLeft <= 0 then
                handle_key_press(lastHoldKey, shiftHeld)
                holdSpeedTimeLeft = holdSpeedTime + holdSpeedTimeLeft
            end
        end
    end
end

function handle_key_press(keyName, shiftHeld)
    if keyName ~= lastHoldKey then
        holdWaitTimeLeft = holdWaitTime
    end
    if keyName == "space" then
        type_char(" ")
    elseif keyName == "backspace" then
        backspace()
    elseif keyName == "return" then
        new_line()
    elseif keyName == "tab" then
        type_char("  ")
    elseif keyName == "up" then
        move_cursor_up()
    elseif keyName == "down" then
        move_cursor_down()
    elseif keyName == "left" then
        move_cursor_left()
    elseif keyName == "right" then
        move_cursor_right()
    else
        if shiftHeld and shiftKeys[keyName] then
            type_char(shiftKeys[keyName])
        else
            type_char(keyName)
        end
    end
end

function script.draw()
    local fullLineHeight = measures.charHeight + measures.lineSpacing
    local fullLineOffset = measures.areaTopOffset + measures.textTopOffset
    Draw.drawRect(Vector(0, measures.areaTopOffset), Vector(63, 63), colors.bgColor)

    for line = 1, #lines do
        local textPos = Vector(0, 0)
        textPos.y = ((line - 1) * fullLineHeight) + fullLineOffset + scroll.y
        textPos.x = measures.textLeftOffset + scroll.x
        Draw.drawText(lines[line], textPos, colors.textColor)
        Draw.drawLine(Vector(0, textPos.y + 1), Vector(0, textPos.y + measures.charHeight - 2), colors.markerColor)
    end

    local cursorPos = Vector(0, 0)
    cursorPos.y = fullLineOffset + (cursorPlace.y - 1) * fullLineHeight + scroll.y
    cursorPos.x = cursorPlace.x * measures.charWidth + 1 + scroll.x
    Draw.drawLine(cursorPos, Vector(cursorPos.x, cursorPos.y + measures.charHeight - 1), colors.cursorColor)
end

return script
