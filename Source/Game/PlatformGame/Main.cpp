#include "Core/Core.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Framework/Framework.h"

#include <iostream>
#include <vector>
#include <thread>
//#include <array>
//#include <map>
#include <functional>
#include "PlatformGame.h"



using namespace std;


int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine");

	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("Assets/Platformer");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize(); //Crash

	// create game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();


	//main game loop
	bool quit = false;
	while (!quit)
	{
		//kiko::MemoryTracker::DisplayInfo();
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)))
		{
			kiko::g_audioSystem.PlayOneShot("laser", false);
		}

		kiko::g_audioSystem.Update();

		//cout << (1.0f / kiko::g_time.GetDeltaTime()) << endl;


		// update game
		game->Update(kiko::g_time.GetDeltaTime());


		if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
		{
			cout << "mouse pressed" << endl;
			cout << "mouse located at: " << kiko::g_inputSystem.GetMousePosition().x << "," << kiko::g_inputSystem.GetMousePosition().y << endl;
		}

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);

		//kiko::g_renderer.DrawTexture(texture.get(), 0.0f, 0.0f, 0.0f);

		kiko::g_particleSystem.Draw(kiko::g_renderer);
		//text->Draw(kiko::g_renderer, 400, 300);



		kiko::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100)); // Fake Lag
	}

	return 0;
}
