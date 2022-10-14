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
    
    
    /*
    e.sounds.LoadSound("quack.wav", "sounds");
    

    //gred
    EntityID gred = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(gred) = Sprite{"gred.png", 0.5};
    e.ecs.Get<Transform>(gred) = Transform{vec3(0), vec3(0), vec3(10,10,10)};
    e.graphics.LoadImageFile("gred.png", "images");

    //Goose
    EntityID goose = e.ecs.UnusedEntity();
    e.ecs.Get<Sprite>(goose) = Sprite{ "goose.png", 0.65 };
    e.ecs.Get<Transform>(goose) = Transform{ vec3(1), vec3(0), vec3(30,30,30) };
    e.graphics.LoadImageFile("goose.png", "images");
    
    */
    std::cout << "done loading\n";

    EntityID goose = e.ecs.UnusedEntity();
    EntityID N0 = e.ecs.UnusedEntity();
    EntityID O = e.ecs.UnusedEntity();
    EntityID C = e.ecs.UnusedEntity();
    EntityID A = e.ecs.UnusedEntity();
    EntityID N1 = e.ecs.UnusedEntity();
    EntityID E = e.ecs.UnusedEntity();
    EntityID QM = e.ecs.UnusedEntity();
    EntityID corner1 = e.ecs.UnusedEntity();
    EntityID corner2 = e.ecs.UnusedEntity();
    //For Initiating images, sound
    EntityID init = e.ecs.UnusedEntity();
    string p = "scripts/init.lua";
    auto initLoad = e.scripts.lua.load_file(e.resources.getPath(p).c_str());
    initLoad(goose, N0, O, C, A, N1, E, QM,  corner1, corner2); //run init

    EntityID Sounds = e.ecs.UnusedEntity();
    e.scripts.LoadScript("soundscript.lua", "scripts");
    e.ecs.Get<Script>(Sounds) = Script{ "soundscript.lua" };

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
    //  e.ecs.Get<Script>(O) = Script{ "cube.lua" };
 

    

    e.RunGameLoop([&]() {
        
        e.graphics.Draw();
        return;

        });

    return 0;
}
