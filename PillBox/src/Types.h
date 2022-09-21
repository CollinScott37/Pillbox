#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>

#include "GLFW/glfw3.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace
{
    struct Sprite {
        std::string name;
        glm::vec2 position;
        glm::vec2 scale;
        double z;
    };
}

namespace Pillbox
{
    typedef double real;
    typedef std::string string;

    class Engine;
    class EngineRef;
    class GraphicsManager;
    class InputManager;
    class ResourceManager;
    class SoundManager;

    typedef std::function<void ()> UpdateCallback;
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

    //std::function<"Return_Type"("Parameters");

}