#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	public:
		float m_speed = 0;
		float m_turnRate = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
