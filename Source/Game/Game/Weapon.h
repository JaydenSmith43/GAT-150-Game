#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		/*
		WeaponComponent(float speed, const kiko::Transform& transform) : //removing model as we dont specify it anymore
			Actor{ transform },
			speed{ speed } // could add parameter for lifespan
		{
			lifespan = 2.0f;
		}
		*/
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
	};
}
