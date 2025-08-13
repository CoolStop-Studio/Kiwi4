local topbar = {}

hovering = false

function topbar.update()
    hovering = Input.isMouseInRect(Vector(58, 0), Vector(63, 5), true)
end

function topbar.draw()
    Draw.drawRect(Vector(0, 0), Vector(63, 5), Color(0, 0, 0, 255))
    Draw.drawText("Topbar", Vector(0, 0), Color(255, 255, 255, 255))
    if hovering then
        Draw.drawRect(Vector(58, 0), Vector(63, 5), Color(0, 255, 0, 255))
    else
        Draw.drawRect(Vector(58, 0), Vector(63, 5), Color(0, 0, 255, 255))
    end
end

return topbar