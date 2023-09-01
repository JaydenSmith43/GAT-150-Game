#pragma once
#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Bat : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Bat)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	public:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		float m_fireRate = 3.0f;
		float m_fireTimer = m_fireRate;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
