local id = ...



if id == gCurrLetter then
    
    GetTransform(id).scale = vec3.new(20)
    GetSprite(id).z = 0.5
    local goosePos = GetTransform(gGoose).position

    --print(goosePos.x, goosePos.y, "\n")

    local triggerPos = GetTrigger(id)
    --goosePos = GetTransform(goose).position



    if( goosePos.x > triggerPos.tl.x and goosePos.x < triggerPos.br.x) then
        if(goosePos.y < triggerPos.tl.y and goosePos.y > triggerPos.br.y) then
            GetTransform(id).position.x = glPos.x + (20 * id)
            if(id > 2) then
                GetTransform(id).position.x = glPos.x + (25 * id) + 10
            end
            GetTransform(id).position.y = glPos.y
            gCurrLetter = gCurrLetter + 1
            local no = "nothing" .. gCurrLetter .. ".png"
            print("is at: ", no)
            GetSprite(nothing1).name = no
            GetTransform(nothing1).scale.x = GetTransform(nothing1).scale.x + 14
            GetTransform(nothing1).scale.y = GetTransform(nothing1).scale.y + 14
        end
    end
elseif id > gCurrLetter then
    GetSprite(id).z = 1 --change to 1
end


