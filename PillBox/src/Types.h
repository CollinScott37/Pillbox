#pragma once
#include <iostream>
#include <string>
#include <functional>

namespace Pillbox
{
    typedef double real;
    typedef std::string string;

    class Engine;
    class EngineRef;
    class GraphicsManager;
    class InputManager;

    typedef std::function<void()> UpdateCallback;

}