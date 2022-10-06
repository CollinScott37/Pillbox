#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

//#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

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
    class ECS;
    class ScriptManager;

    typedef long EntityID;

    typedef std::function<void(EntityID)> ForEachCallback;
    typedef std::function<void ()> UpdateCallback;
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

    
    struct Transform { vec3 position; vec3 rotation; vec3 scale; };
    struct Sprite
    {
        std::string name; double z; 
        
    
    };
    
    //struct Velocity { real x, y; }; // or: struct Velocity : public vec2 {};
    //struct Gravity { real meters_per_second; };
    ///struct Sprite { string image; real size; };
    //struct Health { real percent; };
    struct Script { string name; };

    //std::function<"Return_Type"("Parameters");

}