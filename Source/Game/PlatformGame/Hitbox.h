#pragma once
#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Hitbox : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Hitbox)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	public:
		float timer = 0.5f;
		class PhysicsComponent* m_physicsComponent = nullptr; 
		class SpriteAnimComponent* m_spriteAnimComponent = nullptr;
	};
}
