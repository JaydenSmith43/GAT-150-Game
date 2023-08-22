#include "Core/Core.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>

#include "Physics/PhysicsSystem.h"

#include <functional>

//#include <cassert> // ASSERT

using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;

};


int main(int argc, char* argv[])
{
	kiko::Factory::Instance().Register<kiko::SpriteComponent>("SpriteComponent");
	kiko::Factory::Instance().Register<kiko::SpriteComponent>("CircleCollisionComponent");

	INFO_LOG("Initialize Engine");

	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize(); //Crash

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	vector<Star> stars;
	for (int i = 0; i < 100; i++) {
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 1000), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	
	float speed = 350;
	constexpr float turnRate = kiko::DegreesToRadians(180.0f); //? //cast to fix

	// create texture
	
	//kiko::res_t<kiko::Texture> texture = kiko::g_resources.Get<kiko::Texture>("megaman.png", kiko::g_renderer);
	//shared_ptr<kiko::Texture> texture = make_shared<kiko::Texture>();
	//texture->Load("megaman.png", kiko::g_renderer);



	//main game loop
	bool quit = false;
	while (!quit) 
	{
		kiko::MemoryTracker::DisplayInfo();
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)))
		{
			kiko::g_audioSystem.PlayOneShot("laser", false);
		}

		kiko::g_audioSystem.Update();


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

		for (auto& star : stars) {
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(255, 255, 255, 255);

			star.Draw(kiko::g_renderer);
		}
		
		

		//kiko::g_renderer.DrawTexture(texture.get(), 0.0f, 0.0f, 0.0f);

		kiko::g_particleSystem.Draw(kiko::g_renderer);
		//text->Draw(kiko::g_renderer, 400, 300);

		
		
		kiko::g_renderer.EndFrame();

		

		//this_thread::sleep_for(chrono::milliseconds(100)); // Fake Lag
	}
	//stars.clear();

	return 0;
}
