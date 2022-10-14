local id = ...

if GetKeyCodeDown(KEYBOARD.D) then
    pos = GetTransform(id).position
    pos.x = pos.x + 1;
end

if GetKeyCodeDown(KEYBOARD.A) then
    pos = GetTransform(id).position
    pos.x = pos.x - 1;
end

if GetKeyCodeDown(KEYBOARD.W) then
    pos = GetTransform(id).position
    pos.y = pos.y + 1;
end

if GetKeyCodeDown(KEYBOARD.S) then
    pos = GetTransform(id).position
    pos.y = pos.y - 1;
end