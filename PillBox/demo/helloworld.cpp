#include <iostream>

#include "Types.h"
#include "Engine.h"

using namespace Pillbox;


int main(int argc, const char* argv[]) {
    
    std::cout << "Takes a min to load\n";
    
    Engine e;
    e.StartUp();
    e.sounds.LoadSound("quack.wav", "sounds");
    
    //load both image and sprite
    //e.graphics.LoadImageFile("gred.png", "images");
    //e.graphics.LoadSprite("gred.png", vec2(0), vec3(10), 0.0);


    e.graphics.LoadImageFile("goose.png", "images");
    e.graphics.LoadSprite("goose.png", vec2(0), vec3(50), 0.0);

    std::cout << "done loading\n";

    e.RunGameLoop([&]() {
        
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q) == true)
        {
            std::cout << "Quack!\n";
            e.sounds.PlaySound("quack.wav");
        }


        return;

        });

    return 0;
}
