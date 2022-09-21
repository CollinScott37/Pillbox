#include <iostream>

#include "Types.h"
#include "Engine.h"

using namespace Pillbox;


int main(int argc, const char* argv[]) {
    
    std::cout << "Takes a min to load\n";
    Engine e;
    e.StartUp();
    e.sounds.LoadSound("quack.wav", "sounds");
    //bool prevInputq = e.input.KeyIsPressed(GLFW_KEY_Q);
    //bool prevInputn = e.input.KeyIsPressed(GLFW_KEY_N);
    //bool prevInputp = e.input.KeyIsPressed(GLFW_KEY_P);
    //bool prevInputr = e.input.KeyIsPressed(GLFW_KEY_R);

    std::cout << "done loading";
    e.RunGameLoop([&]() {
        
        if (e.input.GetKeyCodeUp(GLFW_KEY_Q) == true)
        {
            std::cout << "Quack!\n";
            e.sounds.PlaySound("quack.wav");
        }


        if (e.input.GetKeyCodeUp(GLFW_KEY_N) == true)
        {
            std::cout << "Boom!\n";
            //e.sounds.PlaySoundKeyboard(GLFW_KEY_N);
        }

        if (e.input.GetKeyCodeUp(GLFW_KEY_P) == true)
        {
            std::cout << ";)\n";
            // e.sounds.PlaySoundKeyboard(GLFW_KEY_P);
        }

        if (e.input.GetKeyCodeUp(GLFW_KEY_R) == true)
        {
            std::cout << "uh oh\n";
            //e.sounds.PlaySoundKeyboard(GLFW_KEY_R);
        }


        return;

        });

    return 0;
}

void PrintInput(char c)
{
    std::cout << "Pressing: " << c << "\n";
}