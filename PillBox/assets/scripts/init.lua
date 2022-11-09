local goose, N0, O, C, A, N1, E, QM, corner1, corner2 = ...

gGoose = goose --global

gN0 = N0
gO = O
gC = C
gA = A
gN = N
gE = E
gQM = QM

glPos = vec3.new(-100,100-15,0)
gCurrLetter = N0

print("running init\n");


LoadSound("quack.wav", "sounds")


--Can do sprite = GetSprite(goose)
--Goose
LoadImageFile("goose.png", "images")
GetSprite(goose).name = "goose.png"

GetSprite(goose).z = 0.5
GetTransform(goose).position = vec3.new(0)
GetTransform(goose).rotation = vec3.new(0)
GetTransform(goose).scale = vec3.new(10,10,0)

--For letters
local lScale = vec3.new(0,0,0)

--N0
LoadImageFile("cube.png", "images")
LoadImageFile("n.png", "images")
GetSprite(N0).name = "n.png"
GetSprite(N0).z = 0.5
GetTransform(N0).position = vec3.new(50, 50, 0)
GetTransform(N0).rotation = vec3.new(0)
GetTransform(N0).scale = lScale

local c1tl = vec3.new(0)
local c1br = vec3.new(0)
--tl = (pos.x + radius) * scale.x
c1tl.x = (GetTransform(N0).position.x - 15/2)-- * GetTransform(cube1).scale.x
c1tl.y = (GetTransform(N0).position.y + 15/2)-- * GetTransform(cube1).scale.y
c1br.x = (GetTransform(N0).position.x + 15/2)-- * GetTransform(cube1).scale.x
c1br.y = (GetTransform(N0).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(N0).tl = c1tl
GetTrigger(N0).br = c1br

--[[
print("c1 pos", GetTransform(N0).position.x, ", ", GetTransform(N0).position.y,  "\n")
print("tl is: ", c1tl.x, ", ", c1tl.y, "\n")
print("br is: ", c1br.x, ", ", c1br.y, "\n")
--]]




--End of N0

--O
LoadImageFile("o.png", "images")
GetSprite(O).name = "o.png"
GetSprite(O).z = 0.5
GetTransform(O).position = vec3.new(0, 0, 0)
GetTransform(O).rotation = vec3.new(0)
GetTransform(O).scale = lScale

local Otl = vec3.new(0)
local Obr = vec3.new(0)
--tl = (pos.x + radius)
Otl.x = (GetTransform(O).position.x - 15/2)-- * GetTransform(cube1).scale.x
Otl.y = (GetTransform(O).position.y + 15/2)-- * GetTransform(cube1).scale.y
Obr.x = (GetTransform(O).position.x + 15/2)-- * GetTransform(cube1).scale.x
Obr.y = (GetTransform(O).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(O).tl = Otl
GetTrigger(O).br = Obr

--C
LoadImageFile("c.png", "images")
GetSprite(C).name = "c.png"
GetSprite(C).z = 0.5
GetTransform(C).position = vec3.new(-50, 50, 0)
GetTransform(C).rotation = vec3.new(0)
GetTransform(C).scale = lScale

local Ctl = vec3.new(0)
local Cbr = vec3.new(0)
--tl = (pos.x + radius)
Ctl.x = (GetTransform(C).position.x - 15/2)-- * GetTransform(cube1).scale.x
Ctl.y = (GetTransform(C).position.y + 15/2)-- * GetTransform(cube1).scale.y
Cbr.x = (GetTransform(C).position.x + 15/2)-- * GetTransform(cube1).scale.x
Cbr.y = (GetTransform(C).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(C).tl = Ctl
GetTrigger(C).br = Cbr

--[[
--N0 Corner 1
GetSprite(corner1).name = "cube.png"
GetSprite(corner1).z = 0

GetTransform(corner1).position = Ctl --vec3.new(50-(25/2), 50+(25/2), 0)
GetTransform(corner1).rotation = vec3.new(0)
GetTransform(corner1).scale = vec3.new(1,1,0)

--N0 corner2
GetSprite(corner2).name = "cube.png"
GetSprite(corner2).z = 0

GetTransform(corner2).position = Cbr --vec3.new(50+(25/2), 50-(25/2), 0)
GetTransform(corner2).rotation = vec3.new(0)
GetTransform(corner2).scale = vec3.new(1,1,0)
--]]

--A
LoadImageFile("a.png", "images")
GetSprite(A).name = "a.png"
GetSprite(A).z = 0.5
GetTransform(A).position = vec3.new(0, 0, 0)
GetTransform(A).rotation = vec3.new(0)
GetTransform(A).scale = lScale

local Atl = vec3.new(0)
local Abr = vec3.new(0)
--tl = (pos.x + radius)
Atl.x = (GetTransform(A).position.x - 15/2)-- * GetTransform(cube1).scale.x
Atl.y = (GetTransform(A).position.y + 15/2)-- * GetTransform(cube1).scale.y
Abr.x = (GetTransform(A).position.x + 15/2)-- * GetTransform(cube1).scale.x
Abr.y = (GetTransform(A).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(A).tl = Atl
GetTrigger(A).br = Abr



--N1
LoadImageFile("n.png", "images")
GetSprite(N1).name = "n.png"
GetSprite(N1).z = 0.5
GetTransform(N1).position = vec3.new(50, -50, 0)
GetTransform(N1).rotation = vec3.new(0)
GetTransform(N1).scale = lScale

local N1tl = vec3.new(0)
local N1br = vec3.new(0)
--tl = (pos.x + radius)
N1tl.x = (GetTransform(N1).position.x - 15/2)-- * GetTransform(cube1).scale.x
N1tl.y = (GetTransform(N1).position.y + 15/2)-- * GetTransform(cube1).scale.y
N1br.x = (GetTransform(N1).position.x + 15/2)-- * GetTransform(cube1).scale.x
N1br.y = (GetTransform(N1).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(N1).tl = N1tl
GetTrigger(N1).br = N1br


--E
LoadImageFile("e.png", "images")
GetSprite(E).name = "e.png"
GetSprite(E).z = 0.5
GetTransform(E).position = vec3.new(0, 0, 0)
GetTransform(E).rotation = vec3.new(0)
GetTransform(E).scale = lScale

local Etl = vec3.new(0)
local Ebr = vec3.new(0)
--tl = (pos.x + radius)
Etl.x = (GetTransform(E).position.x - 15/2)-- * GetTransform(cube1).scale.x
Etl.y = (GetTransform(E).position.y + 15/2)-- * GetTransform(cube1).scale.y
Ebr.x = (GetTransform(E).position.x + 15/2)-- * GetTransform(cube1).scale.x
Ebr.y = (GetTransform(E).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(E).tl = Etl
GetTrigger(E).br = Ebr

--QM
LoadImageFile("qm.png", "images")
GetSprite(QM).name = "qm.png"
GetSprite(QM).z = 0.5
GetTransform(QM).position = vec3.new(-50, -50, 0)
GetTransform(QM).rotation = vec3.new(0)
GetTransform(QM).scale = lScale

local QMtl = vec3.new(0)
local QMbr = vec3.new(0)
--tl = (pos.x + radius)
QMtl.x = (GetTransform(QM).position.x - 15/2)-- * GetTransform(cube1).scale.x
QMtl.y = (GetTransform(QM).position.y + 15/2)-- * GetTransform(cube1).scale.y
QMbr.x = (GetTransform(QM).position.x + 15/2)-- * GetTransform(cube1).scale.x
QMbr.y = (GetTransform(QM).position.y - 15/2)-- * GetTransform(cube1).scale.y
GetTrigger(QM).tl = QMtl
GetTrigger(QM).br = QMbr


--nothing 1
LoadImageFile("nothing1.png", "images")
LoadImageFile("nothing2.png", "images")
LoadImageFile("nothing3.png", "images")
LoadImageFile("nothing4.png", "images")
LoadImageFile("nothing5.png", "images")
LoadImageFile("nothing6.png", "images")
LoadImageFile("nothing7.png", "images")
LoadImageFile("nothing8.png", "images")
nothing1 = UnusedEntity()
GetSprite(nothing1).name = "nothing1.png"
GetSprite(nothing1).z = 0.9
GetTransform(nothing1).position = vec3.new(0, 0, 0)
GetTransform(nothing1).rotation = vec3.new(0)
GetTransform(nothing1).scale = vec3.new(0,0,0)

--[[
--nothing 2
nothing2 = UnusedEntity()
GetSprite(nothing2).name = "nothing.png"
GetSprite(nothing2).z = 0.9
GetTransform(nothing2).position = vec3.new(100, 0, 0)
GetTransform(nothing2).rotation = vec3.new(0)
GetTransform(nothing2).scale = vec3.new(100,100,0)
--]]
print("done running init")