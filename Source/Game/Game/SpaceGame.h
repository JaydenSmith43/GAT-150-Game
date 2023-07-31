#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

//space game is derived from game
//cannot forward declare when deriving

class SpaceGame : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
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

	void SpawnShip();

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 2.0f;

	float m_stateTimer = 0;
	int randomShip = 0;

	int m_currentWave = 1;

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_waveText;
	std::unique_ptr<kiko::Text> m_titleText;
	std::unique_ptr<kiko::Text> m_gameOverText;
	std::unique_ptr<kiko::Text> m_livesText;
};
