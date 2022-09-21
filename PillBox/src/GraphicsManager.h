#pragma once
#include "Types.h"
#include <unordered_map>

namespace
{
	struct ImageData {
		std::string name;
		sg_image data;
		int width;
		int height;
	};
}


namespace Pillbox
{
	class GraphicsManager
	{
	public:
		Engine& engine;
		GraphicsManager(Engine& e) : engine(e) {}
		friend class InputManager;
		void StartUp();
		void ShutDown();
		void Draw();
		bool LoadSprite( const string& name, const string& path );
		GLFWwindow* GetWindow();
		
		int ShouldQuit();
		void SetShouldQuit(bool);

	private:
		
		int window_width = 1280;
		int window_height = 720;
		const char* window_name = "Pillbox";
		bool window_fullscreen = 0;
		
		sg_pass_action pass_action{};
		sg_pipeline pipeline{};
		sg_bindings bindings{};	
		GLFWwindow* window;
		typedef std::unordered_map< string, ImageData > ImageMap;
		ImageMap imageMap;

	};
}