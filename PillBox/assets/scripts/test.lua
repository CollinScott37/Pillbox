local id = ... --UnusedEntity()

GredTransform = Transform.new(vec3.new(0), vec3.new(0), vec3(10,10,10))


--    Attempt 1
--GredSprite = Sprite.new("goose.png", 0.5)
--GetSprite(gred) = GredSprite


-- Attempt 2
LoadImageFile("goose.png", "images")
GetSprite(0) = Sprite.new("goose.png", 0.5)

--GetTransform(gred) = GredTransform
--LoadImageFile("goose.png", "images")
