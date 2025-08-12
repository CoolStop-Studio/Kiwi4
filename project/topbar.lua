local topbar = {}

function topbar.draw()
    Draw.drawRect(Vector(0, 0), Vector(63, 5), Color(0, 0, 0, 255))
    Draw.drawText("Topbar", Vector(0, 0), Color(255, 255, 255, 255))
end

return topbar