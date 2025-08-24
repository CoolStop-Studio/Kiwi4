self = {}

function self._update(delta)
    --print("CALLING FROM MAIN")
end

function self._draw()
    Draw.drawRect(Vector(25, 25), Vector(80, 80), Color(255, 0, 0, 255))
end

return self