#include <iostream>

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
            e.ecs.Get<Sprite>(id) = Sprite{ n, 0.4 };
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
    

    EntityID cube = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(cube) = Sprite{ "cube.png", 0.1 };
    e.ecs.Get<Transform>(cube) = Transform{ vec3(0), vec3(0), vec3(1,1,1) };
    e.graphics.LoadImageFile("cube.png", "images");

    std::cout << "done loading\n";
    
    EntityID goose = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(goose) = Sprite{ "cube.png", 0.1 };
    e.ecs.Get<Transform>(goose) = Transform{ vec3(0), vec3(0), vec3(1,1,1) };
    vec3 gooseIndex = e.maze.CreateRandomValidMazeIndex(false);
    e.ecs.Get<Transform>(goose).position = e.maze.MazeIndexToWorldPosVec3(gooseIndex);
    EntityID N0 = e.ecs.UnusedEntity();
    EntityID O = e.ecs.UnusedEntity();
    EntityID C = e.ecs.UnusedEntity();
    EntityID A = e.ecs.UnusedEntity();
    EntityID N1 = e.ecs.UnusedEntity();
    EntityID E = e.ecs.UnusedEntity();
    EntityID QM = e.ecs.UnusedEntity();

    //objects
    InitMazeObject(N0, "n.png");
    InitMazeObject(O, "o.png");
    InitMazeObject(C, "c.png");
    InitMazeObject(A, "a.png");
    InitMazeObject(N1, "n.png");
    InitMazeObject(E, "e.png");
    InitMazeObject(QM, "qm.png");

    //Sounds
    e.sounds.LoadSound("quack.wav", "sounds");

    bool hasTarget = false;
    auto GetNewTarget = [&]()
    {
        for(int i = N0; i <= QM; i += 1)
        {
            auto posTarget = e.ecs.Get<MazeObject>(i);
            if(!posTarget.isFound)
            {
                return i;
            }
        }
        return -1; //return found all
    };

    //should the goose behave normally?
    bool stopGoose = false;
    
    //movement
    bool isMoving = false;
    vec3 newMovePos = vec3(0);
    
    bool alreadyCalcDistance = false;
    vec3 movOffsetAmount = vec3(0);
    auto pathStack = std::stack<vec2>();;

    auto GooseBehavior = [&]()
    {
        if(stopGoose) { return; }

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
                e.pathfinder.setGoal(vec2(mo.mazeIndex));

                //get goose index pos;
                vec3 goosePos = e.ecs.Get<Transform>(goose).position;
                vec2 gooseMazeIndex = e.maze.WorldPosToMazeIndex(goosePos);
                
                //find the path to target
                bool foundPath = e.pathfinder.findPath(gooseMazeIndex);
                if(!foundPath)
                {
                    std::cout << "wtf\n";
                }
            }
        }

        if(!isMoving)
        {
            isMoving = true;
            pathStack = e.pathfinder.getPath();
            vec2 huh = pathStack.top();
            pathStack.pop();
            //vec3 wot = vec3(huh.x, huh.y, 0);
            newMovePos = e.maze.MazeIndexToWorldPosVec2(huh);
        }
        else
        {
            if(!alreadyCalcDistance)
            {
                vec3 diff = newMovePos - e.ecs.Get<Transform>(goose).position;
                movOffsetAmount.x = diff.x/60;
                movOffsetAmount.y = diff.y/60;
                movOffsetAmount.z = diff.z/60;
                alreadyCalcDistance = true;
            }

            float dist = glm::distance(newMovePos,  e.ecs.Get<Transform>(goose).position);
            //std::cout << "dist: x:" << dist.x << " y: " << dist.y << " z, " << dist.z << "\n";
            std::cout << "dist: " << dist << "\n";
            //within a certain range
            if(dist < 0.01)//if(dist.x <= 0.01f || dist.y <= 0.01f)
            {
                 e.ecs.Get<Transform>(goose).position = newMovePos;
                 isMoving = false;
                 alreadyCalcDistance = false;
                 hasTarget = false;
            }
            else
            {
                e.ecs.Get<Transform>(goose).position += movOffsetAmount;
            }

        }
    };

    auto LetterBehavior = [&]()
    {
        e.ecs.ForEach<MazeObject, Transform>([&](EntityID id)
        {
            auto mo = e.ecs.Get<MazeObject>(id);
            auto pos = e.ecs.Get<Transform>(id).position;
            if(!mo.isFound)
            {
                float dist = glm::distance(pos,  e.ecs.Get<Transform>(goose).position);
                if(dist <= 0.01f)
                {
                    mo.isFound = true;
                }
            }
        });
    };

    e.RunGameLoop([&]() {
        
        e.graphics.Draw();
        
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q))
        {
            std::cout << "quack\n";
            e.sounds.PlaySound("quack.wav");
        }
        
        GooseBehavior();
        LetterBehavior();
        


        return;

        });

    return 0;
}
