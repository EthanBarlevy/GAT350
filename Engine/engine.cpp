#include "engine.h"

namespace vl
{
	InputSystem g_inputSystem;
	Renderer g_renderer;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resourceManager;
	PhysicsSystem g_physicsSystem;
	EventManager g_eventManager;
	GUI g_gui;

	void Engine::Initialize()
	{
		g_renderer.Initialize();
		g_inputSystem.Initialize();
		g_audioSystem.Initialize();
		g_resourceManager.Initialize();
		g_physicsSystem.Initialize();
		g_eventManager.Initialize();
	}

	void Engine::Shutdown()
	{
		g_gui.Shutdown();
		g_renderer.Shutodwn();
		g_inputSystem.Shutdown();
		g_audioSystem.Shutdown();
		g_resourceManager.Shutodwn();
		g_physicsSystem.Shutdown();
		g_eventManager.Shutdown();
	}

	void Engine::Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event));
		{
			g_gui.Update(event);
		}

		g_time.Tick();
		g_eventManager.Update();
		g_physicsSystem.Update();
		g_inputSystem.Update();
		g_audioSystem.Update();
		
	}

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(CameraController);
		REGISTER_CLASS(LightComponent);

	}
}