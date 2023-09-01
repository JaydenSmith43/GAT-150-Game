#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		enum class playerState
		{
			Idle,
			Hurt,
			Attack,
			Crouch,
			CrouchAttack
		};

	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	public:
		float speed = 0;
		float maxSpeed = 0;

		float attackTimer = 1;
		bool attackTimerActive = false;
		float hurtTimer = 0.5f;
		bool hurtTimerActive = false;

		float jump = 0;
		float defaultJump = 0;
		int groundCount = 0;
		int facing = -1;

		int health = 100;

		playerState m_state = playerState::Idle;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimComponent* m_spriteAnimComponent = nullptr;
	};
}
