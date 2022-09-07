#include <iostream>

#include "../src/Types.h"
#include "../src/Engine.h"
#include "../src/EngineRef.h"
using namespace Pillbox;

char c = 'a';

int main(int argc, const char* argv[]) {
    std::cout << "Hello, World!\n";
    /*
    EngineRef e;
    e.engine->RunGameLoop(&PrintInput);
    */
    Engine e;
    e.RunGameLoop(&PrintInput);
    return 0;
}

void PrintInput(char c)
{
    std::cout << "Pressing: " << c << "\n";
}