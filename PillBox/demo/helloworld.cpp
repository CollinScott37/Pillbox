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
        vec3 wp = e.maze.MazeIndexToWorldPos(mi);
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
    //gred
    EntityID gred = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(gred) = Sprite{"gred.png", 0.5};
    e.ecs.Get<Transform>(gred) = Transform{vec3(0), vec3(0), vec3(10,10,10)};
    e.graphics.LoadImageFile("gred.png", "images");

    //Goose
    */
    EntityID cube = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(cube) = Sprite{ "cube.png", 0.1 };
    e.ecs.Get<Transform>(cube) = Transform{ vec3(0), vec3(0), vec3(1,1,1) };
    e.graphics.LoadImageFile("cube.png", "images");


    
    
    std::cout << "done loading\n";
    
    EntityID goose = e.ecs.UnusedEntity();
    
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

    //EntityID corner1 = e.ecs.UnusedEntity();
    //EntityID corner2 = e.ecs.UnusedEntity();
    

    /*
    EntityID Sounds = e.ecs.UnusedEntity();
    e.scripts.LoadScript("soundscript.lua", "scripts");
    e.ecs.Get<Script>(Sounds) = Script{ "soundscript.lua" };
    */
    /*
    e.scripts.LoadScript("test.lua", "scripts");
    e.ecs.Get<Script>(goose) = Script{ "test.lua" };

    e.scripts.LoadScript("cube.lua", "scripts");
    e.ecs.Get<Script>(N0) = Script{ "cube.lua" };
    e.ecs.Get<Script>(O) = Script{ "cube.lua" };
    e.ecs.Get<Script>(C) = Script{ "cube.lua" };
    e.ecs.Get<Script>(A) = Script{ "cube.lua" };
    e.ecs.Get<Script>(N1) = Script{ "cube.lua" };
    e.ecs.Get<Script>(E) = Script{ "cube.lua" };
    e.ecs.Get<Script>(QM) = Script{ "cube.lua" };
    */

    

    e.RunGameLoop([&]() {
        
        e.graphics.Draw();
        
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q))
        {
            std::cout << "quack\n";
            e.sounds.PlaySound("quack.wav");
            e.maze.CreateMaze();
            for (int i = N0; i <= QM; i += 1)
            {
                InitMazeObject(i, "null");
            }

        }

        return;

        });

    return 0;
}
