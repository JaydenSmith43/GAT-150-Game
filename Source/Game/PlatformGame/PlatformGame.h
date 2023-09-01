#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Renderer/Text.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"
#include "SDL2-2.28.0/include/SDL_image.h"

//platform game is derived from game
//cannot forward declare when deriving

class PlatformGame : public kiko::Game, kiko::IEventListener
{
public:
	enum class eState
	{
		Title,
		StartGame,
		LoadLevel,
		Game,
		PlayerDead,
		PlayerDeadStart,
		GameOver
	};

public:
	// Inherited via Game
	virtual bool Initialize() override;
	virtual bool Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void OnAddPoints(const kiko::Event& event);
	void OnEnemyDead(const kiko::Event& event);

	//SDL_Rect camera{ 0, 0, 800, 600 };

private:
	eState m_state = eState::Game;

	float m_spawnTimer = 0;
	float m_spawnTime = 2.0f;

	float m_stateTimer = 0;
	int randomShip = 0;

	int m_currentScreen = 5;
	int spawnLocationX = 0;
	int spawnLocationY = 0;

	std::string loadString = "Scenes/screen5.json";
};
