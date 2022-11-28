#include "GraphicsManager.h"
#include "Engine.h"

//#define GLFW_INCLUDE_NONE

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Pillbox;
using namespace glm;

namespace {
    struct Uniforms {
        glm::mat4 projection;
        glm::mat4 transform;
    };
}


void GraphicsManager::StartUp()
{
    //EngineRef.engine->Test();
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, window_name, window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
    glfwSetWindowAspectRatio(window, window_width, window_height);
    if (!window)
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //sokol
    // A vertex buffer containing a textured square.
    const float vertices[] = {
        // positions      // texcoords
        -1.0f,  -1.0f,    0.0f,  1.0f,
         1.0f,  -1.0f,    1.0f,  1.0f,
        -1.0f,   1.0f,    0.0f,  0.0f,
         1.0f,   1.0f,    1.0f,  0.0f,
    };


    sg_setup(sg_desc{});
    sg_buffer_desc buffer_desc{};
    buffer_desc.data = SG_RANGE(vertices);
    sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);


    sg_pipeline_desc pipeline_desc{};
    pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
    pipeline_desc.colors[0].blend.enabled = true;
    pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
    pipeline_desc.depth.write_enabled = true;   
    pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
    pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

    //shader
    sg_shader_desc shader_desc{};
    shader_desc.vs.source = R"(
    #version 330
    uniform mat4 projection;
    uniform mat4 transform;
    layout(location=0) in vec2 position;
    layout(location=1) in vec2 texcoords0;
    out vec2 texcoords;
    void main() {
        gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
        texcoords = texcoords0;
    })";
    shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
    // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
    shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
    shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
    shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
    shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

    //fragment shader
    shader_desc.fs.source = R"(
    #version 330
    uniform sampler2D tex;
    in vec2 texcoords;
    out vec4 frag_color;
    void main() {
        frag_color = texture( tex, texcoords );
        // If we're not drawing back to front, discard very transparent pixels so we
        // don't write to the depth buffer and prevent farther sprites from drawing.
        if( frag_color.a < 0.1 ) discard;
    }
    )";
    shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
    shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;


    //add shader to pipeline
    pipeline_desc.shader = sg_make_shader( shader_desc );
    pipeline = sg_make_pipeline( pipeline_desc );

    pass_action.colors[0].action = SG_ACTION_CLEAR;
    pass_action.colors[0].value = { 0.5, 0.5, 0.5, 1/* red, green, blue, alpha floating point values for a color to fill the frame buffer with */ };

    
    bindings.vertex_buffers[0] = vertex_buffer;



}
bool GraphicsManager::LoadImageFile( const string& name, const string& path )
{
    int width, height, channels;

    string p = path + "/" + name;

    unsigned char* data = stbi_load( engine.resources.getPath(p).c_str(), &width, &height, &channels, 4 );
    
    sg_image_desc image_desc{};
    image_desc.width = width;
    image_desc.height = height;
    image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
    image_desc.min_filter = SG_FILTER_LINEAR;
    image_desc.mag_filter = SG_FILTER_LINEAR;
    image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
    image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
    image_desc.data.subimage[0][0].ptr = data;
    image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);
   
    //upload image to GPU
    sg_image image = sg_make_image( image_desc );
    stbi_image_free( data );

    imageMap[name] = ImageData{ name, image, width, height };

    return true;
}



void GraphicsManager::ShutDown()
{
    glfwTerminate();
    sg_shutdown();
}

//void GraphicsManager::Draw(std::vector<Sprite>& sprites)
void GraphicsManager::Draw()
{

    glfwGetFramebufferSize(window, &window_width, &window_height);
    sg_begin_default_pass(pass_action, window_width, window_height);
    sg_apply_pipeline(pipeline);
    
    Uniforms uniforms;
    // Start with an identity matrix.
    uniforms.projection = mat4{ 1 };
    // Scale x and y by 1/100.
    uniforms.projection[0][0] = uniforms.projection[1][1] = 1. / 100.;
    // Scale the long edge by an additional 1/(long/short) = short/long.
    if (window_width < window_height) {
        uniforms.projection[1][1] *= window_width;
        uniforms.projection[1][1] /= window_height;
    }
    else {
        uniforms.projection[0][0] *= window_height;
        uniforms.projection[0][0] /= window_width;
    }
    
    engine.ecs.ForEach<Sprite, Transform>([&](EntityID e)
        {
            Sprite s = engine.ecs.Get<Sprite>(e);
            Transform t = engine.ecs.Get<Transform>(e);
            
            float angle = t.rotation.x;

            int image_width = imageMap[s.name].width;
            int image_height = imageMap[s.name].width;
            glm::vec2 position = t.position;
            real z = s.z; //placeholder
            glm::vec3 scale = t.scale; //placeholder
            //* rotate(mat4{ 1.0 }, glm::radians(s.rotateAngle), s.rotateAxis)
            uniforms.transform = translate(mat4{ 1 }, vec3(position, z)) * rotate(mat4{ 1.0 }, glm::radians(angle), t.axis)  * glm::scale(mat4{ 1 }, vec3(scale.x, scale.y, scale.z));//scale ) ); 

            if (image_width < image_height) {
                uniforms.transform = uniforms.transform * glm::scale(mat4{ 1 }, vec3(real(image_width) / image_height, 1.0, 1.0));
            }
            else {
                uniforms.transform = uniforms.transform * glm::scale(mat4{ 1 }, vec3(1.0, real(image_height) / image_width, 1.0));
            }


            sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));

            bindings.fs_images[0] = imageMap[s.name].data;
            sg_apply_bindings(bindings);
            sg_draw(0, 4, 1);
        });
    
    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(window);

}


int GraphicsManager::ShouldQuit()
{
    //std::cout << "HERE1\n";
    return glfwWindowShouldClose(window);
}

void GraphicsManager::SetShouldQuit(bool quit)
{
    std::cout << "HERE2\n";
    glfwSetWindowShouldClose(window, quit);
}
