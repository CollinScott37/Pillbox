#include "ScriptManager.h"
//#define GLFW_INCLUDE_NONE
//#include "GLFW/glfw3.h"
#include "Engine.h"

using namespace Pillbox;


void ScriptManager::StartUp()
{
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
	lua.script("math.randomseed(0)");
	lua.new_enum("KEYBOARD",
		"A", GLFW_KEY_A,
		"B", GLFW_KEY_B,
		"C", GLFW_KEY_C,
		"D", GLFW_KEY_D,
		"E", GLFW_KEY_E,
		"F", GLFW_KEY_F,
		"G", GLFW_KEY_G,
		"H", GLFW_KEY_H,
		"I", GLFW_KEY_I,
		"J", GLFW_KEY_J,
		"K", GLFW_KEY_K,
		"L", GLFW_KEY_L,
		"M", GLFW_KEY_M,
		"N", GLFW_KEY_N,
		"O", GLFW_KEY_O,
		"P", GLFW_KEY_P,
		"Q", GLFW_KEY_Q,
		"R", GLFW_KEY_R,
		"S", GLFW_KEY_S,
		"T", GLFW_KEY_T,
		"U", GLFW_KEY_U,
		"V", GLFW_KEY_V,
		"W", GLFW_KEY_W,
		"X", GLFW_KEY_X,
		"Y", GLFW_KEY_Y,
		"Z", GLFW_KEY_Z,
		"ESC", GLFW_KEY_ESCAPE,
		"SPACE", GLFW_KEY_SPACE
		);

	//input
	lua.set_function("GetKeyCodeUp", [&](const int keycode) {return engine.input.GetKeyCodeUp(keycode); });
	lua.set_function("GetKeyCodeDown", [&](const int keycode) {return engine.input.GetKeyCodeDown(keycode); });
	
	//ECS
	lua.set_function("UnusedEntity", [&]() {return engine.ecs.UnusedEntity(); });
	lua.set_function("Destroy", [&](const int id) { engine.ecs.Destroy(id); } );	

	//Sound
	lua.set_function("LoadSound", [&](const string& name, const string& path) { return engine.sounds.LoadSound(name, path); } );
	lua.set_function("PlaySound", [&](const string& name) { return engine.sounds.PlaySound(name); } );

	//Grahics
	lua.set_function("LoadImageFile", [&](const string& name, const string& path) { return engine.graphics.LoadImageFile(name, path); });

	//Components
	lua.new_usertype<Sprite>("Sprite",
		sol::constructors<Sprite()>(),
		"name", &Sprite::name,
		"z", &Sprite::z
		);

	lua.new_usertype<glm::vec3>("vec3",
		sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		// optional and fancy: operator overloading. see: https://github.com/ThePhD/sol2/issues/547
		sol::meta_function::addition, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; }),
		sol::meta_function::subtraction, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; }),
		sol::meta_function::multiplication, sol::overload(
			[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
			[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
			[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
		)
		);

	
	lua.new_usertype<Transform>("Transform",
		sol::constructors<Transform()>(),
		"position", &Transform::position,
		"rotation", &Transform::rotation,
		"scale", &Transform::scale
		);

	//ECS Getters
	lua.set_function("GetSprite", [&](const EntityID id) { return engine.ecs.Get<Sprite>(id); });
	lua.set_function("GetTransform", [&](const EntityID id) { return engine.ecs.Get<Transform>(id); });



}


bool ScriptManager::LoadScript(const string& name, const string& path)
{
	string p = path + "/" + name;

	if (scripts.count(name) == 0)
	{
		scripts[name] = lua.load_file(engine.resources.getPath(p).c_str());
		EntityID entity = engine.ecs.UnusedEntity();
		engine.ecs.Get<Script>(entity) = Script{ name };
		return true;	
	}
	else
	{
		return false;
	}
}

void ScriptManager::Update()
{
	
	engine.ecs.ForEach<Script>([&](EntityID e)
		{
			Script s = engine.ecs.Get<Script>(e);
			scripts[s.name](); //run script

		});
	
		
}

