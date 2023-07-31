#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Renderer/ParticleSystem.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

using namespace kiko;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * g_time.GetDeltaTime();
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

	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();


	//kiko::vec2 v{5, 5};
	//v.Normalize();


	vector<Star> stars;
	for (int i = 0; i < 100; i++) {
		kiko::Vector2 pos(Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(randomf(100, 1000), 0.0f);

		stars.push_back(Star(pos, vel));
	}


	//kiko::vec2 position { 400, 300 };
	//kiko::Transform transform{ { 400, 300 }, 0, 3};
	
	float speed = 350;
	constexpr float turnRate = kiko::DegreesToRadians(180.0f); //? //cast to fix




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
			g_audioSystem.PlayOneShot("laser", false);
		}

		g_audioSystem.Update();


		//update game
		game->Update(kiko::g_time.GetDeltaTime());


		if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
		{
			cout << "mouse pressed" << endl;
			cout << "mouse located at: " << kiko::g_inputSystem.GetMousePosition().x << "," << kiko::g_inputSystem.GetMousePosition().y << endl;
		}


		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		for (auto& star : stars) {
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(255, 255, 255, 255);

			star.Draw(kiko::g_renderer);
		}
		
		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		//text->Draw(kiko::g_renderer, 400, 300);
		
		kiko::g_renderer.EndFrame();

		

		//this_thread::sleep_for(chrono::milliseconds(100)); // Fake Lag
	}
	//stars.clear();

	return 0;
}
