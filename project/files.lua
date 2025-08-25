local self = {}

local openPath = {"project", "test"}
local files = {}
local folders = {}

local filesicon = Load.loadImage("assets/icons/script.png")
local foldericon = Load.loadImage("assets/icons/files.png")

local selected = 1

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
    selectedColor = Color.hex("F08F8F"),
    bgColor = Color.hex("202020"),
}

local scrollSpeed = 60
local scroll = Vector(0, 0)

local function arraytostringpath(array)
    local path = ""
    for i = 1, #array do
        path = path .. array[i] .. "/"
    end
    return path
end

local function stringtoarraypath(path)
    local array = {}
    for folder in path:gmatch("[^/]+") do
        table.insert(array, folder)
    end
    return array
end

local function load_folder(path)
    openPath = stringtoarraypath(path)
    FilesTitle = openPath[#openPath] .. "/"
    files = Files.getFiles(path)
    folders = Files.getFolders(path)
    
    selected = 1
    scroll = Vector(0, 0)
end

function self.load(path)
    load_folder(path)
end

function self.update(delta)
    local shiftHeld = Input.isKeyPressed("Left Shift") or Input.isKeyPressed("Right Shift")
    local ctrlHeld = Input.isKeyPressed("Left Ctrl") or Input.isKeyPressed("Right Ctrl")
    local altHeld = Input.isKeyPressed("Left Alt") or Input.isKeyPressed("Right Alt")

    if shiftHeld then return end
    if altHeld then return end

    if ctrlHeld then
        if Input.isKeyPressed("up") then
            scroll.y = scroll.y + scrollSpeed * delta
            if scroll.y >= 0 then
                scroll.y = 0
            end
        elseif Input.isKeyPressed("down") then
            scroll.y = scroll.y - scrollSpeed * delta
        elseif Input.isKeyPressed("left") then
            scroll.x = scroll.x + scrollSpeed * delta
            if scroll.x >= 0 then
                scroll.x = 0
            end
        elseif Input.isKeyPressed("right") then
            scroll.x = scroll.x - scrollSpeed * delta
        end
        return
    end

    if Input.isKeyJustPressed("up") then
        selected = selected - 1
        if selected < 1 then
            selected = 1
        end
    elseif Input.isKeyJustPressed("down") then
        selected = selected + 1
        if selected > #files + #folders then
            selected = #files + #folders
        end
    end

    if Input.isKeyJustPressed("return") then
        if selected <= #folders then
            
            table.insert(openPath, folders[selected])

            load_folder(arraytostringpath(openPath))
        else
            if files[selected - #folders]:sub(-4) == ".lua" then
                ScriptTitle = files[selected - #folders]:sub(0, #files[selected - #folders])

                local new = arraytostringpath(openPath) .. files[selected - #folders]
                print(new)

                Window = 0
                Load_new(new)
            end
        end
    end

    -- Go back to parent folder
    if Input.isKeyJustPressed("backspace") then
        if #openPath > 1 then  -- don't remove root
            table.remove(openPath)  -- remove last folder
            load_folder(arraytostringpath(openPath))
        end
    end

end

function self.draw()
    local fullLineHeight = measures.charHeight + measures.lineSpacing
    local fullLineOffset = measures.areaTopOffset + measures.textTopOffset
    Draw.drawRect(Vector(0, measures.areaTopOffset), Vector(95, 95), colors.bgColor)

    for line = 1, #folders do
        local textPos = Vector(0, 0)
        textPos.y = ((line - 1) * fullLineHeight) + fullLineOffset + scroll.y
        textPos.x = measures.textLeftOffset + scroll.x
        if line == selected then
            Draw.drawText(folders[line], textPos + Vector(1, 0), colors.selectedColor)
        else
            Draw.drawText(folders[line], textPos, colors.textColor)
        end
        Draw.drawImage(Vector(textPos.x - measures.iconWidth, textPos.y), Vector(textPos.x, textPos.y + measures.iconHeight), foldericon)
    end

    for line = 1, #files do
        local textPos = Vector(0, 0)
        textPos.y = ((line - 1) * fullLineHeight) + fullLineOffset + scroll.y + (#folders * fullLineHeight)
        textPos.x = measures.textLeftOffset + scroll.x
        if line + #folders == selected then
            Draw.drawText(files[line], textPos + Vector(1, 0), colors.selectedColor)
        else
            Draw.drawText(files[line], textPos, colors.textColor)
        end
        Draw.drawImage(Vector(textPos.x - measures.iconWidth, textPos.y), Vector(textPos.x, textPos.y + measures.iconHeight), filesicon)
    end
end

return self