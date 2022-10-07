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

    
    
    /* //Attempt 1
    EntityID test = e.ecs.UnusedEntity();
    e.scripts.LoadScript("test.lua", "scripts");
    e.ecs.Get<Script>(test) = Script{ "test.lua" };
    */

    //Atempt 2
    e.scripts.LoadScript("test.lua", "scripts");
    e.scripts.RunScript("test.lua");


 
    e.RunGameLoop([&]() {
        
        /*
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q))
        {
            std::cout << "Quack!\n";
            e.sounds.PlaySound("quack.wav");
        }

        
        */

        e.graphics.Draw();
        return;

        });

    return 0;
}
