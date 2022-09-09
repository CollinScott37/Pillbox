#include <iostream>

#include "../src/Types.h"
#include "../src/Engine.h"
#include "../src/EngineRef.h"

using namespace Pillbox;


int main(int argc, const char* argv[]) {
    
    std::cout << "Takes a min to load\n";
    Engine e;

    bool prevInputq = e.input.KeyIsPressed(GLFW_KEY_Q);
    bool prevInputn = e.input.KeyIsPressed(GLFW_KEY_N);
    bool prevInputp = e.input.KeyIsPressed(GLFW_KEY_P);
    bool prevInputr = e.input.KeyIsPressed(GLFW_KEY_R);

    std::cout << "done loading"
    e.RunGameLoop([&]() {


        
        if (prevInputq == false && e.input.KeyIsPressed(GLFW_KEY_Q) == true)
        {
            std::cout << "Quack!\n";
            e.sounds.PlaySoundKeyboard(GLFW_KEY_Q);
        }
        

        if (prevInputn == false && e.input.KeyIsPressed(GLFW_KEY_N) == true)
        {
            std::cout << "Boom!\n";
            e.sounds.PlaySoundKeyboard(GLFW_KEY_N);
        }

        if (prevInputp == false && e.input.KeyIsPressed(GLFW_KEY_P) == true)
        {
            std::cout << ";)\n";
            e.sounds.PlaySoundKeyboard(GLFW_KEY_P);
        }

        if (prevInputr == false && e.input.KeyIsPressed(GLFW_KEY_R) == true)
        {
            std::cout << "uh oh\n";
            e.sounds.PlaySoundKeyboard(GLFW_KEY_R);
        }

        prevInputq = e.input.KeyIsPressed(GLFW_KEY_Q);
        prevInputn = e.input.KeyIsPressed(GLFW_KEY_N);
        prevInputp = e.input.KeyIsPressed(GLFW_KEY_P);
        prevInputr = e.input.KeyIsPressed(GLFW_KEY_R);
       
        return;
        
        });

    return 0;
}

void PrintInput(char c)
{
    std::cout << "Pressing: " << c << "\n";
}