#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
#include <map>


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
    class MazeManager;
    class PathFind;
    typedef long EntityID;

    typedef std::function<void(EntityID)> ForEachCallback;
    typedef std::function<void ()> UpdateCallback;
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

    
    struct Transform { vec3 position; vec3 rotation; vec3 scale; };
    struct Sprite { std::string name; double z; };
    struct Trigger { vec3 tl; vec3 br; };
    struct Target { Transform target; };

    struct MazeObject { vec3 mazeIndex; bool isFound = false; };
    struct Script { std::string name; };

    //std::function<"Return_Type"("Parameters");

}