#pragma once
#include <memory>

namespace kiko
{
	class Scene; //forward declaration
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual bool Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		float GetScore() const { return m_score; };
		void AddPoints(float points) { m_score += points * m_scoreMultiplier; }
		void AddKills(int kills) { m_kills += kills; }

		int GetLives() const { return m_lives; };
		void SetLives(int lives) { m_lives = lives; }
		
	protected:
		std::unique_ptr<Scene> m_scene;

		float m_score = 0.0f;
		int m_kills = 0;
		int m_lives = 0;
		float m_scoreMultiplier = 1.0f;
	};
}