#include <iostream>
#include <thread>
#include <chrono>
#include "../src/Types.h"
#include "../src/Engine.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

using namespace Pillbox;


int main(int argc, const char* argv[]) {

    std::cout << "Takes a min to load\n";

    Engine e;
    e.StartUp();
    
    //Used for initializing the sacred words
    vec3 letterScale = vec3(5, 5, 1);
    auto InitMazeObject = [&](int id, string n)
    {
        //Sprite
        if (n != "null")
        {
            e.graphics.LoadImageFile(n, "images");
            e.ecs.Get<Sprite>(id) = Sprite{ n, 0.1 };
        }

        
        //Maze
        vec3 mi = e.maze.CreateRandomValidMazeIndex(false);
        e.ecs.Get<MazeObject>(id) = MazeObject{ mi, false };

        //Transform
        vec3 wp = e.maze.MazeIndexToWorldPosVec3(mi);
        e.ecs.Get<Transform>(id) = Transform{ wp, vec3(0), letterScale };

        //Colliders
        vec3 tl = vec3(0);
        vec3 br = vec3(0);
        //tl = (pos.x + radius) * scale.x
        tl.x = (wp.x - letterScale.x / 2);// * GetTransform(cube1).scale.x
        tl.y = (wp.y + letterScale.x / 2);// * GetTransform(cube1).scale.y
        br.x = (wp.x + letterScale.x / 2);// * GetTransform(cube1).scale.x
        br.y = (wp.y - letterScale.x / 2);// * GetTransform(cube1).scale.y
        e.ecs.Get<Trigger>(id) = Trigger{ tl, br };
    };
    
    /*
    EntityID cube = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(cube) = Sprite{ "cube.png", 0.1 };
    e.ecs.Get<Transform>(cube) = Transform{ vec3(0), vec3(0), vec3(1,1,1) };
    */
    e.graphics.LoadImageFile("cube.png", "images");
    e.graphics.LoadImageFile("goose.png", "images");

    std::cout << "done loading\n";
    
    //Gooes info
    EntityID goose = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(goose) = Sprite{ "goose.png", 0.1 };
    e.ecs.Get<Transform>(goose) = Transform{ vec3(0), vec3(0), vec3(10,10,1) };
    vec3 gooseIndex = e.maze.CreateRandomValidMazeIndex(false);
    e.ecs.Get<Transform>(goose).position = e.maze.MazeIndexToWorldPosVec3(gooseIndex);
    
    //letters
    EntityID N0 = e.ecs.UnusedEntity();
    EntityID O = e.ecs.UnusedEntity();
    EntityID C = e.ecs.UnusedEntity();
    EntityID A = e.ecs.UnusedEntity();
    EntityID N1 = e.ecs.UnusedEntity();
    EntityID E = e.ecs.UnusedEntity();
    EntityID QM = e.ecs.UnusedEntity();
    InitMazeObject(N0, "n.png");
    InitMazeObject(O, "o.png");
    InitMazeObject(C, "c.png");
    InitMazeObject(A, "a.png");
    InitMazeObject(N1, "n.png");
    InitMazeObject(E, "e.png");
    InitMazeObject(QM, "qm.png");

    //Sounds
    e.sounds.LoadSound("quack.wav", "sounds");
    e.sounds.LoadSound("moyai.wav", "sounds");
    //std::::cout << "N0 ID:" << N0 << "\n";
    
    int nothingCount = 0;
    e.graphics.LoadImageFile("nothing1.png", "images");
    e.graphics.LoadImageFile("nothing2.png", "images");
    e.graphics.LoadImageFile("nothing3.png", "images");
    e.graphics.LoadImageFile("nothing4.png", "images");
    e.graphics.LoadImageFile("nothing5.png", "images");
    e.graphics.LoadImageFile("nothing6.png", "images");
    e.graphics.LoadImageFile("nothing7.png", "images");
    e.graphics.LoadImageFile("nothing8.png", "images");
    
    //GOOSE MOVEMENT START
    bool hasTarget = false; //does the goose have a letter to go to  
    bool stopGoose = false; //should the goose behave normally?
    bool isMoving = false; //is it already move towards a position
    bool alreadyCalcDistance = false; //has it calculated a distane to go to
    auto GetNewTarget = [&]()
    {
        
        auto min = 100000000.0f;
        auto posTarget = -1;
        for(int i = N0; i <= QM; i += 1)
        {
            
            auto mo = e.ecs.Get<MazeObject>(i);
            if(!mo.isFound)
            {
                auto pos = e.ecs.Get<Transform>(i).position;
                float dist = glm::distance(pos,  e.ecs.Get<Transform>(goose).position);
                if(dist <= min)
                {
                    posTarget = i;
                    min = dist;
                }
            }
        }
        return posTarget; //return found all
    };

    //movement
    vec3 newMovePos = vec3(0); //position to move to in world space
    vec3 movOffsetAmount = vec3(0); //offset move amount in world space
    auto pathStack = std::stack<vec2>(); //stack containing positions to move to

    //std::::cout << "BEFORE LOOP:\n";
    //std::::cout << "Goose Position WORLD x: " << e.ecs.Get<Transform>(goose).position.x <<  " y:" << e.ecs.Get<Transform>(goose).position.y << "\n";
    //auto goosetempmi = e.maze.WorldPosToMazeIndex(e.ecs.Get<Transform>(goose).position);
    //std::::cout << "Goose Position MAZE x: " << goosetempmi.x <<  " y:" << goosetempmi.y << "\n";
    //std::::cout << "AFTER LOOP\n";
    bool alreadyCreatedObjects = false;
    int startObject = -1;
    int endObject = -1;
    auto ChangeOverlay = [&](string name)
    {
        if(!alreadyCreatedObjects)
        {
            int id = -1;
            for (int j = 0; j < e.maze.height; j += 1)
            {
                for (int i = 0; i < e.maze.width; i += 1)
                {
                    id = e.ecs.UnusedEntity();
                    if(startObject == -1)
                    {
                        startObject = id; 
                    }
                    e.ecs.Get<Transform>(id).position = e.maze.MazeIndexToWorldPos(i,j);
                    e.ecs.Get<Transform>(id).rotation = vec3(0);
                    e.ecs.Get<Transform>(id).scale = vec3(1, 1, 1) * (5.0f/2.0f);
                    e.ecs.Get<Sprite>(id) = Sprite {name, 0.2f};
                }
            }
            endObject = id;
            alreadyCreatedObjects = true;
        }
        else
        {
            for(int i = startObject; i < endObject; i += 1)
            {
                e.ecs.Get<Sprite>(i) = Sprite {name, 0.8f};
            }
        }
        

    };
    EntityID nothing1 = e.ecs.UnusedEntity();
    bool isResetting = false;

    auto ResetEverything = [&]()
    {   
        // :)
        e.ecs.Get<Transform>(nothing1) = Transform{ vec3(0), vec3(100), vec3(100,100,1)};
        e.ecs.Get<Sprite>(nothing1) = Sprite {"nothing8.png", 0.15f};
        e.graphics.Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        nothingCount = 0;
        ChangeOverlay("nothing1.png");
        isResetting = true;
        hasTarget = false;
        std::cout << "quack\n";
        e.sounds.PlaySound("quack.wav");
        
        e.maze.CreateMaze();
        
        InitMazeObject(N0, "n.png");
        InitMazeObject(O, "o.png");
        InitMazeObject(C, "c.png");
        InitMazeObject(A, "a.png");
        InitMazeObject(N1, "n.png");
        InitMazeObject(E, "e.png");
        InitMazeObject(QM, "qm.png");

        vec3 gooseIndex = e.maze.CreateRandomValidMazeIndex(false);
        e.ecs.Get<Transform>(goose).position = e.maze.MazeIndexToWorldPosVec3(gooseIndex);
        isMoving = false;
        isResetting = false;
        e.ecs.Get<Transform>(nothing1) = Transform{ vec3(0), vec3(0), vec3(0,0,1)};
    };

    auto GooseBehavior = [&]()
    {
        if(isResetting) {return;}

        if(stopGoose)
        {
            ResetEverything();
            stopGoose = false;
            return;
        }

        if(!hasTarget)
        {
            int id = GetNewTarget();
            if(id == -1) //no more targets
            {
                stopGoose = true;
                return;
            }
            else
            {
                //set target
                hasTarget = true;

                MazeObject mo = e.ecs.Get<MazeObject>(id);
                //vec3 heckel = e.ecs.Get<Transform>(id).position;
                //std::::cout << "mo x: " << mo.mazeIndex.x <<  " y:" << mo.mazeIndex.y << "\n";
                //std::::cout << "heckel x: " << heckel.x <<  " y:" << heckel.y << "\n";
                
                e.pathfinder.setGoal(vec2(mo.mazeIndex));

                //get goose index pos;
                vec3 goosePos = e.ecs.Get<Transform>(goose).position;
                vec2 gooseMazeIndex = e.maze.WorldPosToMazeIndex(goosePos);
                
                //find the path to target
                bool foundPath = e.pathfinder.findPath(gooseMazeIndex);
                
                if(!foundPath)
                {
                    //std::::cout <<  "Did not find path\n";
                    stopGoose = true;
                }
                else
                {
                    //std::::cout << "has found path\n";
                    pathStack = e.pathfinder.getPath();
                }
                return;
            }
        }
        
        //std::::cout << "INSIDE LOOP:\n1newMovePos WORLD x: " << newMovePos.x <<  " y:" << newMovePos.y << "\n";
        //vec2 newMoveMazeIndex = e.maze.WorldPosToMazeIndex(newMovePos);
        //std::::cout << "1newMoveMazeIndex MAZE x: " << newMoveMazeIndex.x <<  " y:" << newMoveMazeIndex.y << "\n";
        //std::::cout << "size: " << pathStack.size() << "\n";

        if(!isMoving)
        {   
            //std::::cout << "INSIDE !isMoving:\n";
            isMoving = true;

            vec2 huh = pathStack.top();
            pathStack.pop();
            //vec3 wot = vec3(huh.x, huh.y, 0);
            newMovePos = e.maze.MazeIndexToWorldPosVec2(huh);
            //std::::cout << "2newMoveMaze WORLD x: " << newMovePos.x <<  " y:" << newMovePos.y << "\n\n";
            //std::cout << "2newMovePos MAZE x:" << huh.x <<  " y:" << huh.y << "\n\n";
        }
        else
        {
            if(!alreadyCalcDistance)
            {
                vec3 diff = newMovePos - e.ecs.Get<Transform>(goose).position;
                movOffsetAmount.x = diff.x;
                movOffsetAmount.y = diff.y;
                movOffsetAmount.z = diff.z;

                if(diff.x > 0)
                {
                    e.ecs.Get<Transform>(goose).rotation = vec3(-90);
                }
                else
                {
                    e.ecs.Get<Transform>(goose).rotation = vec3(90);
                }
                if(diff.y > 0)
                {
                    e.ecs.Get<Transform>(goose).rotation = vec3(0);
                }
                else if(diff.y < 0)
                {
                    e.ecs.Get<Transform>(goose).rotation = vec3(180);
                }

                alreadyCalcDistance = true;
            }

            float dist = glm::distance(newMovePos,  e.ecs.Get<Transform>(goose).position);
            //std::cout << "dist: x:" << dist.x << " y: " << dist.y << " z, " << dist.z << "\n";
            //std::::cout << "dist: " << dist << "\n";
            //within a certain range
            if(dist < 0.01)//if(dist.x <= 0.01f || dist.y <= 0.01f)
            {
                 e.ecs.Get<Transform>(goose).position = newMovePos;
                 isMoving = false;
                 alreadyCalcDistance = false;
            }
            else
            {
                e.ecs.Get<Transform>(goose).position += movOffsetAmount;
            }

        }
    };

    auto LetterBehavior = [&]()
    {
        for(int i = N0; i <= QM; i += 1)
        {
            auto mo = e.ecs.Get<MazeObject>(i);
            auto pos = e.ecs.Get<Transform>(i).position;
            if(!mo.isFound)
            {
                float dist = glm::distance(pos,  e.ecs.Get<Transform>(goose).position);
                if(dist <= 0.01f)
                {
                    //std::cout << "Here\n";
                    //std::::cout << (e.ecs.Get<MazeObject>(id).isFound == e.ecs.Get<MazeObject>(N0).isFound) << "\n";
                    hasTarget = false; //tell goose it does not have a target
                    e.ecs.Get<MazeObject>(i).isFound = true;
                    nothingCount += 1;
                    string name = (string)"nothing" + std::to_string(nothingCount) + (string)".png";
                    ChangeOverlay(name);
                    e.sounds.PlaySound("moyai.wav");
                    //std::::cout << (e.ecs.Get<MazeObject>(id).isFound == e.ecs.Get<MazeObject>(N0).isFound) << "\n";
                }
            }
            else
            {
                float num = (i - N0) * 20.0f;
                if((i-N0) >= 2)
                {
                    num += 10;
                }
                e.ecs.Get<Transform>(i).position = vec3(-num, 0, 0);
                e.ecs.Get<Transform>(i).scale = vec3(-20, -20, 1);
            }
        }
    };

    ChangeOverlay("nothing1.png");

    e.RunGameLoop([&]() {
        
        e.graphics.Draw();
        
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q))
        {
            ResetEverything();
        }
        
        GooseBehavior();
        LetterBehavior();
        
        return;

        });

    return 0;
}
