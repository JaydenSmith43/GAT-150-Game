#include "PlatformGame.h"

#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

#include "Framework/Components/TextRenderComponent.h"

bool PlatformGame::Initialize()
{
	//load audio
	kiko::g_audioSystem.AddAudio("death", "Audio/death.wav");
	kiko::g_audioSystem.AddAudio("hurt", "Audio/chipHurt.wav");
	kiko::g_audioSystem.AddAudio("music", "Audio/GothicGame.wav");
	kiko::g_audioSystem.PlayOneShot("music", true);

	//create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/PlatformScene.json");
	m_scene->Load(loadString);
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnEnemyDead", PlatformGame::OnEnemyDead); 
	EVENT_SUBSCRIBE("OnPlayerHit", PlatformGame::OnPlayerHit);

	kiko::EventManager::Instance().Subscribe("OnAddPoints", this, std::bind(&PlatformGame::OnAddPoints, this, std::placeholders::_1));
	kiko::EventManager::Instance().Subscribe("OnEnemyDead", this, std::bind(&PlatformGame::OnEnemyDead, this, std::placeholders::_1));
	kiko::EventManager::Instance().Subscribe("OnPlayerHit", this, std::bind(&PlatformGame::OnPlayerHit, this, std::placeholders::_1));

	return true;
}

bool PlatformGame::Shutdown()
{
	return true;
}

void PlatformGame::Update(float dt)
{
	//probably not the best way, but stores that player hasKey even when loading different screen/scene
	if (m_scene->GetActorByName("Player")->tag == "hasKey")
	{
		hasKey = true;
	}
	if (hasKey == true)
	{
		m_scene->GetActorByName("Player")->tag = "hasKey";
	}

	switch (m_state)
	{
	case PlatformGame::eState::Title:



	case PlatformGame::eState::StartGame:
		

		m_state = eState::LoadLevel;
		break;

	case PlatformGame::eState::LoadLevel:
		m_scene->RemoveAll();
		m_scene = std::make_unique<kiko::Scene>();
		m_scene->Load("Scenes/platformScene.json");

		m_scene->GetActorByName("Player")->transform.position.x = spawnLocationX;
		m_scene->GetActorByName("Player")->transform.position.y = spawnLocationY;

		m_scene->GetActorByName("Bat")->transform.position.x = spawnLocationX;

		loadString = "Scenes/screen" + std::to_string(m_currentScreen) + ".json";
		m_scene->Load(loadString);

		m_scene->Initialize();
		
		if (m_currentScreen == 5)
		{
			m_scene->GetActorByName("Title")->active = true;
		}
		else
		{
			m_scene->GetActorByName("Title")->active = false;
		}
		
		m_state = eState::Game;
		break;

	case PlatformGame::eState::Game:
		if (m_scene->GetActorByName("Player")->transform.position.x >= 800)
		{
			m_currentScreen++;
			m_state = eState::LoadLevel;
			spawnLocationX = 30;
			spawnLocationY = m_scene->GetActorByName("Player")->transform.position.y;
		}

		if (m_scene->GetActorByName("Player")->transform.position.x <= 0)
		{
			m_currentScreen--;
			m_state = eState::LoadLevel;
			spawnLocationX = 770;
			spawnLocationY = m_scene->GetActorByName("Player")->transform.position.y;
		}
		break;


		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::LoadLevel;
		}
		break;

	case PlatformGame::eState::GameOver:
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

	m_scene->GetActorByName("healthText")->GetClassName();

	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnEnemyDead(const kiko::Event& event)
{
	//m_lives--;
	//m_state = eState::PlayerDeadStart;
	kiko::g_audioSystem.PlayOneShot("death");
}

void PlatformGame::OnPlayerHit(const kiko::Event& event)
{
	kiko::g_audioSystem.PlayOneShot("hurt");
}