#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/EnginePhysicsComponent.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"



bool SpaceGame::Initialize()
{
	// create font / text objects
	//m_font = kiko::g_resources.Get <kiko::Font>("space.ttf", 30); // Don't need m_font
	m_titleText = std::make_unique<kiko::Text>(kiko::g_resources.Get <kiko::Font>("space.ttf", 30));
	m_titleText->Create(kiko::g_renderer, "asteroids", kiko::Color{ 1, 1, 1, 1 });

	m_scoreText = std::make_unique<kiko::Text>(kiko::g_resources.Get <kiko::Font>("space.ttf", 30));
	m_scoreText->Create(kiko::g_renderer, "score", kiko::Color{ 1, 0, 1, 1 });

	m_gameOverText = std::make_unique<kiko::Text>(kiko::g_resources.Get <kiko::Font>("space.ttf", 30));
	m_gameOverText->Create(kiko::g_renderer, "GameOver", kiko::Color{ 1, 0, 1, 1 });

	m_waveText = std::make_unique<kiko::Text>(kiko::g_resources.Get <kiko::Font>("space.ttf", 30));
	m_waveText->Create(kiko::g_renderer, "wave", kiko::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<kiko::Text>(kiko::g_resources.Get <kiko::Font>("space.ttf", 30));
	m_livesText->Create(kiko::g_renderer, "wave", kiko::Color{ 0, 1, 0.4f, 1 });

	

	//load audio
	kiko::g_audioSystem.AddAudio("laser", "laser.wav");
	kiko::g_audioSystem.AddAudio("music", "gogo!.wav");
	kiko::g_audioSystem.PlayOneShot("music", true);

	m_scene = std::make_unique<kiko::Scene>();

	return true;
}

bool SpaceGame::Shutdown()
{
	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_kills = 0;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		// create player
		auto player = std::make_unique<Player>(10.0f, kiko::Pi, kiko::Transform{ {400, 300 }, 0, 4 }); // kiko::g_manager.Get("ship.txt") std::unique_ptr<Player>
		player->m_tag = "Player";
		player->m_game = this;

		// create components
		auto renderComponent = std::make_unique<kiko::SpriteComponent>();
		renderComponent->m_texture = kiko::g_resources.Get<kiko::Texture>("megaman.png", kiko::g_renderer);
		player->AddComponent(std::move(renderComponent));

		auto physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));

		m_scene->Add(std::move(player));
	}
		m_state = eState::Game;
		break;

	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		
		if (m_spawnTimer >= m_spawnTime)
		{
			if (m_currentWave > 2)
			{
				randomShip = kiko::random(5);
				if (randomShip == 0)
				{
					std::unique_ptr<Boss> boss = std::make_unique<Boss>(30.0f, kiko::Pi, kiko::Transform{ {400, 0}, kiko::randomf(kiko::TwoPi), 8}); // kiko::g_manager.Get("boss.txt")

					boss->m_tag = "Enemy";
					boss->m_game = this;
					m_scene->Add(std::move(boss));
					m_spawnTimer = 0;
				}
				else
				{
					SpawnShip();
				}
			} 
			else 
			{
				SpawnShip();
			}
		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;

	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;

	default:
		break;
	}

	//kills for wave check
	if (m_kills == 0)
	{
		m_currentWave = 0;
		m_spawnTime = 2.0f;
		m_scoreMultiplier = 1;
	}
	if (m_kills == 10)
	{
		m_currentWave = 2;
		m_spawnTime = 1.5f;
		m_scoreMultiplier = 1.5f;
	}
	else if (m_kills == 25)
	{
		m_currentWave = 3;
		m_spawnTime = 1.2f;
		m_scoreMultiplier = 2.0f;
	}
	else if (m_kills == 40)
	{
		m_currentWave = 4;
		m_spawnTime = 1.0f;
		m_scoreMultiplier = 3.0f;
	}
	else if (m_kills == 60)
	{
		m_currentWave = 5;
		m_spawnTime = 1.0f;
		m_scoreMultiplier = 5.0f;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string((int)m_score), { 1, 1, 1, 1 });
	m_waveText->Create(kiko::g_renderer, "Wave: " + std::to_string(m_currentWave), {1, 0, 1, 1});
	m_livesText->Create(kiko::g_renderer, "Lives: " + std::to_string(m_lives), { 0, 1, 0.4f, 1});

	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 300, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 300, 300);
	}

	if (m_state == eState::Game || m_state == eState::PlayerDead)
	{
		m_waveText->Draw(renderer, 300, 40);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_livesText->Draw(renderer, 600, 40);

	m_scene->Draw(renderer);
}

void SpaceGame::SpawnShip()
{
	//setting so enemies only spawn at corners of screen
	int borderSpawnX = kiko::random(2);
	int borderSpawnY = kiko::random(2);

	if (borderSpawnX == 0)
	{
		borderSpawnX = 750;
	}
	else {
		borderSpawnX = 50;
	}

	if (borderSpawnY == 0)
	{
		borderSpawnY = 575;
	}
	else {
		borderSpawnY = 25;
	}

	m_spawnTimer = 0;

	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>((kiko::randomf(75.0f, 150.0f)), kiko::Pi, kiko::Transform{ {borderSpawnX + kiko::random(50), borderSpawnY + kiko::random(25)},
		kiko::randomf(kiko::TwoPi), 2}); // kiko::g_manager.Get("enemy.txt")

	enemy->m_tag = "Enemy";
	enemy->m_game = this;

	std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
	component->m_texture = kiko::g_resources.Get<kiko::Texture>("megaman.png", kiko::g_renderer);
	enemy->AddComponent(std::move(component));

	m_scene->Add(std::move(enemy));
}