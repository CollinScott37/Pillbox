gred = UnusedEntity()

GredSprite = Sprite.new("goose.png", 0.5)
GredTransform = Transform.new(vec3.new(0), vec3.new(0), vec3(10,10,10))
GetSprite(gred) = GredSprite
GetTransform(gred) = GredTransform
LoadImageFile("goose.png", "images")
